// main.c
// xxd -i hello_world.cl > hello_world_cl.h
// gcc hello_world.c -o hello_opencl.exe -lOpenCL

#define CL_TARGET_OPENCL_VERSION 300
#include <CL/cl.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h> 

#include "hello_world_cl.h"


int main() {

    cl_context context = NULL;
    cl_command_queue command_queue = NULL;
    cl_program program = NULL;
    cl_kernel kernel = NULL;
    cl_int ret;

    // === Get number of platforms & devices ===
    cl_uint myplatform_index  = 0 ;
    cl_uint num_platforms;

    ret = clGetPlatformIDs(0, NULL, &num_platforms);
    if (ret != CL_SUCCESS || num_platforms == 0) {
        printf("No OpenCL platforms found! Error: %d\n", ret);
        return 1;
    }

    cl_platform_id platforms[num_platforms];
    clGetPlatformIDs(num_platforms, platforms, NULL);

    printf("Found %u platform(s)\n", num_platforms);

    for (cl_uint i = 0; i < num_platforms; i++) {
        char pname[128], vendor[128], version[128], extensions[1024];
        clGetPlatformInfo(platforms[i], CL_PLATFORM_NAME, sizeof(pname), pname, NULL);
        clGetPlatformInfo(platforms[i], CL_PLATFORM_VENDOR, sizeof(vendor), vendor, NULL);
        clGetPlatformInfo(platforms[i], CL_PLATFORM_VERSION, sizeof(version), version, NULL);
        clGetPlatformInfo(platforms[i], CL_PLATFORM_EXTENSIONS, sizeof(extensions), extensions, NULL);

        printf("\nPlatform %u:\n", i);
        printf("  Name:      %s\n", pname);
        printf("  Vendor:    %s\n", vendor);
        printf("  Version:   %s\n", version);
        printf("  Extensions:\n    %s\n", extensions);

        // Check GPU devices
        cl_uint num_devices;
        ret = clGetDeviceIDs(platforms[i], CL_DEVICE_TYPE_GPU, 0, NULL, &num_devices);

        if (ret == CL_DEVICE_NOT_FOUND || num_devices == 0) {
            fprintf(stdout, "  No GPU devices on this platform.\n");
            continue;
        } else if (ret != CL_SUCCESS) {
            fprintf(stderr, "  Error getting GPU devices: %d\n", ret);
            continue;
        }

        cl_device_id devices[num_devices];
        ret = clGetDeviceIDs(platforms[i], CL_DEVICE_TYPE_GPU, num_devices, devices, NULL);
        if (ret != CL_SUCCESS) {
            fprintf(stderr, "  Error getting GPU devices: %d\n", ret);
            continue;
        }

        for (cl_uint j = 0; j < num_devices; j++) {
            char dname[128];
            clGetDeviceInfo(devices[j], CL_DEVICE_NAME, sizeof(dname), dname, NULL);
            fprintf(stdout, "    GPU Device %u: %s\n", j, dname);
        }

        if (strcmp( pname, "NVIDIA CUDA") == 0) {
        if ( num_devices > 0 ) {
            myplatform_index = i;
        }}
    }

    cl_device_id device_id = NULL ;
    ret = clGetDeviceIDs(platforms[ myplatform_index ], CL_DEVICE_TYPE_GPU, 1, &device_id, NULL);
    if (ret != CL_SUCCESS) {
        fprintf(stderr, "Error getting device IDs: %d\n", ret);
        exit(1);
    }else{
        char dname[128];
        ret = clGetDeviceInfo( device_id , CL_DEVICE_NAME, sizeof(dname), dname, NULL);
        if (ret != CL_SUCCESS) {
            fprintf(stderr, "Error getting device info: %d\n", ret);
            exit(1);
        }
        fprintf(stdout, "\nUsing GPU device %s from platform %u\n", dname, myplatform_index);
    }

    // === end of getting number of platforms & devices ===


    context = clCreateContext(NULL, 1, &device_id, NULL, NULL, &ret);
    if (ret != CL_SUCCESS) {
        fprintf(stderr, "Error creating context: %d\n", ret);
        exit(1);
    }

    #if defined(CL_VERSION_2_0)
        // OpenCL 2.0+ headers, preferred
        const cl_queue_properties props[] = {0};
        command_queue = clCreateCommandQueueWithProperties(context, device_id, props, &ret);
    #else
        // OpenCL 1.2
        command_queue = clCreateCommandQueue(context, device_id, 0, &ret);
    #endif
    if (ret != CL_SUCCESS) {
        fprintf(stderr, "Failed to create command queue: %d\n", ret);
        exit(1);
    }

const char *source = (const char *)hello_world_cl;
size_t length = hello_world_cl_len;

program = clCreateProgramWithSource(context, 1, &source, &length, &ret);
if (ret != CL_SUCCESS) {
    printf("Error creating program: %d\n", ret);
}

    ret = clBuildProgram(program, 1, &device_id, NULL, NULL, NULL);
    if (ret != CL_SUCCESS) {
        size_t log_size;
        clGetProgramBuildInfo(program, device_id, CL_PROGRAM_BUILD_LOG, 0, NULL, &log_size);
        char *log = (char *) malloc(log_size);
        clGetProgramBuildInfo(program, device_id, CL_PROGRAM_BUILD_LOG, log_size, log, NULL);
        fprintf(stderr, "%s\n", log);
        free(log);
        exit(1);
    }

    kernel = clCreateKernel(program, "hello_world", &ret);
    if (ret != CL_SUCCESS) {
        fprintf(stderr, "Error creating kernel: %d\n", ret);
        exit(1);
    }
    
    size_t global_item_size = 1;
    size_t local_item_size = 1;
    ret = clEnqueueNDRangeKernel(command_queue, kernel, 1, NULL, &global_item_size, &local_item_size, 0, NULL, NULL);
    if (ret != CL_SUCCESS) {
        fprintf(stderr, "Error executing kernel: %d\n", ret);
        exit(1);
    }

    // Clean up
    ret = clFlush(command_queue);
    ret = clFinish(command_queue);
    ret = clReleaseKernel(kernel);
    ret = clReleaseProgram(program);
    ret = clReleaseCommandQueue(command_queue);
    ret = clReleaseContext(context);


    return EXIT_SUCCESS ;
}


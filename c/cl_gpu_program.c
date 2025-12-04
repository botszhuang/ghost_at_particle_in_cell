#ifndef CL_GPU_PROGRAM_C
#define CL_GPU_PROGRAM_C

#include <cl_gpu_profile_struct.h>
#include <stdio.h>
#include "hello_world_cl.h"

void get_program ( cl_gpu_profile_struct * a ){

    const char* source = (const char*)hello_world;
    size_t length = hello_world_len;

    cl_int ret = 0 ;

    a->program = clCreateProgramWithSource( a->context, 1, &source, &length, &ret);
    if (ret != CL_SUCCESS) {
        printf("Error creating program: %d\n", ret);
    }

    ret = clBuildProgram( a->program, 1, a->device_Ids , NULL, NULL, NULL);
    if (ret != CL_SUCCESS) {
        size_t log_size;
        unsigned int i = 0 ;
        clGetProgramBuildInfo( a->program , a->device_Ids [ i ] , CL_PROGRAM_BUILD_LOG, 0, NULL, &log_size);
        char* log = (char*)malloc(log_size);
        clGetProgramBuildInfo( a->program , a->device_Ids [ i ] , CL_PROGRAM_BUILD_LOG, log_size, log, NULL);
        fprintf(stderr, "%s\n", log);
        free(log);
        exit( EXIT_FAILURE );
    }
}

#endif
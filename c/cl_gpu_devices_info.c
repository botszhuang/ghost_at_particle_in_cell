#ifndef CL_GET_DEVICES_INFO_C
#define CL_GET_DEVICES_INFO_C

#include <cl_version.h>
#include <cl_gpu_profile_struct.h>
#include <cl_gpu_tool.h>
#include <c_tool.h>

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

cl_device_id * get_devices_info(  unsigned int * divce_numPtr , cl_platform_id platforms  ){

    cl_int ret = 0 ;
    cl_uint num_devices = 0 ;

    //queries GPU count
    ret = clGetDeviceIDs( platforms , CL_DEVICE_TYPE_GPU, 0, NULL, &num_devices);
    if (ret == CL_DEVICE_NOT_FOUND || num_devices == 0) {
        fprintf(stdout, "\tNo GPU devices on this platform.\n");
        return NULL ;
    } else if (ret != CL_SUCCESS) {
        fprintf(stderr, "\tError getting GPU devices: %d\n", ret);
        return NULL ;
    }    

    * divce_numPtr = num_devices ;

    // allocates a devive list
    cl_device_id * devices = malloc(sizeof(cl_device_id) * num_devices);
    if (!devices) {
        fprintf(stderr, "\tMemory allocation failed.\n");
        return NULL ;
    }
    
    // get devices' ID
    ret = clGetDeviceIDs( platforms , CL_DEVICE_TYPE_GPU, num_devices, devices, NULL);
    if (ret != CL_SUCCESS) {
        fprintf(stderr, "\tError getting GPU devices: %d\n", ret);
        free ( devices ) ;
        return NULL ;
    }

    // print devices' name
    char dname[128];
    for (cl_uint j = 0; j < num_devices; j++) {
        clGetDeviceInfo( devices[j], CL_DEVICE_NAME, sizeof(dname), dname, NULL);
        fprintf(stdout, "\tGPU Device %u: %s\n", j, dname);
    } 

    return devices ;
    
}

void get_device_ids( cl_gpu_profile_struct * g ){
    
    unsigned int i = 0 ;
    //for (  unsigned int i = 0 ; i < g->platform_id_num ; i++ ){
    get_platform_info( ( const cl_platform_id ) ( g->platform_Ids [i])  ) ;
    //}    
    
    g->device_number = 1 ;
    g->device_Ids = get_devices_info(  &g->device_number , g->platform_Ids [ i ]  ) ;

}
void free_device ( cl_gpu_profile_struct * g ){
    iffree ( g->device_Ids  );
}
#endif

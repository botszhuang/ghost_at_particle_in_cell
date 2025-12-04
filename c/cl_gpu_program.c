#ifndef CL_GPU_PROGRAM_C
#define CL_GPU_PROGRAM_C

#include <cl_gpu_profile_struct.h>
#include <cl_erro_code.h>

#include <stdio.h>
//#include "hello_world_cl.h"
//#include "leapfrog_step_cl.h"

//extern unsigned char _hello_world_cl_start[];
//extern unsigned char _leapfrog_step_cl_start[];

extern unsigned char _binary_cl_hello_world_cl_start[];
extern unsigned char _binary_cl_leapfrog_step_cl_start[];

void get_program ( cl_gpu_profile_struct * a ){

    //const char * source[] = { hello_world , leapfrog_step };
    const char * source[] = { _binary_cl_hello_world_cl_start , 
                              _binary_cl_leapfrog_step_cl_start };

    cl_int ret = 0 ;

    a->program = clCreateProgramWithSource( a->context, 1, source, NULL , &ret);
    CL_CHECK ( ret ) ;

    CL_CHECK ( clBuildProgram( a->program, 1, a->device_Ids , NULL, NULL, NULL));
    
}
void free_program ( cl_gpu_profile_struct *a ){ 
    if ( a->program ){ 
        CL_CHECK (clReleaseProgram(a->program));
    } 
}
#endif
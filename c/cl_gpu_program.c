#ifndef CL_GPU_PROGRAM_C
#define CL_GPU_PROGRAM_C

#include <cl_gpu_profile_struct.h>
#include <cl_erro_code.h>

#include <stdio.h>
#include "hello_world_cl.h"
#include "leapfrog_step_cl.h"

void get_program ( cl_gpu_profile_struct * a ){

    const char * source[] = { hello_world , leapfrog_step };

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
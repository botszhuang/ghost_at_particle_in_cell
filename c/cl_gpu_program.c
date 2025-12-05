#ifndef CL_GPU_PROGRAM_C
#define CL_GPU_PROGRAM_C

#include <cl_gpu_profile_struct.h>
#include <cl_erro_code.h>

#include <stdio.h>

//$ nm cl_h/hello_world_cl.o | grep start
//$ nm cl_h/*.o | grep start
extern const char  _binary_cl_h_hello_world_cl_o_temp_null_start [] ;
extern const char  _binary_cl_h_c_and_cl_common_o_temp_null_start []  ;
extern const char  _binary_cl_h_leapfrog_step_cl_o_temp_null_start [] ;

void get_program ( cl_gpu_profile_struct * a ){

    //const char * source[] = { hello_world , leapfrog_step };

    const char *hello_src  = _binary_cl_h_hello_world_cl_o_temp_null_start ;
    const char *common_src = _binary_cl_h_c_and_cl_common_o_temp_null_start ;
    const char *leap_src   = _binary_cl_h_leapfrog_step_cl_o_temp_null_start ;

    const char *sources[] = { hello_src , leap_src }; // Common source first for includes
    int num_sources = sizeof( sources ) / sizeof(sources[0]);
    
    cl_int ret = 0 ;

    a->program = clCreateProgramWithSource( a->context, num_sources , sources, NULL , &ret);
    CL_CHECK ( ret ) ;

    CL_CHECK ( clBuildProgram( a->program, 1, a->device_Ids , NULL, NULL, NULL));
    
}
void free_program ( cl_gpu_profile_struct *a ){ 
    if ( a->program ){ 
        CL_CHECK (clReleaseProgram(a->program));
    } 
}
#endif
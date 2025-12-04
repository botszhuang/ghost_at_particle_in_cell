#ifndef CL_GPU_KERNEL_C
#define CL_GPU_KERNEL_C

#include <cl_gpu_profile_struct.h>
#include <cl_erro_code.h>

void get_kernel ( cl_gpu_profile_struct * g ){
    
    cl_int ret = 0 ;
    g->kernel = clCreateKernel(g->program, "hello_world", &ret);
    CL_CHECK ( ret ) ;
    
}
void free_kernel ( cl_gpu_profile_struct * g ){
    if ( g->kernel ){ 
        CL_CHECK( clReleaseKernel (g->kernel) );
    }
}
#endif
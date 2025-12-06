#ifndef CL_KERNEL_LEAPFROG_STEP_C
#define CL_KERNEL_LEAPFROG_STEP_C

#include <cl_gpu_profile_struct.h>
#include <cl_erro_code.h>
#include <test_particle_type.h>

#define k ( g-> kernel_leapfrog_step )
#define kName ( "leapfrog_step" )

void get_kernel_leapfrog_step( cl_gpu_profile_struct * g ){
    
    cl_int ret = 0 ;
    k = clCreateKernel(g->program, kName, &ret);
    CL_CHECK ( ret ) ;
    
}
void free_kernel_leapfrog_step( cl_gpu_profile_struct * g ){
    if ( k ) { CL_CHECK( clReleaseKernel ( k ) ); }
}
void setArg_for_kernel_leapfrog_step ( test_particle_profile_struct * p , cl_gpu_profile_struct * g , t_type * t ) {

    clSetKernelArg( k , 0 , sizeof ( cl_mem ) , &(p->cl_x) );
    clSetKernelArg( k , 1 , sizeof ( cl_mem ) , &(p->cl_v) );
    clSetKernelArg( k , 2 , sizeof ( cl_mem ) , &(p->cl_F) );
    clSetKernelArg( k , 3 , sizeof ( cl_mem ) , &(p->cl_m) );
    clSetKernelArg( k , 4 , sizeof ( cl_mem ) , &(p->cl_q) );
    clSetKernelArg( k , 5 , sizeof (   *t   ) ,  (   t   ) );
}
void run_kernel_leapfrog_step( cl_gpu_profile_struct * g ){
    cl_uint work_dim = 1;
    size_t global_item_size = 5 ;
    size_t local_item_size = 1;
    CL_CHECK( clEnqueueNDRangeKernel( g->queue, 
                                      k , work_dim, NULL,  
                                 &global_item_size, 
                                 &local_item_size, 
                                 0, NULL, NULL));

    // Provided by CL_VERSION_1_0
    /*cl_int clEnqueueNDRangeKernel(
        cl_command_queue command_queue,
        cl_kernel kernel,
        cl_uint work_dim,
        const size_t* global_work_offset,
        const size_t* global_work_size,
        const size_t* local_work_size,
        cl_uint num_events_in_wait_list,
        const cl_event* event_wait_list,
        cl_event* event);*/                             
}
#undef kName
#undef k
#endif
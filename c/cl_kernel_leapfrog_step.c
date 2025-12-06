#ifndef CL_KERNEL_LEAPFROG_STEP_C
#define CL_KERNEL_LEAPFROG_STEP_C

#include <cl_gpu_profile_struct.h>
#include <cl_erro_code.h>
#include <test_particle_type.h>

#define k0 ( g-> kernel_leapfrog_step0 )
#define kName0 ( "leapfrog_step0" )

#define k1 ( g-> kernel_leapfrog_step1 )
#define kName1 ( "leapfrog_step1" )

const cl_uint work_dim = 1;
const size_t global_item_size = 5 ;
const size_t local_item_size = 1;

void get_kernel_leapfrog_step( cl_gpu_profile_struct * g ){

    cl_int ret = 0 ;
    #define createKernel(k,kname){\
        k = clCreateKernel(g->program, kname, &ret);\
        CL_CHECK ( ret ) ;\
    }

    createKernel ( k0, kName0 );
    createKernel ( k1, kName1 );    

    #undef CreateKernel
}
void free_kernel_leapfrog_step( cl_gpu_profile_struct * g ){
    if ( k0 ) { CL_CHECK( clReleaseKernel ( k0 ) ); }
    if ( k1 ) { CL_CHECK( clReleaseKernel ( k1 ) ); }
}
void setArg_for_kernel_leapfrog_step ( test_particle_profile_struct * p , cl_gpu_profile_struct * g , t_type * t ) {

    #define setArg(k) {\
        clSetKernelArg( k , 0 , sizeof ( cl_mem ) , &(p->cl_x) );\
        clSetKernelArg( k , 1 , sizeof ( cl_mem ) , &(p->cl_v) );\
        clSetKernelArg( k , 2 , sizeof ( cl_mem ) , &(p->cl_F) );\
        clSetKernelArg( k , 3 , sizeof ( cl_mem ) , &(p->cl_m) );\
        clSetKernelArg( k , 4 , sizeof ( cl_mem ) , &(p->cl_q) );\
        clSetKernelArg( k , 5 , sizeof (   *t   ) ,  (   t   ) );\
        clSetKernelArg( k , 6 , sizeof ( p->number ) , &( p->number ) );\
    }

    setArg ( k0 ) ;
    setArg ( k1 ) ;
    
    #undef setArg
}
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

#define launchKernel(k){\
  CL_CHECK( clEnqueueNDRangeKernel( g->queue, \
                                      k0 , work_dim, NULL,  \
                                 &global_item_size, \
                                 &local_item_size, \
                                 0, NULL, NULL));\
}        
void run_kernel_leapfrog_step0( cl_gpu_profile_struct * g ){ launchKernel(k0) ; }
void run_kernel_leapfrog_step1( cl_gpu_profile_struct * g ){ launchKernel(k1) ; }

#undef launchKernel
#undef kName
#undef k
#endif
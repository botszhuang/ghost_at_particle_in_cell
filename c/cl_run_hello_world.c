#ifndef CL_RUN_HELLO_WORLD_C
#define CL_RUN_HELLO_WORLD_C
#include <cl_gpu_profile_struct.h>
#include <cl_erro_code.h>

void run_hello_world ( cl_gpu_profile_struct * g ){
    size_t global_item_size = 1;
    size_t local_item_size = 1;
    CL_CHECK( clEnqueueNDRangeKernel( g->queue, 
                                      g->kernel, 1, NULL, 
                                 &global_item_size, 
                                 &local_item_size, 
                                 0, NULL, NULL));
}
#endif
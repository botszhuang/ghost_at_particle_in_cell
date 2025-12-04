#ifndef TEST_PARTICLE_PASS_DATA_C
#define TEST_PARTICLE_PASS_DATA_C

#include <cl_gpu_profile_struct.h>
#include <test_particle_type.h>
#include <cl_erro_code.h>

#define host_to_gpu(name) \
    CL_CHECK( clEnqueueWriteBuffer( g->queue, p->cl_##name, \
                                    CL_TRUE, \
                                    0, \
                                    p->cl_##name##_total_bytes, \
                                    p->name, \
                                    0, NULL, NULL ) )\
                                

void pX_all_from_host_to_gpu ( test_particle_profile_struct * p ,
                          cl_gpu_profile_struct * g ){
    host_to_gpu ( x ) ;
}
void pV_all_from_host_to_gpu ( test_particle_profile_struct * p ,
                          cl_gpu_profile_struct * g ){
    host_to_gpu ( v ) ;
}
void pF_all_from_host_to_gpu ( test_particle_profile_struct * p ,
                          cl_gpu_profile_struct * g ){
    host_to_gpu ( F ) ;
}
#undef host_to_gpu
#endif
#ifndef CL_GPU_PROFILE_STRUCT_H
#define CL_GPU_PROFILE_STRUCT_H

#include <cl_version.h>

typedef{
    cl_context context ;
    cl_command_queue command_queue ;
    cl_program program ;
    cl_kernel kernel ;
}cl_gpu_profile_struct;

#endif

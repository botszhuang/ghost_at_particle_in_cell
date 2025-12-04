#ifndef CL_ERROR_CODE_H
#define CL_ERROR_CODE_H

#include <cl_version.h>

#ifdef DEBUG
    const char* clGetErrorString(cl_int err);
    #define CL_CHECK(call) \
        do { \
            cl_int ret = (call); \
            if (ret != CL_SUCCESS) { \
                printf("OpenCL error %s (%d) at %s:%d\n", \
                    clGetErrorString(ret), ret, __FILE__, __LINE__); \
                exit(EXIT_FAILURE); \
            } \
        } while (0) ;
#else
    #define CL_CHECK(call) (void)(call)
#endif

#endif
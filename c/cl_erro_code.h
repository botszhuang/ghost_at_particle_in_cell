#ifndef CL_ERROR_CODE_H
#define CL_ERROR_CODE_H

#include <cl_version.h>
#include <stdio.h>

#ifdef DEBUG
    const char* clGetErrorString(cl_int ret);

    static inline void CL_CHECK_FUNC( cl_int ret, const char * file, int line ) { 
        
        if ( ret == CL_SUCCESS ) { return; }

        printf("OpenCL error %s (%d) at %s:%d\n", clGetErrorString(ret), ret, file, line);
        exit ( EXIT_FAILURE );
    }

    #define CL_CHECK(ret) CL_CHECK_FUNC((ret), __FILE__, __LINE__)
        
#else
    #define CL_CHECK(call) (void)(call)
#endif

#endif
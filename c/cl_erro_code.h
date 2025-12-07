#ifndef CL_ERROR_CODE_H
#define CL_ERROR_CODE_H

#include <cl_version.h>
#include <stdio.h>

#ifdef DEBUG

    void CL_CHECK_FUNC1(cl_int ret, const char *file, int line);
    void CL_BUILD_CHECK_sub(cl_int ret,
                        cl_program program,
                        cl_device_id device,
                        const char *file,
                        int line);

    #define CL_CHECK(ret) \
        CL_CHECK_FUNC1((ret), __FILE__, __LINE__)

    #define CL_BUILD_CHECK(ret, program, device) \
        CL_BUILD_CHECK_sub((ret), (program), (device), __FILE__, __LINE__)


#else
    #define CL_CHECK(call) (void)(call)
#endif

#endif
#ifndef CL_ERROR_CODE_H
#define CL_ERROR_CODE_H

#include <cl_version.h>
#include <stdio.h>

#ifdef DEBUG

    void CL_CHECK1_func(cl_int ret,
                             const char *file, int line);

    void CL_CHECK3_func(cl_int ret,
                             void *a,
                             void *b,
                             const char *file, int line);

    // Correct versions: only pass args, no types here.
    #define CL_CHECK1(ret) \
        CL_CHECK1_func((ret), __FILE__, __LINE__)

    #define CL_CHECK3(ret, a, b) \
        CL_CHECK3_func((ret), (a), (b), __FILE__, __LINE__)

    #define _GET_CL_CHECK(_1,_2,_3,NAME,...) NAME
    #define CL_CHECK(...) _GET_CL_CHECK(__VA_ARGS__, CL_CHECK3, dummy, CL_CHECK1)(__VA_ARGS__)

#else
    #define CL_CHECK(call) (void)(call)
#endif

#endif
#ifndef CL_GPU_CONTEXT_AND_QUEUE_C
#define CL_GPU_CONTEXT_AND_QUEUE_C
#include <stdio.h>
#include <cl_gpu_profile_struct.h>
#include <cl_erro_code.h>

void get_context_and_queue( cl_gpu_profile_struct * a ){

    cl_uint ret = 0 ;

    const unsigned int index = 0 ;

    a->context = clCreateContext(NULL, 1,&( a->device_Ids[ index ]) , NULL, NULL, &ret);
    if (ret != CL_SUCCESS) {
        fprintf(stderr, "Error creating context: %d\n", ret);
        exit( EXIT_FAILURE );
    }
    
    //#if defined(CL_VERSION_2_0)
        // OpenCL 2.0+ headers, preferred
        const cl_queue_properties props[] = { 0 };
        a->command_queue = clCreateCommandQueueWithProperties(a->context, a->device_Ids[ index ], props, &ret);
    //#else
        // OpenCL 1.2
    //    command_queue = clCreateCommandQueue(context, device_id, 0, &ret);
    //#endif
        if (ret != CL_SUCCESS) {
            fprintf(stderr, "Failed to create command queue: %d\n", ret);
            exit( EXIT_FAILURE );
        }    
}

void free_context ( cl_gpu_profile_struct * g ) { 
    CL_CHECK ( clReleaseContext(g->context) );
}
void free_queue ( cl_gpu_profile_struct * g ) { 
    CL_CHECK ( clReleaseCommandQueue(g->command_queue) ) ; }
#endif
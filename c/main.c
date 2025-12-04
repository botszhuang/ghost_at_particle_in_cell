#include <cl_gpu_tool.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

#include <c_tool.h>


int main()
{

    cl_int ret;

    cl_gpu_profile_struct * g = calloc ( 1 , sizeof ( cl_gpu_profile_struct ) )  ;   
    get_platform_number_and_ids ( g ) ;                                
    get_device_ids( g ) ;
    get_context_and_queue ( g ) ;
    get_program ( g ) ;
    get_kernel  ( g ) ;

    // Clean up
    ret = clFlush(g->command_queue);
    ret = clFinish(g->command_queue);
    free_kernel   ( g );
    free_program  ( g );
    free_queue    ( g );
    free_context  ( g );
    free_device   ( g );
    free_platform ( g );
    iffree ( g ) ;

    return EXIT_SUCCESS;
}

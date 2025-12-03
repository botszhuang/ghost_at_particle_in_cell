#include <cl_gpu_tool.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

#include "hello_world_cl.h"


int main()
{

    cl_int ret;

    cl_gpu_profile_struct * g = calloc ( 1 , sizeof ( cl_gpu_profile_struct ) )  ;   
    get_platform_number_and_ids ( g ) ;                                
    get_device_ids( g ) ;


    free ( g->device_Ids ) ;
    free ( g->platform_Ids ) ;
    free ( g ) ;

    return EXIT_SUCCESS;
}

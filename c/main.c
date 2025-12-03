#include <cl_gpu_tool.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>



int main()
{

    cl_int ret;

    cl_gpu_profile_struct * g = calloc ( 1 , sizeof ( cl_gpu_profile_struct ) )  ;   
    get_platform_number_and_ids ( g ) ;                                
    get_device_ids( g ) ;
    get_context_and_queue ( g ) ;
    get_program ( g ) ;


    if (g->device_Ids)  { free(g->device_Ids);}
    if (g->platform_Ids){ free(g->platform_Ids);}
    free ( g ) ;

    return EXIT_SUCCESS;
}

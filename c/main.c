
#include <stdlib.h>
#include <c_tool.h>
#include <c_type.h>
#include <cl_gpu_tool.h>
#include <cl_run_kernel.h>

int main(){

    cl_gpu_profile_struct * g = calloc ( 1 , sizeof ( cl_gpu_profile_struct ) )  ;   
    get_platform_number_and_ids ( g ) ;                                
    get_device_ids( g ) ;
    get_context_and_queue ( g ) ;
    get_program ( g ) ;
    get_kernel  ( g ) ;

    run_hello_world ( g ) ;
    
    test_particle_profile_struct p ;
    p.number = 100 ;

    #define mallocP(a) ( malloc( p.number * sizeof ( (a)[ 0 ] ) )) 
    p.x = mallocP( p.x ) ; 
    p.v = mallocP( p.v ) ;
    p.F = mallocP( p.F ) ;
    #undef mallocP



    iffree ( p.x );
    iffree ( p.v );
    iffree ( p.F );

    // Clean up
    flush_and_finish_queue ( g ) ;
    free_kernel   ( g );
    free_program  ( g );
    free_queue    ( g );
    free_context  ( g );
    free_device   ( g );
    free_platform ( g );
    iffree ( g ) ;

    return EXIT_SUCCESS;
}

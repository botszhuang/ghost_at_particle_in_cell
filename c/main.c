
#include <stdlib.h>

#include <c_tool.h>
#include <test_particle_run.h>

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
    
    test_particle_profile_struct * p ;

    init_test_particle_mem  ( & p ) ;
    init_test_particle_status ( p ) ;
    print_test_particle       ( p ) ;

    cl_init_test_particle_mem ( p , g );
  

    
    // write data to GPU
    host_to_gpu ( p , g , x ) ;
    host_to_gpu ( p , g , v ) ;
    host_to_gpu ( p , g , F ) ;


    // Read data from GPU
    gpu_to_host ( p , g , x ) ;
    gpu_to_host ( p , g , v ) ;
    gpu_to_host ( p , g , F ) ;


    // Clean up
    flush_and_finish_queue ( g ) ;
    free_kernel   ( g );
    free_program  ( g );
    free_queue    ( g );

    cl_free_test_particle_mem ( p );

    free_context  ( g );
    free_device   ( g );
    free_platform ( g );
    iffree ( g ) ;

    free_test_particle_mem ( p ) ;

    return EXIT_SUCCESS;
}

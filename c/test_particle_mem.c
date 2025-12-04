#ifndef TEST_PARTICLE_MEM_C
#define TEST_PARTICLE_MEM_C
#include <c_tool.h>
#include <test_particle_type.h>
#include <cl_gpu_profile_struct.h>

void init_test_particle_mem ( test_particle_profile_struct ** pPtr ){

    * pPtr = calloc ( 1 , sizeof ( * pPtr[0] ) ) ;
    test_particle_profile_struct * p = * pPtr ;
   
    p->number = 100 ;

    #define mallocP(a) ( malloc( p->number * sizeof ( (a)[ 0 ] ) )) 
    
    p->x = mallocP( p->x ) ; 
    p->v = mallocP( p->v ) ;
    p->F = mallocP( p->F ) ;
    
    #undef mallocP
}

void free_test_particle_mem ( test_particle_profile_struct * p ){
    iffree ( p->x );
    iffree ( p->v );
    iffree ( p->F ); 
    iffree ( p ) ;
}

void cl_init_test_particle_mem ( test_particle_profile_struct * p , cl_gpu_profile_struct * g ){

    cl_int ret = 0 ;

    #define createBuffer(cl_x,cl_x_bit,x){\
        cl_x_bit = p->number * sizeof ( cl_3D_struct ) ;\
        cl_x = clCreateBuffer(\
                    g->context,\
                    CL_MEM_READ_WRITE,\
                    cl_x_bit ,\
                    ( void* ) x  ,\
                    &ret );\
    }

    createBuffer ( (p->cl_x) , (p->cl_x_total_bit), (p->x) ) ;
    createBuffer ( (p->cl_v) , (p->cl_v_total_bit), (p->v) ) ;
    createBuffer ( (p->cl_F) , (p->cl_F_total_bit), (p->F) ) ;

    #undef createBuffer
}

#endif
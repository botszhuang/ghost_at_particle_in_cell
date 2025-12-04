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

    #define createBuffer(name){\
        p->cl_##name##_total_bytes = p->number * sizeof ( cl_3D_struct ) ;\
        p->cl_##name = clCreateBuffer(\
                    g->context,\
                    CL_MEM_READ_WRITE,\
                    p->cl_##name##_total_bytes ,\
                    ( void* ) p->name  ,\
                    &ret );\
    }

    createBuffer ( x ) ;
    createBuffer ( v ) ;
    createBuffer ( F ) ;

    #undef createBuffer
}
void cl_free_test_particle_mem ( test_particle_profile_struct * p  ){

    #define cl_iffree(a) if (a) { clReleaseMemObject(a); a = NULL; }
        
        cl_iffree ( p->cl_x ) ;
        cl_iffree ( p->cl_v ) ;
        cl_iffree ( p->cl_F ) ; 

    #undef cl_iffree
}

#endif
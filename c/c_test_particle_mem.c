#ifndef C_TEST_PARTICLE_MEM_C
#define C_TEST_PARTICLE_MEM_C
#include <c_tool.h>
#include <c_type.h>

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

#endif
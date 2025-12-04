#ifndef TEST_PARTICLE_INIT_C
#define TEST_PARTICLE_INIT_C
#include <c_tool.h>
#include <test_particle_type.h>

void init_test_particle_status ( test_particle_profile_struct * p ){

    const typeof( (p->number) ) num = p->number ;

    for ( unsigned int i = 0 ; i < num ; i++ ) {
        p->x[i] =  ( x_dimension ) { 1,  2, 3 } ;
        //p->v[i] = ( v_dimension ) { 20, 21, 22 } ;
        //p->F[i] = ( F_dimension ) { 30, 31, 32 } ;
    }
 
}

#endif
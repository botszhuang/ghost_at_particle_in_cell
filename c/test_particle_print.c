#ifndef TEST_PARTICLE_PRINT_C
#define TEST_PARTICLE_PRINT_C
#include <stdio.h>
#include <c_tool.h>
#include <test_particle_type.h>

void print_test_particle ( test_particle_profile_struct * p ){

    const typeof( (p->number) ) num = p->number ;


    #define X (p->x[i])
    #define V (p->v[i])
    #define F (p->F[i])

    for ( unsigned int i = 0 ; i < num ; i++ ) {
        printf( "[%i]\n", i );
        printf("  x"); x_dim_printf ( X , i ) ;
        printf("  v"); v_dim_printf ( V , i ) ;
        printf("  F"); F_dim_printf ( F , i ) ;
        printf( "  m=%.2lf\n  q=%.2lf\n", p->m[i], p->q[i] );
    }

    #undef X
    #undef V
    #undef F
 
}

#endif
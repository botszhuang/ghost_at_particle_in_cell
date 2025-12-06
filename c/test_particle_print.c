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
        fprintf( stdout, "\t%i) ", i );
        fprintf( stdout, "\t%.2lf %.2lf %.2lf ,", X.x, X.y, X.z);
        fprintf( stdout, "\t%.2lf %.2lf %.2lf ,", V.x, V.y, V.z);
        fprintf( stdout, "\t%.2lf %.2lf %.2lf ,", F.x, F.y, F.z);
        fprintf( stdout, "\t%.2lf %.2lf\n", p->m[i], p->q[i] );
    }

    #undef X
    #undef V
    #undef F
 
}

#endif
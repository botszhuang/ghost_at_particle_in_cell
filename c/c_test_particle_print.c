#ifndef C_TEST_PARTICLE_PRINT_C
#define C_TEST_PARTICLE_PRINT_C
#include <stdio.h>
#include <c_tool.h>
#include <c_type.h>

void print_test_particle ( test_particle_profile_struct * p ){

    const typeof( (p->number) ) num = p->number ;


    #define X (p->x[i])
    #define V (p->v[i])
    #define F (p->F[i])

    for ( unsigned int i = 0 ; i < num ; i++ ) {
        fprintf( stdout, "\t%i) %lf %lf %lf , %lf %lf %lf, %lf %lf %lf\n",
            i, 
            X.x, X.y, X.z,
            V.x, V.y, V.z,
            F.x, F.y, F.z );
    }

    #undef X
    #undef V
    #undef F
 
}

#endif
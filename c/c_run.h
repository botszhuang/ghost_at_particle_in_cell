#ifndef C_RUN_H
#define C_RUN_H

#include <test_particle_type.h>
void init_test_particle_mem ( test_particle_profile_struct ** pPtr ) ;
void free_test_particle_mem ( test_particle_profile_struct * p ) ;

void init_test_particle_status ( test_particle_profile_struct * p );
void print_test_particle ( test_particle_profile_struct * p );

#endif
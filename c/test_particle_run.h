#ifndef TEST_PARTICLE_RUN_H
#define TEST_PARTICLE_RUN_H

#include <cl_gpu_profile_struct.h>
#include <test_particle_type.h>

void init_test_particle_mem ( test_particle_profile_struct ** pPtr ) ;
void free_test_particle_mem ( test_particle_profile_struct * p ) ;

void init_test_particle_status ( test_particle_profile_struct * p );
void print_test_particle ( test_particle_profile_struct * p );

void cl_init_test_particle_mem ( test_particle_profile_struct * p , cl_gpu_profile_struct * g );
void cl_free_test_particle_mem ( test_particle_profile_struct * p  );


void pX_all_from_host_to_gpu ( test_particle_profile_struct * p , cl_gpu_profile_struct * g ) ;
void pV_all_from_host_to_gpu ( test_particle_profile_struct * p , cl_gpu_profile_struct * g ) ;
void pF_all_from_host_to_gpu ( test_particle_profile_struct * p , cl_gpu_profile_struct * g ) ;
#endif
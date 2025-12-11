#ifndef READ_DATA_H
#define READ_DATA_H

#include <cell_type.h>
#include <test_particle_type.h>

void read_x_dim_CSV ( const char * filename , x_dim ** lflf_array , unsigned int * lflf_size ) ;
void read_3int_CSV  ( const char * filename , triangleStruct ** int3_array   , unsigned int * int3_size ) ;

#endif
#ifndef C_DEFINE_H
#define C_DEFINE_H

#include <c_dimension_struct.h>

#define x_dimension c_3D_struct
#define v_dimension c_3D_struct
#define F_dimension c_3D_struct

typedef struct{
  unsigned int number ;  
  x_dimension * x ;
  v_dimension * v ;
  F_dimension * F ;
} test_particle_profile_struct ;

#endif
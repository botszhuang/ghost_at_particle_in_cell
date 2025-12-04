#ifndef C_DEFINE_H
#define C_DEFINE_H

#include <cl_version.h>
#include <dimension_struct.h>

#define x_dimension c_3D_struct
#define v_dimension c_3D_struct
#define F_dimension c_3D_struct

#define cl_x_dimension cl_3D_struct
#define cl_y_dimension cl_3D_struct
#define cl_z_dimension cl_3D_struct

typedef struct{
  
  unsigned int number ;  

  x_dimension * x ;
  v_dimension * v ;
  F_dimension * F ;

  cl_mem cl_x ;
  cl_mem cl_v ;
  cl_mem cl_F ;

  unsigned int cl_x_total_bytes ;
  unsigned int cl_v_total_bytes ;
  unsigned int cl_F_total_bytes ;

} test_particle_profile_struct ;



#endif
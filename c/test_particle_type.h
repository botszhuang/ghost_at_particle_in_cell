#ifndef C_DEFINE_H
#define C_DEFINE_H

#include <cl_version.h>
#include <c_and_cl_common.h>

typedef struct{
  
  unsigned int number ;  

  x_dim * x ;
  v_dim * v ;
  F_dim * F ;

  cl_mem cl_x ;
  cl_mem cl_v ;
  cl_mem cl_F ;

  unsigned int cl_x_total_bytes ;
  unsigned int cl_v_total_bytes ;
  unsigned int cl_F_total_bytes ;

} test_particle_profile_struct ;



#endif
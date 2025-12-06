#ifndef CELL_TYPE_H
#define CELL_TYPE_H

#include <cl_version.h>
#include <c_and_cl_common.h>

typedef struct{
  
  unsigned int    cellSize ;  
  unsigned int  * cell  ;
  unsigned int    cellArrayLength ; //  cellArratLength = cellSize * 3

  unsigned int nodeSize ;
  x_dim * node ;
 
} cell_profile_struct ;

#endif
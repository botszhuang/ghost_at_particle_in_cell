#ifndef C_DIMENSION_STRUCT_H
#define C_DIMENSION_STRUCT_H
#include <stdlib.h>
#include <cl_version.h>

typedef struct {
    double x, y, z ;
}c_3D_struct;

typedef struct {
    cl_double x, y, z ;
}cl_3D_struct;


typedef struct {
    double x, y ;
}c_2D_struct;

typedef struct {
    cl_double x, y, z ;
}cl_2D_struct;


#endif
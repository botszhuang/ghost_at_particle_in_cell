#ifndef CELL_READ_C
#define CELL_READ_C

#include <cell_type.h>
#include <read_data.h>

#define fNodeFile  "nodes.csv"
#define fCellFile  "triangles.csv"

void read_node ( cell_profile_struct * c ) {
    read_x_dim_CSV ( fNodeFile , &( c->node ) , &( c->nodeSize ) ) ;
}
void read_cell ( cell_profile_struct * c ) {
    read_3int_CSV ( fCellFile , (triangleStruct **)&( c->cell ) , &( c->cellSize ) ) ;
}

#undef fNodeFile
#undef fCellFile

#endif
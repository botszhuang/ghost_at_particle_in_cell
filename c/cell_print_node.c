#ifndef CELL_PRINT_NODE_C
#define CELL_PRINT_NODE_C

#include <stdio.h>
#include <cell_type.h>

void print_node_in_cell ( cell_profile_struct * c ) {

    for ( unsigned int i = 0 ; i < c->nodeSize ; i++ ) {
        #define X (c->node[i])
        printf ("node [%i] ( %.6lf, %.6lf, %.6lf )\n", 
            i , X.x , X.y , X.z ) ;
    }

}

#endif
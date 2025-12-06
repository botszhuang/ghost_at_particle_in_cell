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

void print_cell_array ( cell_profile_struct * c ){

    for ( unsigned int i = 0 ; i < c->cellArrayLength ; i++ ) {
        printf ("cell [%i] ( %d )\n", i , c->cell[i] ) ;
    }
   
}
void print_node_index_of_cell ( cell_profile_struct * c ) {

    for ( unsigned int i = 0 ; i < c->cellSize ; i++ ) {

        #define N0 (c->cell[ 3*i    ])
        #define N1 (c->cell[ 3*i +1 ])
        #define N2 (c->cell[ 3*i +2 ])
        printf ("cell [%i] ( %d, %d, %d )\n", 
            i , N0 , N1 , N2 ) ;
    }

}
#endif
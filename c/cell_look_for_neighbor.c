#ifndef CELL_LOOK_FOR_NEIGHBOR_C
#define CELL_LOOK_FOR_NEIGHBOR_C

#include <stdbool.h>
#include <string.h>
#include <cell_type.h>

void cell_look_for_neighbor ( cell_profile_struct * c ) {
 
    cellNeighborType * cellNeighbors ;
    cellNeighbors = calloc ( 30 , cellNeighbors [ 0 ] ) ;

    cellNeighborType cellNeighborArray [ 10 ] ;

    triangleStruct host ;
    triangleStruct guest ;
    bool match = true ;
    const typeof ( c->cellSize ) cellSize = c->cellSize ;

    unsigned int counter = 0 ;
    for ( typeof ( c->cellSize ) hi = 0 ; hi < 1 ; hi++ ) {
        host = c->cell [ hi ] ;
        for ( typeof ( c->cellSize ) i = 0; i < cellSize ; i++) {
            guest = c->cell [ hi ] ;

            match =  ( host.x == guest.x ) | ( host.y == guest.x ) 
                   | ( host.z == guest.x ) | ( host.x == guest.y )
                   | ( host.y == guest.y ) | ( host.z == guest.y ) 
                   | ( host.x == guest.z ) | ( host.y == guest.z ) 
                   | ( host.z == guest.z )  ;

            if ( match ) {  cellNeighbors [ counter++ ] ; }

        }
        
        
    }

}



#endif
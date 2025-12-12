#ifndef CELL_LOOK_FOR_NEIGHBOR_C
#define CELL_LOOK_FOR_NEIGHBOR_C

#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <cell_type.h>

void cell_look_for_neighbor ( cell_profile_struct * c ) {
 
    cellNeighborType * cellNeighbors ;
    cellNeighbors = calloc ( 30 , sizeof (  cellNeighbors [ 0 ] )) ;

    cellNeighborType cellNeighborArray [ 10 ] ;

    triangleStruct host ;
    triangleStruct guest ;
    bool match = true ;
    const typeof ( c->cellSize ) cellSize = c->cellSize ;
    const typeof ( c->nodeSize ) nodeSize = c->nodeSize ;
    unsigned int a  [  nodeSize  ] [ 10 ] ;
    unsigned int a_counter [ nodeSize ] ;
    for ( size_t i = 0 ; i < nodeSize ; i++){
    for ( size_t j = 0 ; j < 10 ; j ++ ){
        a [ i ] [ j ] = 0 ; 
    }}
    for ( size_t i = 0 ; i < nodeSize ; i++){
        a_counter [ i ] = 0 ;
    }   
    

    unsigned int counter = 0 ;
    for ( typeof ( c->cellSize ) hi = 0 ; hi < cellSize ; hi++ ) {
        
        host = c->cell [ hi ] ;
        a [ host.x ] [ a_counter [ host.x ] ] = hi ; ( a_counter [ host.x ] )++ ;
        a [ host.y ] [ a_counter [ host.y ] ] = hi ; ( a_counter [ host.y ] )++ ;
        a [ host.z ] [ a_counter [ host.z ] ] = hi ; ( a_counter [ host.z ] )++ ;
        
    }

    for (  unsigned int i = 0 ; i < nodeSize ; i++ ) {
        printf ( "vertex [%3i] %i: " , i , a_counter [ i ] ) ;
        for ( unsigned int j = 0 ; j < a_counter [ i ] ; j++ ) {
            printf ( "%6i", a [ i ] [ j ] ) ;
        }
        puts("") ;
    }

    unsigned int * index ;
    unsigned int sizeofIndex = sizeof ( unsigned int ) ;
    index = calloc ( c->nodeSize +1 , sizeofIndex ) ;

    for ( unsigned int i = 0 ; i < nodeSize ; i++ ) {  
        index [ i +1 ] = index [ i ] + a_counter [ i ] ; 
    }
    
    unsigned int * indexList = calloc ( index [ c->nodeSize ] , sizeofIndex ) ;
    for ( unsigned int i = 0 ; i < c->nodeSize; i ++ ) {
        memcpy  (  indexList + index [ i ]  , a [ i ] , a_counter [ i ] * sizeofIndex ) ;
    }

    unsigned int cc = 0 ;
    unsigned int istart , iend ;
    for ( unsigned int i = 0 ; i < c->nodeSize ; i++ ) {
        istart = index [ i ] ;
        iend   = index [ i + 1 ] ;
        printf ( "List node[%5i] %5i %5i" , i , istart , iend ) ;
        for ( unsigned int j = istart ; j < iend ; j++ ) {
            printf ( "%6i", indexList [ j ] ) ;
        }
        puts("");
    }

}



#endif
#ifndef CELL_READ_NODE_C
#define CELL_READ_NODE_C

#include <stdio.h>
#include <cl_erro_code.h>
#include <c_tool.h>
#include <cell_type.h>
#include <cl_gpu_profile_struct.h>

#define fNodeFile  "nodes.txt"
#define fCellFile  "elements.txt"

#define rellocation(p,pSize,counter,extra, tmp) {\
    if ( counter == pSize ) {\
        pSize += extra ;\
        tmp = realloc( p, pSize * sizeof( p[0] ) );\
        if (!tmp) {\
            printf ( "realloc failed %s, %d" , __FILE__ , __LINE__  );\
            iffree(p);  \
            fclose(fp);\
            exit(EXIT_FAILURE);\
    }\
    p = tmp ;    \
    }\
}
#define skipTheHead(fp){\
    char header[100];\
    fgets(header, sizeof(header), fp);  \
}
#define checkCellNode(a) {\
    if (!a) {\
        printf("realloc failed for ##a @ %s %d", __FILE__, __LINE__ );\
        iffree(a);\
        iffree(c);\
        exit(EXIT_FAILURE);\
    }\
}
#define openF(fp, fn) {\
    fp = fopen(fn, "r");\
    if (!fp) {\
        printf("Error opening file %s at %s, line %d\n", fNodeFile, __FILE__, __LINE__);\
        exit(EXIT_FAILURE);\
    }\
}

void read_node ( cell_profile_struct * c ) {

    printf ( "reading %s ...\n", fNodeFile ) ;

    FILE * fp ;
    openF( fp , fNodeFile ) ;
    skipTheHead( fp );

    // reading the data from text file
    unsigned int ListSize = 30 ;
    x_dim * List0 = malloc ( ListSize * sizeof( List0 [0] ) )  ;
    x_dim X ;
    unsigned int counter = 0  ;
    while ( fscanf ( fp , "%lf %lf", &X.x, &X.y ) == 2) {
        X.z = 0 ;
        List0 [ counter ] = X ;
        counter ++ ;
        x_dim * tmp ;
        rellocation( List0 , ListSize , counter , 100 , tmp ) ;
    }

    fclose ( fp );

    // update cell's profile
    c->nodeSize = counter ;
    c->node = realloc ( List0 , c->nodeSize * sizeof ( c->node [0] ) ) ;
    checkCellNode(c->node) ;

}

void read_cell ( cell_profile_struct * c ) {

    printf ( "reading %s ...\n", fCellFile ) ;

    FILE * fp ;
    openF( fp , fCellFile ) ;
    skipTheHead( fp );

    unsigned int ListSize  = 10 *3  ;
    unsigned int * List = calloc ( 30 , sizeof ( List [0] ) ) ;

    // reading the data from text file
    unsigned int X0 , X1 , X2 ;
    unsigned int counter = 0  ;
    while ( fscanf ( fp , "%d %d %d", &X0 , &X1 , &X2 ) == 3) {    
        List [  counter     ] = X0 ;  
        List [  counter +1  ] = X1 ;  
        List [  counter +2  ] = X2 ;
        counter +=3 ;  
        unsigned int * tmp ;
        rellocation( List , ListSize , counter , 100*3 , tmp ) ;
    }

    fclose ( fp );

    // update cell's profile
    c->cellArrayLength = counter ;
    c->cellSize = c->cellArrayLength / 3 ;
    c->cell = realloc( List , c->cellArrayLength * sizeof( c->cell [0] ));  // Final reallocation for cells
    checkCellNode(c->cell);  // Check if reallocation succeeded

}

#undef openF
#undef checkCellNode 
#undef rellocation
#undef skipTheHead
#undef fNodeFile

void free_cell_profile ( cell_profile_struct *c ) { 
    iffree ( c->node ) ;
    iffree ( c->cell ) ; 
    iffree ( c ) ;
}

void cl_cell_mem_init ( cell_profile_struct * c , 
                        cl_gpu_profile_struct * g ){

    cl_int ret = 0 ;

    c->cl_node_total_bytes = c->nodeSize * sizeof ( c->node [0] ) ;
    c->cl_cell_total_bytes = c->cellArrayLength * sizeof ( c->cell [0] ) ;

    #define createBuffer(name){\
        c->cl_##name = clCreateBuffer(\
                    g->context,\
                    CL_MEM_READ_WRITE,\
                    c->cl_##name##_total_bytes ,\
                    NULL  ,\
                    &ret );\
    }

    createBuffer ( node ) ;   CL_CHECK ( ret );
    createBuffer ( cell ) ;   CL_CHECK ( ret );
   
    #undef createBuffer
}

#endif
#ifndef CELL_READ_NODE_C
#define CELL_READ_NODE_C

#include <stdio.h>
#include <c_tool.h>
#include <cell_type.h>

#define fNodeFile  "nodes.txt"
#define fCellFile  "elements.txt"

#define rellocation(p,pSize,counter) {\
    if ( counter == pSize ) {\
        pSize += 100 ;\
        x_dim * tmp = realloc( p, pSize * sizeof( p[0] ) );\
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
        rellocation( List0 , ListSize , counter ) ;

    }
    
    fclose ( fp );

    // update cell's profile
    c->nodeSize = counter ;
    c->node = realloc ( List0 , c->nodeSize * sizeof ( c->node [0] ) ) ;
    checkCellNode(c->node) ;

}

#undef openF
#undef checkCellNode 
#undef rellocation
#undef skipTheHead
#undef fNodeFile

#endif
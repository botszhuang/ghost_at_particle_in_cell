#ifndef READ_NODE_C
#define READ_NODE_C

#include <stdio.h>
#include <cl_erro_code.h>
#include <c_tool.h>
#include <c_and_cl_common.h>
#include <cl_gpu_profile_struct.h>
#include <string.h>


#define checkRelocate(a) {\
    if (!a) {\
        printf("realloc failed for ##a @ %s %d", __FILE__, __LINE__ );\
        iffree(a);\
        exit(EXIT_FAILURE);\
    }\
}

static inline void examfopen(FILE *fp, const char *fn){
        if (!fp) {
        printf("Error opening file %s at func:%s at %s, line %d\n", fn, __func__ , __FILE__, __LINE__);
        exit(EXIT_FAILURE);
    }
}
static inline void skipCSVhead( FILE * fp ) {
    char header[200];
    fgets(header, sizeof(header), fp);
}
static inline unsigned int rellocation_func ( void ** p , size_t pSize, const size_t counter ,  const size_t element_size ) {
    if ( counter < pSize ) { return pSize ; }
    
        pSize += 100 ;
        void * tmp = realloc( *p, ( pSize * element_size ) );
        if ( ! tmp ) {\
            printf ( "realloc failed %s, %d" , __FILE__ , __LINE__  );
            iffree(p);  
            exit(EXIT_FAILURE);
        }
         * p = tmp ;
        return pSize ;
    
}

void read_x_dim_CSV ( const char * filename , x_dim ** lflf_array , unsigned int * lflf_size ) {

    printf ( "reading %s ...\n", filename ) ;

    FILE * fp = fopen( filename , "r");
    examfopen( fp , filename ) ;
    skipCSVhead( fp );

    // reading CSV file
    x_dim X ;
    const unsigned int sizeofElement = sizeof( X ) ;
    unsigned int ListSize = 30 ;
    x_dim * List0 = malloc ( ListSize * sizeofElement  )  ;
    unsigned int counter = 0  ;
    
    while ( fscanf ( fp , "%lf,%lf", &X.x, &X.y ) == 2) {
        //ist0 [ counter ] = X ;
        memcpy( List0 + counter , &X , sizeofElement );
        counter ++ ;
        ListSize = rellocation_func( (void **)&List0 , ListSize , counter , sizeofElement ) ;
    }
    // end of reading CSV file

    fclose ( fp );

    // update output
    *lflf_size  = counter ;
    *lflf_array = realloc ( List0 , counter * sizeofElement ) ;
    checkRelocate( lflf_array ) ;

}
void read_3int_CSV  ( const char * filename , triangleStruct ** int3_array   , unsigned int * int3_size ) {

    printf ( "reading %s ...\n", filename ) ;

    FILE * fp = fopen( filename , "r");
    examfopen( fp , filename ) ;
    skipCSVhead( fp );  

    // reading CSV file
    triangleStruct X ;
    const unsigned int sizeofElement = sizeof( X ) ;
    unsigned int ListSize = 30 ;
    triangleStruct * List0 = malloc ( ListSize * sizeofElement  )  ;
    unsigned int counter = 0  ;
    
    while ( fscanf ( fp , "%d,%d,%d", &X.x, &X.y, &X.z ) == 3) {
        memcpy( List0 + counter , &X , sizeofElement );
        //memcpy List0 [ counter ] = X ;
        counter ++ ;
        ListSize = rellocation_func( (void **)&List0 , ListSize , counter , sizeofElement ) ;
    }
    // end of reading CSV file

    fclose ( fp );

    // update output
    *int3_size  = counter ;
    *int3_array = realloc ( List0 , counter * sizeofElement ) ;
    checkRelocate( int3_array ) ;

}


#endif
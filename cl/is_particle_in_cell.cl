#define geometric_vector(p,v1,v2) ( cross((v2-v1), (p-v1)) )

__kernel void is_particle_in_cell(
    __global node_type *  nodePtr
  , unsigned int          nodeSize
  , __global cell_type *  cellPtr
  , unsigned int          cellSize
  , __global x_dim *      particle
  , unsigned int          particleSize
){
    const int gid = get_global_id(0);
    const int gid_size = get_global_size(0);
 
    unsigned int cell_index = 0 ;
    cell_type n1, n2, n3 ;

    for ( unsigned int i = gid ; i < cellSize ; i += gid_size  ){

      cell_index = i * 3 ; 
      n1 = cellPtr [ cell_index ] ;
      n2 = cellPtr [ cell_index +1 ] ;
      n3 = cellPtr [ cell_index +2 ] ;
      printf ( "%i) %d %d %d\n" ,  i , n1 , n2 , n3  ) ;

    }

    x_dim X ;
    for ( unsigned int i = gid ; i < nodeSize ; i += gid_size  ){

      X = nodePtr [ i ] ;
      printf ( "g, node %i) %.3lf %.3lf %.3lf\n" ,  i , X.x , X.y , X.z  ) ;

    }
    

    x_dim p ;
    x_dim A , B , C ;
    x_dim c1 , c2 , c3 , N ;
    double s1 , s2 , s3 ;

    // get a triangle & its nodes' index
    //unsigned int 
    cell_index = 0 ; 
    n1 = cellPtr [ cell_index    ] ;
    n2 = cellPtr [ cell_index +1 ] ;
    n3 = cellPtr [ cell_index +2 ] ;

    for ( unsigned int i = gid ; i < particleSize ; i += gid_size  ){

      p = particle [ i ] ;

      // get the nodes' position ( x, y, z ) for the index of node
      A = nodePtr [ n1 ] ;
      B = nodePtr [ n2 ] ;
      C = nodePtr [ n3 ] ;

      N  = cross ( ( B - A ) , ( C - A ) ) ;
      c1 = cross ( ( B - A ) , ( p - A ) ) ;
      c2 = cross ( ( C - B ) , ( p - B ) ) ;
      c3 = cross ( ( A - C ) , ( p - C ) ) ;
      
      s1 = dot ( c1 , N ) ; 
      s2 = dot ( c2 , N ) ; 
      s3 = dot ( c3 , N ) ; 

      printf ( "[%2i] cell: %.2lf %.2lf %.2lf\t%.2lf %.2lf %.2lf\t%.2lf %.2lf %.2lf\t particle: %.2lf %.2lf %.2lf\n" , 
       i, A.x , A.y , A.z, 
       B.x , B.y , B.z , 
       C.x , C.y , C.z ,
       p.x , p.y , p.z ) ;


    }

}
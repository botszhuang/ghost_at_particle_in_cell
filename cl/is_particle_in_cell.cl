
#define CROSS2(a,b) (((a).x)*((b).y) - (((a).y)*((b).x))) // z-component of 2D cross
#define getCellNodesPosition(A,B,C,ci){\
      /* get a triangle & its nodes' index*/\
      cell_index = ci * 3 ; \
      n1 = cellPtr [ cell_index    ] ;\
      n2 = cellPtr [ cell_index +1 ] ;\
      n3 = cellPtr [ cell_index +2 ] ;\
      /* get the nodes' position ( x, y, z ) for the index of node*/\
      A = nodePtr [ n1 ] ; \
      B = nodePtr [ n2 ] ; \
      C = nodePtr [ n3 ] ; \
}
inline bool point_in_triangle ( double2 A, double2 B, double2 C, double2 P ) {
    
    double2 v , p;
/*
    double2 AB = B - A;
    double2 BC = C - B;
    double2 CA = A - C;

    double2 AP = P - A;
    double2 BP = P - B;
    double2 CP = P - C;
*/
    v = B - A ;
    p = P - A ;
    double z1 = CROSS2( v , p );

    v = C - B ;
    p = P - B ;
    double z2 = CROSS2( v , p );

    v = A - C ;
    p = P - C ;
    double z3 = CROSS2( v , p );


    // Inside if all cross products have the same sign (or zero)
    // 1 -> true  -> P is inside the triangle
    // 0 -> false -> P is outside the triangle
    return ((z1 >= 0.0f && z2 >= 0.0f && z3 >= 0.0f) || // true
            (z1 <= 0.0f && z2 <= 0.0f && z3 <= 0.0f));  // false
            
}

__kernel void is_particle_in_cell(
    __global node_type *  nodePtr
  , unsigned int          nodeSize
  , __global cell_type *  cellPtr
  , unsigned int          cellSize
  , __global x_dim *      particle
  , unsigned int          particleSize
  , __global cell_index_type * cell_index_of_p_Ptr
){
    const int gid0 = get_global_id(0);
    const int gid1 = get_global_id(1);

    const int gid0_size = get_global_size(0);
    const int gid1_size = get_global_size(1);

    /*These are required variables for getCellNodesPosition() */
    unsigned int cell_index = 0 ;
    cell_type n1, n2, n3 ;

   /*for ( unsigned int i = gid ; i < cellSize ; i += gid_size  ){

      cell_index = i * 3 ; 
      n1 = cellPtr [ cell_index ] ;
      n2 = cellPtr [ cell_index +1 ] ;
      n3 = cellPtr [ cell_index +2 ] ;
      printf ( "g, %i) %d %d %d\n" ,  i , n1 , n2 , n3  ) ;

    }*/

    /*x_dim X ;
    for ( unsigned int i = gid ; i < nodeSize ; i += gid_size  ){

      X = nodePtr [ i ] ;
      printf ( "g, node %i) %.3lf %.3lf \n" ,  i , X.x , X.y ) ;

    }*/
    

    x_dim A , B , C ; // vortex of traingle
    x_dim P ; // point
    bool y ;
    for ( unsigned int ci = gid1 ; ci < cellSize ; ci += gid1_size  ) {
      
      getCellNodesPosition ( A , B , C , ci );

      for ( unsigned int pi = gid0 ; pi < particleSize ; pi += gid0_size  ){

        P = particle [ pi ] ;

        y = point_in_triangle ( A , B , C , P ) ;
        if ( y ) { printf ( "p[%i] is inside cell[%i]\n"  , pi , ci ) ; }
            else { printf ( "p[%i] is outside cell[%i]\n" , pi , ci ) ; }
      }
    }

}
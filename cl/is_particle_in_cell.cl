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
    cell_type v1, v2, v3 ;

    for ( unsigned int i = gid ; i < cellSize ; i += gid_size  ){

      cell_index = i * 3 ; 
      v1 = cellPtr [ cell_index ] ;
      v2 = cellPtr [ cell_index +1 ] ;
      v3 = cellPtr [ cell_index +2 ] ;
      printf ( "%i) %d %d %d\n" ,  i , v1 , v2 , v3  ) ;

    }

}
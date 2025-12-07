__kernel void is_particle_in_cell(
    __global node_type *  nodePtr
  , unsigned int          nodeSize
  , __global cell_type *  cellPtr
  , unsigned int          cellSize
){
    const int gid = get_global_id(0);

}
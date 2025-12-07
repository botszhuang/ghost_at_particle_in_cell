__kernel void is_particle_in_cell(
    __global node_type *  nodePtr
  , unsigned int          nodeSize
  , __global cell_type *  cellPtr
  , unsigned int          cellSize
  , __global x_dim *      particle
  , unsigned int          particleSize
){
    const int gid = get_global_id(0);

}
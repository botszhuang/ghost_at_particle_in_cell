#ifndef CELL_RUN_H
#define CELL_RUN_H

#include <cell_type.h>

void read_node ( cell_profile_struct * c ) ;
void read_cell ( cell_profile_struct * c ) ;

void print_node_in_cell       ( cell_profile_struct * c ) ;
void print_node_index_of_cell ( cell_profile_struct * c ) ;
void print_cell_array         ( cell_profile_struct * c ) ;

#endif
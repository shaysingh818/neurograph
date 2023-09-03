#ifndef COMPUTATION_GRAPH_H
#define COMPUTATION_GRAPH_H

#include "value.h"

struct ComputationGraph {
    int size, curr_index;  
    double base_gradient; 
    value_t **operations; 
}; 

typedef struct ComputationGraph computation_graph_t;


/* create computation graph */
computation_graph_t *create_graph(int set_size, double set_gradient); 

/* Append operation */
void append_op(computation_graph_t *graph, value_t *val); 

/* forward all */
void forward_nodes(computation_graph_t *graph); 

/* backward all */
void backward_nodes(computation_graph_t *graph); 


#endif
#ifndef COMPUTATION_H
#define COMPUTATION_H

#include "graph.h"


/* improved graph structure for the future */
struct ComputationGraph {
    int curr_node_count;
    double base_derivative; 
	graph_t *graph; 
};

typedef struct ComputationGraph computation_graph_t;


/* computation graph node */
node_t *value(void *value); 

/* create instance of graph */
computation_graph_t *computation_graph(double base_deriv);

/* utilities for adding nodes */
void add_variable(graph_t *g, node_t *var); 
void add_operation(graph_t *g, node_t *var);

/* debugging methods */
void print_value(node_t *val);

#endif
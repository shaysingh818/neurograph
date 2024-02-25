#ifndef COMPUTATION_H
#define COMPUTATION_H

#include <math.h>
#include "graph.h"
#include <data_structures/ndarray/includes/ndarray.h>
#include <data_structures/ndarray/includes/ops.h>
#include <data_structures/node/includes/scalar.h>

/* improved graph structure for the future */
struct ComputationGraph {
    int curr_node_count, curr_node_id;
    double base_derivative; 
    bool status; 
	graph_t *graph;
};

typedef struct ComputationGraph computation_graph_t;


/* computation graph node */
node_t *variable(computation_graph_t *g, void *value);

/* create instance of graph */
computation_graph_t *computation_graph(double base_deriv);

/* utilities for adding nodes */
void add_variable(computation_graph_t *g, node_t *operation, node_t *input); 

/* evaulate all operations in the graph */
void forward_evaluate(computation_graph_t *g, node_t *output);

/* debugging methods */
void print_computation_graph(computation_graph_t *g);

#endif
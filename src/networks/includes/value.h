#ifndef VALUE_H
#define VALUE_H

#define FALSE 0
#define TRUE 1

#include "../../data_structures/includes/matrix.h"

struct NodeValue {
    double output;  
    double upstream_gradient;
    double x_d_gradient, y_d_gradient;
    struct NodeValue *left, *right;  
	void(*forward_operation)(struct NodeValue *val); 
	void(*backward_operation)(struct NodeValue *val); 
}; 

typedef struct NodeValue node_value_t;


struct ComputationGraph {
    int size, curr_index;  
    double base_gradient; 
    node_value_t **operations; 
}; 

typedef struct ComputationGraph computation_graph_t; 

/* init node value */
node_value_t *input_node(double output);

/* init node operation */
node_value_t *node_op(
    node_value_t *set_left,
    node_value_t *set_right, 
	void(*set_forward)(struct NodeValue *val),
	void(set_backward)(struct NodeValue *val) 
);

/* create computation graph */
computation_graph_t *create_graph(int set_size, double set_gradient); 

/* Append operation */
void append_op(computation_graph_t *graph, node_value_t *val); 

/* forward all */
void forward_nodes(computation_graph_t *graph); 

/* backward all */
void backward_nodes(computation_graph_t *graph); 



#endif
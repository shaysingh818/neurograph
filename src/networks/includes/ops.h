#ifndef OPS_H
#define OPS_H

#define FORWARD_DEBUG FALSE
#define BACKWARD_DEBUG FALSE

#include "value.h"

/* Add constant values */
void add_node(node_value_t *val);
void backward_add_node(node_value_t *val);
node_value_t *adder(
    computation_graph_t *graph,  
    node_value_t *val, 
    node_value_t *val2
); 

/* Multiply two constants */
void multiply_node(node_value_t *val); 
void backward_mult_node(node_value_t *val);
node_value_t *mult(
    computation_graph_t *graph,  
    node_value_t *val, 
    node_value_t *val2
); 

/* Raise a value by an exponent */
void exponent(node_value_t *val); 
void backward_exp(node_value_t *val);
node_value_t *expnt(
    computation_graph_t *graph,  
    node_value_t *val 
); 

/* Use eulers number */
void eulers(node_value_t *val); 
void backward_eulers(node_value_t *val);
node_value_t *euler(
    computation_graph_t *graph,  
    node_value_t *val
); 

/* Adding 1 to a value*/
void successor(node_value_t *val); 
void backward_successor(node_value_t *val);
node_value_t *add_one(
    computation_graph_t *graph,  
    node_value_t *val 
); 

/* 1/x on a value */
void reciprocal(node_value_t *val); 
void reciprocal_backward(node_value_t *val); 
node_value_t *recip(
    computation_graph_t *graph,  
    node_value_t *val 
); 

#endif
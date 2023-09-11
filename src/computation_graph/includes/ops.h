#ifndef OPS_H
#define OPS_H

#include "value.h"
#include "computation_graph.h"

/* Add constant values */
void add_node(value_t *val);
void backward_add_node(value_t *val);
value_t *adder(
    computation_graph_t *graph,  
    value_t *val, 
    value_t *val2
); 

/* Multiply two constants */
void multiply_node(value_t *val); 
void backward_mult_node(value_t *val);
value_t *mult(
    computation_graph_t *graph,  
    value_t *val, 
    value_t *val2
); 

/* Raise a value by an exponent */
void exponent(value_t *val); 
void backward_exp(value_t *val);
value_t *expnt(
    computation_graph_t *graph,  
    value_t *val 
); 

/* Use eulers number */
void eulers(value_t *val); 
void backward_eulers(value_t *val);
value_t *euler(
    computation_graph_t *graph,  
    value_t *val
); 

/* Adding 1 to a value*/
void successor(value_t *val); 
void backward_successor(value_t *val);
value_t *add_one(
    computation_graph_t *graph,  
    value_t *val 
); 

/* 1/x on a value */
void reciprocal(value_t *val); 
void reciprocal_backward(value_t *val); 
value_t *recip(
    computation_graph_t *graph,  
    value_t *val 
);


#endif
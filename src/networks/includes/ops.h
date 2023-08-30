#ifndef OPS_H
#define OPS_H

#define C_GRAPH_DEBUG TRUE

#include "value.h"

/* Add constant values */
void add_node(node_value_t *val);
void backward_add_node(node_value_t *val);

/* Multiply two constants */
void multiply_node(node_value_t *val); 
void backward_mult_node(node_value_t *val);

/* Raise a value by an exponent */
void exponent(node_value_t *val); 
void backward_exp(node_value_t *val); 

/* Use eulers number */
void eulers(node_value_t *val); 
void backward_eulers(node_value_t *val); 


#endif
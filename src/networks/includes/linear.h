#ifndef LINEAR_H
#define LINEAR_H

#include <math.h>
#include "computation_graph.h"

/* linear node */
struct Linear {
    c_node_t *node; 
    mat_t *weights, *biases;
    double learning_rate; 
}; 

typedef struct Linear linear_t; 


/* linear node methods */
void linear_forward(void *linear_ptr, mat_t *set_inputs);
void linear_backward(void *linear_ptr, mat_t *output_delta); 
linear_t *linear(int input_size,int output_size, double learning_rate);
void debug_linear(linear_t *linear); 

#endif
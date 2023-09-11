#ifndef MAT_OPS_H
#define MAT_OPS_H

#include "value.h"
#include "computation_graph.h"

/* matrix operations */
void mat_multiply(value_t *val); 
void mat_multiply_backward(value_t *val); 
value_t *mat_mul(
    computation_graph_t *graph,  
    value_t *x,
    value_t *y 
);


void mat_scale_add(value_t *val); 
void mat_scale_add_backward(value_t *val); 
value_t *scale_add_mat(
    computation_graph_t *graph,  
    value_t *x,
    value_t *y
);


/* apply activation function on matrix values */
value_t *apply_activation(
    computation_graph_t *graph,
    value_t *val,
	void(*activation)(value_t *val), 
	void(*activation_prime)(value_t *val)
); 


#endif
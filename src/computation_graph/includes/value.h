#ifndef VALUE_H
#define VALUE_H

#define FALSE 0
#define TRUE 1

#define FORWARD_DEBUG FALSE
#define BACKWARD_DEBUG FALSE

#include <math.h> 
#include "../../data_structures/includes/matrix.h"

struct Value {
    char *alias; 
    double output;  
    double upstream_gradient;
    double x_d_gradient, y_d_gradient;
    mat_t *mat_output, *mat_upstream_grad;
    mat_t *mat_x_d_grad, *mat_y_d_grad; 
    struct Value *left, *right;  
	void(*forward_operation)(struct Value *val); 
	void(*backward_operation)(struct Value *val); 
}; 

typedef struct Value value_t;


/* init node value */
value_t *input_node(double output);
value_t *input_node_mat(mat_t *input);

/* init node operation */
value_t *node_op(
    char *set_alias,
    value_t *set_left,
    value_t *set_right, 
	void(*set_forward)(value_t *val),
	void(set_backward)(value_t *val) 
);

#endif

#ifndef VALUE_H
#define VALUE_H

#include "../../data_structures/matrix/includes/matrix.h"

struct Value {
    char *alias; 
    struct Value *left, *right;  
    mat_t *val, *output;
    mat_t *upstream_gradient;
    mat_t *left_grad, *right_grad, *local_grad; 
	mat_t *(*forward_operation)(struct Value *val); 
	mat_t *(*backward_operation)(struct Value *val);
	double (*loss)(double val); 
	mat_t *(*loss_prime)(mat_t *val); 
}; 

typedef struct Value value_t;

/* create computation graph */
value_t *value(mat_t *set_value); 


#endif
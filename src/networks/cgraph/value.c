#include "includes/value.h"


value_t *input_node(double output) {
    value_t *val = malloc(sizeof(value_t));
    val->right = NULL; 
    val->left = NULL; 
    val->output = output; 
    return val;     
}

value_t *input_node_mat(mat_t *input) {
    value_t *val = malloc(sizeof(value_t));
    val->right = NULL; 
    val->left = NULL; 
    val->mat_output = input; 
    return val;     
}

value_t *node_op(
    value_t *set_left, 
    value_t *set_right,
	void(*set_forward)(struct Value *val),
	void(*set_backward)(struct Value *val)) {

    value_t *val = malloc(sizeof(value_t)); 
    val->left = set_left; 
    val->right = set_right; 
    val->forward_operation = set_forward; 
    val->backward_operation = set_backward; 
    return val;  
}
#include "includes/ops.h"

/* multiplication */
value_t *mat_mul(computation_graph_t *graph, value_t *x, value_t *y) {

    value_t *val = malloc(sizeof(value_t));
    size_t alias = strlen("mat_mul")+1; 
    val->alias = malloc(alias * sizeof(char)); 
    strcpy(val->alias, "mat_mul");  
    
    val->left = x; 
    val->right = y; 
    val->forward_operation = mat_mul_forward; 
    val->backward_operation = mat_mul_backward;
    append_op(graph, val); 
    return val; 
}

mat_t *mat_mul_forward(value_t *val) {
    val->val = dot(val->left->val, val->right->val);
    return val->val; 
} 


mat_t *mat_mul_backward(value_t *val) {
    val->left_grad = dot(val->upstream_gradient, transpose(val->right->val)); 
    val->right_grad = dot(transpose(val->left->val), val->upstream_gradient); 
    val->left->upstream_gradient = val->left_grad; 
    val->right->upstream_gradient = val->right_grad; 
    return val->right_grad; 
} 



/* scale add */
value_t *scale_add_mat(computation_graph_t *graph, value_t *x, value_t *y) {
    value_t *val = malloc(sizeof(value_t));
    size_t alias = strlen("scale_add")+1; 
    val->alias = malloc(alias * sizeof(char)); 
    strcpy(val->alias, "scale_add");  

    val->left = x; 
    val->right = y; 
    val->forward_operation = scale_add_forward; 
    val->backward_operation = scale_add_backward;
    append_op(graph, val); 
    return val; 
} 

mat_t *scale_add_forward(value_t *val) {
    val->val = scale_add(val->left->val, val->right->val); 
    return val->val; 
}


mat_t *scale_add_backward(value_t *val) {
    val->left_grad = val->upstream_gradient; 
    val->right_grad = val->upstream_gradient; 
    val->left->upstream_gradient = val->left_grad; 
    val->right->upstream_gradient = val->right_grad; 
    return val->right_grad; 
}



/* apply loss  */
value_t *apply_loss(
    computation_graph_t *graph, 
    value_t *set_val,
    double(*loss)(double val), 
	mat_t*(*loss_prime)(mat_t *val)) {

    value_t *val = malloc(sizeof(value_t));
    size_t alias = strlen("apply_loss")+1; 
    val->alias = malloc(alias * sizeof(char)); 
    strcpy(val->alias, "apply_loss");  
    
    val->left = set_val; 
    val->right = NULL; 
    val->loss = loss; 
    val->loss_prime = loss_prime; 
    val->forward_operation = apply_loss_forward; 
    val->backward_operation = apply_loss_backward;
    append_op(graph, val); 
    return val; 
    
}


mat_t *apply_loss_forward(value_t *val) {
    val->val = apply(val->loss, val->left->val); 
    return val->val; 
}


mat_t *apply_loss_backward(value_t *val) {
    val->left_grad = elementwise_multiply(
        val->upstream_gradient,
        val->loss_prime(val->left->val)
    );
    val->local_grad = val->left_grad; 
    val->left->upstream_gradient = val->left_grad; 
    return val->left_grad; 
}
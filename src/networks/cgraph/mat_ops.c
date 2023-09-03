#include "includes/mat_ops.h"


void mat_multiply(value_t *val) {
    val->mat_output = dot(val->left->mat_output, val->right->mat_output);
    if(FORWARD_DEBUG){
        print_vec(val->left->mat_output); 
        printf("\n X \n"); 
        print_vec(val->right->mat_output); 
    } 
}


void backward_mat_multiply(value_t *val) {
    val->mat_x_d_grad = transpose(val->right->mat_output); 
    val->mat_y_d_grad = transpose(val->left->mat_output); 
    val->left->mat_upstream_grad = val->mat_x_d_grad; 
    val->right->mat_upstream_grad = val->mat_y_d_grad; 
    if(BACKWARD_DEBUG){
        print_vec(val->left->mat_output); 
        printf("\n X \n"); 
        print_vec(val->right->mat_output); 
    } 
}


value_t *mat_mul(
    computation_graph_t *graph,  
    value_t *x,
    value_t *y) {


    value_t *i = node_op(
        x, y, 
        mat_multiply, 
        backward_mat_multiply
    );

    append_op(graph, i); 
    return i; 

} 


void mat_scale_add(value_t *val) {    
    val->mat_output = scale_add(val->left->mat_output, val->right->mat_output);
    if(FORWARD_DEBUG){
        print_vec(val->left->mat_output); 
        printf("\n X \n"); 
        print_vec(val->right->mat_output); 
    } 
} 

void mat_scale_add_backward(value_t *val) {    
    val->mat_x_d_grad = val->right->mat_output;
    val->left->mat_upstream_grad = val->mat_x_d_grad;  
    if(BACKWARD_DEBUG){
        print_vec(val->left->mat_output); 
        printf("\n X \n"); 
        print_vec(val->right->mat_output); 
    } 
}


value_t *scale_add_mat(
    computation_graph_t *graph,  
    value_t *x,
    value_t *y) {


    value_t *i = node_op(
        x, y, 
        mat_scale_add, 
        mat_scale_add_backward
    );

    append_op(graph, i); 
    return i; 

}
#include "includes/ops.h"


void add_node(node_value_t *val) {
    val->output = val->left->output + val->right->output;
    if(FORWARD_DEBUG){
        printf(
            "(%.2f + %.2f) = %.2f \n", 
            val->left->output, val->right->output, val->output
        );
    } 
}

void backward_add_node(node_value_t *val) {
    val->x_d_gradient = 1 * val->upstream_gradient; 
    val->y_d_gradient = 1 * val->upstream_gradient;
    val->left->upstream_gradient = val->x_d_gradient; 
    val->right->upstream_gradient = val->y_d_gradient;
    if(BACKWARD_DEBUG){
        printf(
            "(%.2f * %.2f) = %.2f , (%.2f * %.2f) = %.2f\n", 
            1.00, val->upstream_gradient, val->x_d_gradient,
            1.00, val->upstream_gradient, val->y_d_gradient
        );
    } 
}


node_value_t *adder(
    computation_graph_t *graph,  
    node_value_t *val, 
    node_value_t *val2 ) {

    
    node_value_t *e = node_op(
        val, val2, 
        add_node, 
        backward_add_node
    );

    append_op(graph, e);
    return e; 
} 


void multiply_node(node_value_t *val) {
    val->output = val->left->output * val->right->output;
    if(FORWARD_DEBUG){
        printf(
            "(%.2f * %.2f) = %.2f \n", 
            val->left->output, val->right->output, val->output
        );
    } 
} 

void backward_mult_node(node_value_t *val) {
    val->x_d_gradient = val->right->output * val->upstream_gradient;
    val->y_d_gradient = val->left->output * val->upstream_gradient;
    val->left->upstream_gradient = val->x_d_gradient; 
    val->right->upstream_gradient = val->y_d_gradient;
    if(BACKWARD_DEBUG){
        printf(
            "(%.2f * %.2f) = %.2f , (%.2f * %.2f) = %.2f\n", 
            val->right->output, val->upstream_gradient, val->x_d_gradient,
            val->left->output, val->upstream_gradient, val->y_d_gradient
        );
    } 

}


node_value_t *mult(
    computation_graph_t *graph,  
    node_value_t *val, 
    node_value_t *val2 ) {
 
    node_value_t *e = node_op(
        val, val2, 
        multiply_node, 
        backward_mult_node
    );

    append_op(graph, e);
    return e; 
} 


void exponent(node_value_t *val){
    val->output = exp(val->left->output);
    if(FORWARD_DEBUG){
        printf(
            "exp(%.2f) = %.2f \n", 
            val->left->output, val->output
        );
    } 
}


void backward_exp(node_value_t *val) {
    double local_grad = exp(val->left->output); 
    val->x_d_gradient = local_grad * val->upstream_gradient; 
    val->left->upstream_gradient = val->x_d_gradient; 
    if(BACKWARD_DEBUG){
        printf(
            "(%.2f * %.2f) = %.2f \n", 
            local_grad, val->upstream_gradient, val->x_d_gradient
        );
    } 
}


node_value_t *expnt(
    computation_graph_t *graph,  
    node_value_t *val) {
 
    node_value_t *e = node_op(
        val, NULL, 
        exponent, 
        backward_exp
    );

    append_op(graph, e);
    return e; 
} 


void eulers(node_value_t *val) {
    val->output = val->left->output * -1; 
    if(FORWARD_DEBUG){
        printf(
            "(%.2f * %.2f) = %.2f \n", 
            val->left->output, -1.00, val->output
        );
    } 
}


void backward_eulers(node_value_t *val) {
    double local_grad = -1.00;
    val->x_d_gradient = local_grad * val->upstream_gradient; 
    val->left->upstream_gradient = val->x_d_gradient; 
    if(BACKWARD_DEBUG){
        printf(
            "(%.2f * %.2f) = %.2f \n", 
            local_grad, val->upstream_gradient, val->x_d_gradient
        );
    } 
}


node_value_t *euler(
    computation_graph_t *graph,  
    node_value_t *val) {

    node_value_t *e = node_op(
        val, NULL, 
        eulers, 
        backward_eulers
    );

    append_op(graph, e);
    return e; 
    
} 


void successor(node_value_t *val) {
    val->output = val->left->output + 1; 
    if(FORWARD_DEBUG){
        printf(
            "(%.2f + 1) = %.2f \n", 
            val->left->output, val->output
        );
    } 
}


void successor_backward(node_value_t *val) {
    double local_grad = 1.00; 
    val->x_d_gradient = local_grad * val->upstream_gradient;
    val->left->upstream_gradient = val->x_d_gradient;  
    if(BACKWARD_DEBUG){
        printf(
            "(%.2f * %.2f) = %.2f \n", 
            local_grad, val->upstream_gradient, val->x_d_gradient
        );
    } 
} 


node_value_t *add_one(
    computation_graph_t *graph,  
    node_value_t *val) {


    node_value_t *i = node_op(
        val, NULL, 
        successor, 
        successor_backward
    );

    append_op(graph, i); 
    return i; 

} 


void reciprocal(node_value_t *val) {
    val->output = 1 / val->left->output; 
    if(FORWARD_DEBUG){
        printf(
            "(1 / %.2f) = %.2f \n", 
            val->left->output, val->output
        );
    } 
}


void reciprocal_backward(node_value_t *val) {
    double local_grad = -1 / (val->left->output * val->left->output); 
    val->x_d_gradient = local_grad * val->upstream_gradient;
    val->left->upstream_gradient = val->x_d_gradient;  
    if(BACKWARD_DEBUG){
        printf(
            "(%.2f * %.2f) = %.2f \n", 
            local_grad, val->upstream_gradient, val->x_d_gradient
        );
    } 
} 


node_value_t *recip(
    computation_graph_t *graph,  
    node_value_t *val) {


    node_value_t *i = node_op(
        val, NULL, 
        reciprocal, 
        reciprocal_backward
    );

    append_op(graph, i); 
    return i; 

} 
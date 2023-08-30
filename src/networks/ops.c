#include "includes/ops.h"


void add_node(node_value_t *val) {
    val->output = val->left->output + val->right->output;
    if(C_GRAPH_DEBUG){
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
}

void multiply_node(node_value_t *val) {
    val->output = val->left->output * val->right->output;
    if(C_GRAPH_DEBUG){
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
}


void exponent(node_value_t *val){
    val->output = exp(val->left->output);
    if(C_GRAPH_DEBUG){
        printf(
            "exp(%.2f) = %.2f \n", 
            val->left->output, val->output
        );
    } 
} 


void eulers(node_value_t *val) {
    val->output = val->left->output * -1; 
    if(C_GRAPH_DEBUG){
        printf(
            "(%.2f * %.2f) = %.2f \n", 
            val->left->output, -1.00, val->output
        );
    } 
} 
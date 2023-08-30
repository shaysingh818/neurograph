#include "includes/value.h"


node_value_t *input_node(double output) {
    node_value_t *val = malloc(sizeof(node_value_t));
    val->right = NULL; 
    val->left = NULL; 
    val->output = output; 
    return val;     
}


node_value_t *node_op(
    node_value_t *set_left, 
    node_value_t *set_right,
	void(*set_forward)(struct NodeValue *val),
	void(*set_backward)(struct NodeValue *val)) {

    node_value_t *val = malloc(sizeof(node_value_t)); 
    val->left = set_left; 
    val->right = set_right; 
    val->forward_operation = set_forward; 
    val->backward_operation = set_backward; 
    return val;  
}


computation_graph_t *create_graph(int set_size, double set_gradient) {
    computation_graph_t *graph = malloc(sizeof(computation_graph_t));
    graph->size = set_size; 
    graph->curr_index = 0; 
    graph->base_gradient = 1.00; 

    /* allocate op nodes  */
    graph->operations = malloc(graph->size * sizeof(node_value_t*)); 
    for(int i = 0; i < graph->size; i++){
        graph->operations[i] = malloc(sizeof(node_value_t)); 
    }
    return graph; 
}


void append_op(computation_graph_t *graph, node_value_t *val) {
    if(graph->curr_index == graph->size){
        printf("Graph is full\n"); 
        exit(0); 
    }
    graph->operations[graph->curr_index] = val; 
    graph->curr_index += 1; 
}


void forward_nodes(computation_graph_t *graph) {
    for(int i = 0; i < graph->curr_index; i++){
        node_value_t *op = graph->operations[i]; 
        op->forward_operation(op); 
    }
}


void backward_nodes(computation_graph_t *graph) {
    node_value_t *base_node = graph->operations[graph->curr_index-1]; 
    base_node->upstream_gradient = graph->base_gradient;
    for(int i = graph->curr_index-1; i >= 0; i--){
        node_value_t *op = graph->operations[i]; 
        op->backward_operation(op); 
    }
} 
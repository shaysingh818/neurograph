#include "includes/computation_graph.h"


computation_graph_t *create_graph(int set_size, double set_gradient) {
    computation_graph_t *graph = malloc(sizeof(computation_graph_t));
    graph->size = set_size; 
    graph->curr_index = 0; 
    graph->base_gradient = 1.00; 

    /* allocate op nodes  */
    graph->operations = malloc(graph->size * sizeof(value_t*)); 
    for(int i = 0; i < graph->size; i++){
        graph->operations[i] = malloc(sizeof(value_t)); 
    }
    return graph; 
}


void append_op(computation_graph_t *graph, value_t *val) {
    if(graph->curr_index == graph->size){
        printf("Graph is full\n"); 
        exit(0); 
    }
    graph->operations[graph->curr_index] = val; 
    graph->curr_index += 1; 
}


void forward_nodes(computation_graph_t *graph) {
    for(int i = 0; i < graph->curr_index; i++){
        value_t *op = graph->operations[i]; 
        op->forward_operation(op); 
    }
}


void backward_nodes(computation_graph_t *graph) {
    value_t *base_node = graph->operations[graph->curr_index-1]; 
    base_node->upstream_gradient = graph->base_gradient;
    for(int i = graph->curr_index-1; i >= 0; i--){
        value_t *op = graph->operations[i]; 
        op->backward_operation(op); 
    }
} 
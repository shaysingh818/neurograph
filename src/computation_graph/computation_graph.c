#include "includes/computation_graph.h"


computation_graph_t *create_graph() {
    computation_graph_t *graph = malloc(sizeof(computation_graph_t));
    graph->size = 2; /* initial size */
    graph->curr_index = 0; 

    /* allocate op nodes  */
    graph->nodes = malloc(graph->size * sizeof(value_t*)); 
    for(int i = 0; i < graph->size; i++){
        graph->nodes[i] = malloc(sizeof(value_t)); 
    }
    return graph; 
}


void append_op(computation_graph_t *graph, value_t *val) {
    if(graph->curr_index == graph->size){
        int new_size = graph->size + graph->size; 
        graph->nodes = realloc(graph->nodes, new_size * sizeof(value_t*)); 
        for(int i = graph->size; i < new_size; i++){
            graph->nodes[i] = malloc(sizeof(value_t)); 
        } 
    }
    graph->nodes[graph->curr_index] = val; 
    graph->curr_index += 1; 
}


void forward_nodes(computation_graph_t *graph) {
    for(int i = 0; i < graph->curr_index; i++){
        value_t *op = graph->nodes[i];
        op->forward_operation(op);
    }
}


void backward_nodes(computation_graph_t *graph, mat_t *output_error) {
    value_t *base_node = graph->nodes[graph->curr_index-1]; 
    base_node->upstream_gradient = output_error; 
    for(int i = graph->curr_index-1; i >= 0; i--){
        value_t *op = graph->nodes[i]; 
        op->backward_operation(op); 
    }
} 
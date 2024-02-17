#include "includes/computation.h"


computation_graph_t *computation_graph(double base_derivative) {
	computation_graph_t *comp_graph = malloc(sizeof(computation_graph_t)); 
    comp_graph->curr_node_count = 3; 
    comp_graph->base_derivative = base_derivative;
    comp_graph->graph = init_graph(
        comp_graph->curr_node_count, 
        comp_graph->curr_node_count, 
        false
    );
    return comp_graph;
}


#include "includes/test_comp.h"


void test_comp_graph() {

    /* create graph */
    adjacency_list_t *graph = init_comp_graph();
    add_cgraph_node(graph, 0, 1);
    add_cgraph_node(graph, 0, 2);
    print_comp_graph(graph);
}
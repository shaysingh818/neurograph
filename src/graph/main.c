#include "includes/graph.h"


int main(int argc, char **argv) {

	/* test random walk */
    int vertices = 5; // num of vertices

    adj_list_t *g = init_graph(vertices, vertices, false);
    add_node(g, 0, "A", 1, "B", 0);
    add_node(g, 0, "A", 2, "C", 0);
    add_node(g, 0, "A", 3, "D", 0);
    add_node(g, 1, "B", 2, "C", 0);
    add_node(g, 4, "E", 2, "C", 0);

    print_graph(g);

	return 0; 

}

#include "graph/includes/graph.h"
#include "graph/includes/path.h"
#include "data_structures/includes/matrix.h"
#include "data_structures/includes/adj_list.h"
#include "data_structures/includes/queue.h"
#include "data_structures/includes/map.h"
#include "data_structures/includes/node.h"
#include "extractors/includes/frame.h"
#include "extractors/includes/gml.h"
#include "extractors/includes/re.h"
#include "networks/includes/network.h"

int main(int argc, char **argv) {


	/* test random walk */ 
  	int vertices = 5; // num of vertices

	graph_t *g = init_graph(vertices, vertices, false); 
	add_node(g->list, 0, "A", 1, "B", 0); 
	add_node(g->list, 0, "A", 2, "C", 0); 
	add_node(g->list, 0, "A", 3, "D", 0); 
	add_node(g->list, 1, "B", 2, "C", 0);
	add_node(g->list, 4, "E", 2, "C", 0);

	printf("Graph library test\n"); 
	print_graph_list(g); 

	printf("\n");

	/* create adjacency matrix graph with size 5 */
	mat_graph_t *m = init_matrice_graph(5); 

    /* create unique nodes */
    entry_t *a = init_entry(0, "A"); 
    entry_t *b = init_entry(1, "B"); 
    entry_t *c = init_entry(2, "C"); 
    entry_t *d = init_entry(3, "D"); 

	/* connect a to everyone */ 
    insert(m, a, b, 0, false); 
    insert(m, a, c, 0, false); 
    insert(m, b, c, 0, false); 
    insert(m, b, d, 0, false); 
    insert(m, c, d, 0, false); 

	printf("Matrix library test\n");
	print_matrix_ids(m);

	printf("\n"); 

	/* create nodes */ 
    node_t *node1 = create_node(1, "A", 0); 
    node_t *node2 = create_node(2, "B", 0); 
    node_t *node3 = create_node(3, "C", 0); 
    

	/* neural net library  */
    double learning_rate = 0.1; 
    bool equality_status = true; 
    int epochs = 1000, num_layers = 4;
    net_t *nn = init_network(num_layers, learning_rate);

    linear_t *l1 = linear(2, 3, learning_rate); 
    layer(nn, init_node_type(LINEAR, l1));

    loss_t *loss1 = loss(2, 3, tanh, tanh_prime);
    layer(nn, init_node_type(LOSS, loss1));

    linear_t *l2 = linear(3, 1, learning_rate);
    layer(nn, init_node_type(LINEAR, l2));

    loss_t *loss2 = loss(3, 1, tanh, tanh_prime);
    layer(nn, init_node_type(LOSS, loss2));



	return 0; 
}

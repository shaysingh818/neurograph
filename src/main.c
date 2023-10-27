#include "graph/includes/graph.h"
#include "graph/includes/path.h"
#include "data_structures/matrix/includes/matrix.h"
#include "data_structures/list/includes/adj_list.h"
#include "data_structures/queue/includes/queue.h"
#include "data_structures/map/includes/map.h"
#include "data_structures/node/includes/node.h"
#include "extractors/includes/frame.h"
#include "extractors/includes/gml.h"
#include "extractors/includes/re.h"
#include "networks/includes/network.h"
#include "computation_graph/includes/computation_graph.h"

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

	/* create nodes */ 
    node_t *node1 = create_node(1, "A", 0); 
    node_t *node2 = create_node(2, "B", 0); 
    node_t *node3 = create_node(3, "C", 0); 
    

	/* neural net library  */
    double learning_rate = 0.1; 
    double inputs[4][2] = {{0,0},{0,1},{1,0},{1,1}};
    double outputs[4][1] = {{0},{1},{1},{0}};

    /* create x input */
    mat_t *x = copy_arr_to_matrix(4, 2, inputs); 
    mat_t *y = copy_arr_to_matrix(4, 1, outputs);
    value_t *input = value(x);
    net_t *nn = init_network(learning_rate, input, 0);

    /* define model architecture */
    layer(nn, linear(2, 3));
    layer(nn, activation(2, 3, "tanh", tanh_activation, tanh_prime));
    layer(nn, linear(3, 1)); 
    layer(nn, activation(3, 1, "tanh", tanh_activation, tanh_prime));
    train(nn, 1000, y);

    /* get output */
    int output_index = nn->graph->curr_index - 1;
    mat_t *output = nn->graph->nodes[output_index]->val;
    print_vec(output);  





	return 0; 
}

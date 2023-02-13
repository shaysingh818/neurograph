#include "includes/graph.h"
#include "includes/matrix.h"
#include "includes/queue.h"
#include "includes/path.h"

int main(int argc, char **argv) {


	/* test random walk */ 
  	int vertices = 5; // num of vertices

	graph_t *g = init_graph(vertices, vertices, false); 
	add_node(g, 0, "A", 1, "B", 0); 
	add_node(g, 0, "A", 2, "C", 0); 
	add_node(g, 0, "A", 3, "D", 0); 
	add_node(g, 1, "B", 2, "C", 0);
	add_node(g, 4, "E", 2, "C", 0);

	print_graph(g); 

	/*
	int steps = 10; 
	int path[steps]; 
    int *result = random_walk(g, 0, steps, path);
	for(int i = 0; i < steps; i++) {
		printf("%d ", path[i]); 
	} */ 


	return 0; 
}

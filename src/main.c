#include "includes/graph.h"
#include "includes/matrix.h"
#include "includes/queue.h"
#include "includes/path.h"

int main(int argc, char **argv) {


	/* test random walk */ 
  	int vertices = 5; // num of vertices

	adj_list_t *a = init_adj_list(vertices); 
	add_edge(a, 0, 'A', 1, 'B'); 
	add_edge(a, 0, 'A', 2, 'C'); 
	add_edge(a, 0, 'A', 3, 'D'); 
	add_edge(a, 1, 'B', 2, 'C');
	add_edge(a, 4, 'E', 2, 'C');


	int steps = 10; 
	int path[steps]; 
    int *result = random_walk(a, 0, steps, path);
	for(int i = 0; i < steps; i++) {
		printf("%d ", path[i]); 
	}


	return 0; 
}

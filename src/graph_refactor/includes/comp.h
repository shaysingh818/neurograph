#ifndef COMP_H
#define COMP_H

/* include data structures library */
#include "node.h"
#include <stdbool.h> 

#define INITIAL_NODE_SIZE 5
#define TRUE 1
#define FALSE 0

/* standard graph representation that contains array of weighted edges */ 
struct AdjacencyList {
	int v, e; 
	int curr_node_count; 	
	int *visited, *used;
	bool directed;
   	bool err; 	
	node_obj_list_t **items; 	
}; 

typedef struct AdjacencyList adjacency_list_t; 

/* computation graph */
adjacency_list_t *init_comp_graph();
int add_cgraph_node(adjacency_list_t *g, int src_id, int dest_id);

/* printing methods */
void print_comp_graph(adjacency_list_t *g);


#endif
#ifndef GRAPH_H
#define GRAPH_H

#include "../../data_structures/includes/set.h"
#include "../../data_structures/includes/queue.h"
#include "../../data_structures/includes/matrix.h"
#include "../../data_structures/includes/adj_list.h"

#define TRUE 1
#define FALSE 0

/* structure for storing results of walking through a graph */ 
struct Walk {
	int *path;
   	int steps; 	
	int weighted_sum;  
	int cycles; 
}; 

typedef struct Walk walk_t;

/* improved graph structure for the future */
struct Graph {
	int vertices, edges;
	int *visited, *labels;
	char *filename; 
	bool directed; 
	adj_list_t *list; 
	mat_graph_t *matrix;
	walk_t *walk; 
};

typedef struct Graph graph_t;

/* create graph structure */
graph_t *init_graph(int v, int e, bool directed); 

/* init walk structure */
walk_t *init_walk(int steps);
void print_walk(walk_t *w); 

/* conversion methods to matrix */
mat_graph_t *to_matrix(mat_graph_t *m, adj_list_t *g, bool directed);

/* conversion methods to adjacency list  */ 
adj_list_t *to_list(adj_list_t *g, mat_graph_t *m, bool directed);

/* printing methods */
void print_graph_list(graph_t *g); 
void print_graph_matrix(graph_t *g);
void print_graph_walk(graph_t *g); 


#endif



#ifndef GRAPH_H
#define GRAPH_H

#include <string.h>
#include <stdio.h>
#include <stdlib.h> 
#include <math.h>
#include <time.h>
#include <unistd.h>

#include "node.h"
#include "queue.h"
#include "matrix.h"

#define TRUE 1
#define FALSE 0


/* standard graph representation that contains array of weighted edges */ 
struct Graph {
	int v;
   	int e; 	
	int *visited; 
	bool directed; 
   	edge_t **edges;
	node_list_t *items; 	
}; 

typedef struct Graph graph_t; 

/* structure for storing results of walking through a graph */ 
struct Walk {
	int *path;
   	int steps; 	
	int weighted_sum;  
	int cycles; 
}; 

typedef struct Walk walk_t;


/* structural methods */ 
graph_t *init_graph(int v, int e, bool directed);
walk_t *init_walk(int steps); 

/* mutators for structural methods */ 
graph_t *transpose_items(graph_t *g, graph_t *r); 

/* conversion methods to matrix */
mat_t *to_matrix(mat_t *m, graph_t *g);
mat_t *to_weighted_matrix(mat_t *m, graph_t *g);
mat_t *to_directed_matrix(mat_t *m, graph_t *g); 
mat_t *to_directed_weighted_matrix(mat_t *m, graph_t *g); 

/* conversion methods to graph */ 
graph_t *to_list(graph_t *g, mat_t *m); 
graph_t *to_weighted_list(graph_t *g, mat_t *m);
graph_t *to_directed_list(graph_t *a, mat_t *m); 
graph_t *to_directed_weighted_list(graph_t *g, mat_t *m); 


/* methods for adding nodes to graph */
int add_node(
	graph_t *g, int src_id, char *src_label, 
	int dest_id, char *dest_label, int weight
); 
int add_end_node(graph_t *g, int src_id, char *src_label, int weight);
int push_unweighted_node(graph_t *g, char *src, char *dst); 
int push_weighted_node(graph_t *g, char *src, char *dst, int weight); 

/* printers formatters */ 
void print_graph(graph_t *g);

#endif


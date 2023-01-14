
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

/* adjacency list for representing a graph */ 
struct AdjList {
	int v; 
	int *visited; 
	node_list_t *items; 
}; 

typedef struct AdjList adj_list_t;


/* adjacency list for representing a graph with weighted nodes */ 
struct WeightedAdjList {
	int v; 
	int *visited;
	w_node_list_t *items; 
}; 

typedef struct WeightedAdjList w_adj_list_t;


/* structure for storing results of walking through a graph */ 
struct Walk {
	int *path;
   	int steps; 	
	int weighted_sum;  
	int cycles; 
}; 

typedef struct Walk walk_t;


/* standard graph representation that contains array of weighted edges */ 
struct Graph {
	int v;
   	int e; 	
	int *visited; 
   	edge_t **edges; 	
}; 

typedef struct Graph graph_t; 

/* structural methods */ 
graph_t *init_graph(int v, int e);
adj_list_t *init_adj_list(int v);
w_adj_list_t *init_w_adj_list(int v);
walk_t *init_walk(int steps); 

/* mutators for structural methods */ 
adj_list_t *transpose_adj(adj_list_t *a, adj_list_t *r); 

/* conversion methods */
mat_t *to_matrix(mat_t *m, adj_list_t *a);
mat_t *to_weighted_matrix(mat_t *m, w_adj_list_t *a);
mat_t *to_directed_matrix(mat_t *m, adj_list_t *a); 
mat_t *to_directed_weighted_matrix(mat_t *m, w_adj_list_t *a); 
adj_list_t *to_list(adj_list_t *a, mat_t *m); 
w_adj_list_t *to_weighted_list(w_adj_list_t *a, mat_t *m);
adj_list_t *to_directed_list(adj_list_t *a, mat_t *m); 
w_adj_list_t *to_directed_weighted_list(w_adj_list_t *a, mat_t *m); 


/* utilities */
void print_graph(graph_t *g);
void print_adj_list(adj_list_t *a);
void print_w_adj_list(w_adj_list_t *a); 
int add_edge(adj_list_t *a, int src_id, char src_label, int dest_id, char dest_label);
int add_directed_edge(
	adj_list_t *a, 
	int src_id, char src_label, 
	int dest_id, char dest_label
); 
int add_directed_weighted_edge(
	w_adj_list_t *a, 
	int src_id, char src_label, 
	int dest_id, char dest_label,
	int weight
); 
int add_end_node(adj_list_t *a, int src_id, char src_label); 
int add_w_edge(
	w_adj_list_t *a, 
	int src_id, char src_label,
	int dest_id, char dest_label,
	int weight
);


#endif


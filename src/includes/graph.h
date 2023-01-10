
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
int add_end_node(adj_list_t *a, int src_id, char src_label); 
int add_w_edge(
	w_adj_list_t *a, 
	int src_id, char src_label,
	int dest_id, char dest_label,
	int weight
); 

/* traversals (search) */ 
queue_t *bfs(adj_list_t *a, node_t *root); 
int dfs(queue_t *q, adj_list_t *a, node_t *root);

/* path finding */ 
int *bellman_ford(graph_t *g, node_t *root, int *dist); 
int *random_walk(adj_list_t *a, int start_vertex, int steps, int *path); 
walk_t *weighted_random_walk(w_adj_list_t *a, walk_t *w, int start_vertex); 

/* centrality algorithms */
int degree_centrality(graph_t *g, node_t *root);
int weighted_degree_centrality(w_adj_list_t *a);

/* community detection */
int k_dfs(queue_t *q, adj_list_t *a, node_t *root); 
int kosaraju(adj_list_t *a, int start_vertex);
int label_propagation(graph_t *g, node_t *root); 


#endif


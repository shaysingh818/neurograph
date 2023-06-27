#ifndef ADJ_LIST_H
#define ADJ_LIST_H

#include <string.h>
#include <stdio.h>
#include <stdlib.h> 
#include <math.h>
#include <time.h>
#include <unistd.h>
#include <stdbool.h> 
#include <limits.h> 

#include "node.h"

#define TRUE 1
#define FALSE 0


/* standard graph representation that contains array of weighted edges */ 
struct AdjacencyList {
	int v;
   	int e; 	
	int *visited; 
	bool directed;
   	bool err; 	
   	edge_t **edges;
	node_list_t **items; 	
}; 

typedef struct AdjacencyList adj_list_t; 


/* structural methods */ 
adj_list_t *init_graph(int v, int e, bool directed);

/* mutators for structural methods */ 
adj_list_t *transpose_items(adj_list_t *g, adj_list_t *r); 

/* methods for adding nodes to graph */
int add_node(
	adj_list_t *g, int src_id, char *src_label, 
	int dest_id, char *dest_label, int weight
); 

int add_end_node(adj_list_t *g, int src_id, char *src_label, int weight);
int push_unweighted_node(adj_list_t *g, char *src, char *dst); 
int push_weighted_node(adj_list_t *g, char *src, char *dst, int weight);

/* utiltiy */ 
node_t *get_node_by_id(adj_list_t *g, int id);
void resize_adj_list(adj_list_t *g, int new_size);  

/* printers formatters */ 
void print_graph(adj_list_t *g);

#endif
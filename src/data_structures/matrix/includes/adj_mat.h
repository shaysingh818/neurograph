#ifndef ADJ_MAT_H
#define ADJ_MAT_H

#include <string.h>
#include <stdio.h>
#include <stdlib.h> 
#include <math.h>
#include <time.h>
#include <unistd.h>
#include <stdbool.h> 
#include <limits.h> 
#include "matrix.h"
#include "../../node/includes/node.h"

/* standard graph representation that contains array of weighted edges */ 
struct AdjacencyMatrix {
	int v;
   	int e; 	
	int *visited, *used;
	bool directed;
   	bool err; 	
    mat_t *weights; 
	node_t **items; 	
}; 

typedef struct AdjacencyMatrix adj_mat_t;


/* matrice instance */ 
adj_mat_t *init_adj_mat(int v, int e, bool directed);

/* Add node relationship to adjacency matrix */
void add_node_mat(
    adj_mat_t *m, int src_id, char *src, 
    int dst_id, char *dst, double weight
);

/* tranpose items in adjacency matrix  */ 
adj_mat_t *transpose_items_mat(adj_mat_t *m, adj_mat_t *r); 

/* search node by id */
node_t *search_node_by_id_mat(adj_mat_t *m, int id);

/* print adjacency matrix */
void print_adj_mat(adj_mat_t *m); 

#endif





#ifndef GRAPH_H
#define GRAPH_H

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

/* init walk structure */
walk_t *init_walk(int steps); 

/* conversion methods to matrix */
mat_graph_t *to_matrix(mat_graph_t *m, adj_list_t *g, bool directed);

/* conversion methods to graph */ 
adj_list_t *to_list(adj_list_t *g, mat_graph_t *m, bool directed); 


#endif


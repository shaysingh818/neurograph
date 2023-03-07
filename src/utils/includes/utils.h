#ifndef UTILS_H
#define UTILS_H

#include "../../matrice/includes/matrix.h"
#include "../../graph/includes/graph.h"
#include "../../queue/includes/queue.h"
#include "../../graph/includes/path.h"
#include "../../csv/includes/csv.h"


/* bare bones graph methods */ 
adj_list_t *init_graph_util(int size, bool directed);
int add_node_util(
	adj_list_t *g, int src_id, char *src, 
	int dst_id, char *dst, int weight
);

/* csv methods */ 
char *extract_headers(char *filename); 
adj_list_t *g_to_csv_util(char *filename, int *features,  int size, int row_limit);
void free_graph(adj_list_t *g); 

#endif

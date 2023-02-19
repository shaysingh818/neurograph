#ifndef UTILS_H
#define UTILS_H

#include "matrix.h"
#include "graph.h"
#include "queue.h"
#include "path.h"
#include "csv.h"


/* bare bones graph methods */ 
graph_t *init_graph_util(int size, bool directed);
int add_node_util(
	graph_t *g, int src_id, char *src, 
	int dst_id, char *dst, int weight
);

/* csv methods */ 
char *extract_headers(char *filename); 
graph_t *g_to_csv_util(char *filename, int *features,  int size, int row_limit);
void free_graph(graph_t *g); 

#endif

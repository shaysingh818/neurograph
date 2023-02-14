#ifndef UTILS_H
#define UTILS_H

#include "matrix.h"
#include "graph.h"
#include "queue.h"
#include "path.h"


/* methods exposed for python libary */ 
graph_t *init_graph_util(int size, bool directed);
int add_node_util(
	graph_t *g, int src_id, char *src, 
	int dst_id, char *dst, int weight
); 

#endif

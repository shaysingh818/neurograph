#ifndef PATH_H
#define PATH_H

#include "graph.h"

int *bellman_ford(graph_t *g, node_t *root, int *dist); 
int *random_walk(adj_list_t *a, int start_vertex, int steps, int *path); 
walk_t *weighted_random_walk(w_adj_list_t *a, walk_t *w, int start_vertex);

#endif

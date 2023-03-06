#ifndef PATH_H
#define PATH_H


#include <limits.h> 
#include "graph.h"

int *bellman_ford(graph_t *g, node_t *root, int *dist); 
int *dijkstra(graph_t *g, int start_vertex);
int shortest_path(graph_t *g, int start_vertex, int end_vertex);  
int *random_walk(graph_t *g, int start_vertex, int steps, int *path); 
walk_t *weighted_random_walk(graph_t *g, walk_t *w, int start_vertex);

#endif

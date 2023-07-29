#ifndef PATH_H
#define PATH_H

#include <limits.h> 
#include "graph.h"

/* ADJACENCY LIST (Path finding )*/
int *bellman_ford_list(graph_t *g, node_t *root, int *dist); 
int *dijkstra_list(graph_t *g, int start_vertex);
int shortest_path_list(graph_t *g, int start_vertex, int end_vertex);  
walk_t *random_walk_list(graph_t *g, int start_vertex, int steps); 
walk_t *weighted_random_walk_list(graph_t *g, walk_t *w, int start_vertex);


/* MATRICE REPRESENTATION (Path finding) */
walk_t *random_walk_mat(graph_t *m, int start_vertex, int steps);
int *dijkstra_mat(graph_t *m, int start_vertex); 
int shortest_path_mat(graph_t *m, int start_vertex, int end_vertex); 


#endif

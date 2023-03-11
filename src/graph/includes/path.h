#ifndef PATH_H
#define PATH_H

#include <limits.h> 
#include "graph.h"

/* ADJACENCY LIST (Path finding )*/
int *bellman_ford(adj_list_t *g, node_t *root, int *dist); 
int *dijkstra(adj_list_t *g, int start_vertex);
int shortest_path(adj_list_t *g, int start_vertex, int end_vertex);  
int *random_walk(adj_list_t *g, int start_vertex, int steps, int *path); 
walk_t *weighted_random_walk(adj_list_t *g, walk_t *w, int start_vertex);


/* MATRICE REPRESENTATION (Path finding) */
walk_t *random_walk_mat(mat_t *m, int start_vertex, int steps);
int *dijkstra_mat(mat_t *m, int start_vertex); 
int shorest_path_mat(mat_t *m, int start_vertex, int end_vertex); 


#endif

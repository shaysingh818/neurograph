#ifndef COMMUNITY_H
#define COMMUNITY_H

#include "graph.h"
#include "search.h"
#include "path.h"

/* ADJACENCY LIST representation (Centrality) */
int degree_centrality_list(graph_t *g, node_t *root);
int weighted_degree_centrality_list(graph_t *g); 
float closeness_centrality_list(graph_t *g, int vertex);
float normalized_closeness_centrality_list(graph_t *g, int vertex); 
int page_rank_list(graph_t *g, node_t *root); 
int **kosaraju_list(graph_t *g, int start_vertex);
int max_label_occurrence(graph_t *g, int node_id, node_t *root);
int *label_propagator_list(graph_t *g, int *labels, int start_vertex);
int *label_propagation_iterative_list(graph_t *g, int start_vertex); 
int triangle_count_list(graph_t *g, int vertex); 

/* matrice based methods */
int *degree_centrality_mat(graph_t *m);
mat_t *label_nodes_mat(graph_t *m, int labels[]); 
mat_t *label_propogation_mat(mat_t *A, int iterations); 


#endif

#ifndef COMMUNITY_H
#define COMMUNITY_H

#include "graph.h"
#include "search.h"
#include "path.h"

/* ADJACENCY LIST representation (Centrality) */
int degree_centrality(adj_list_t *g, node_t *root);
int weighted_degree_centrality(adj_list_t *g); 
float closeness_centrality(adj_list_t *g, int vertex);
float normalized_closeness_centrality(adj_list_t *g, int vertex); 

/* ADJACENCY LIST (Page Rank Centrality)*/
int page_rank(adj_list_t *g, node_t *root); 

/* ADJACENCY LIST Community detection*/
int **kosaraju(adj_list_t *g, int start_vertex); 

/* MATRICE REPRESENTATION */
int *degree_centrality_mat(mat_graph_t *m);
mat_t *label_nodes(mat_graph_t *m, int labels[]); 
mat_t *label_propogation(mat_t *A, int iterations); 

/* method for labeling adj_list graph */
int *label_propagator(adj_list_t *g, int *labels, int start_vertex); 
int triangle_count(adj_list_t *g, int vertex); 

#endif

#ifndef COMMUNITY_H
#define COMMUNITY_H

#include "graph.h"
#include "search.h"
#include "path.h"

int degree_centrality(adj_list_t *g, node_t *root); 
int weighted_degree_centrality(adj_list_t *g); 
int **kosaraju(adj_list_t *g, int start_vertex); 

/* v.0.2.0 */
float closeness_centrality(adj_list_t *g, int vertex);
float normalized_closeness_centrality(adj_list_t *g, int vertex);  
int page_rank(adj_list_t *g, node_t *root); 

#endif

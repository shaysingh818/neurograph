#ifndef COMMUNITY_H
#define COMMUNITY_H

#include "graph.h"
#include "search.h"
#include "path.h"

int degree_centrality(graph_t *g, node_t *root); 
int weighted_degree_centrality(graph_t *g); 
int **kosaraju(graph_t *g, int start_vertex); 

/* v.0.2.0 */
float closeness_centrality(graph_t *g, int vertex);
float normalized_closeness_centrality(graph_t *g, int vertex);  
int page_rank(graph_t *g, node_t *root); 

#endif

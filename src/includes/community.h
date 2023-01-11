#ifndef COMMUNITY_H
#define COMMUNITY_H

#include "graph.h"
#include "search.h"

int degree_centrality(graph_t *g, node_t *root); 
int weighted_degree_centrality(w_adj_list_t *a); 
char **kosaraju(adj_list_t *a, int start_vertex); 

#endif

#ifndef SEARCH_H
#define SEARCH_H

#include "graph.h"

queue_t *bfs(adj_list_t *a, node_t *root); 
int dfs(queue_t *q, adj_list_t *a, node_t *root); 
int k_dfs(queue_t *q, adj_list_t *a, node_t *root); 


#endif

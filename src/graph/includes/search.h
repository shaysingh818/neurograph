#ifndef SEARCH_H
#define SEARCH_H

#include "graph.h"
#include "../../data_structures/includes/queue.h"

queue_t *bfs(adj_list_t *g, node_t *root); 
int dfs(queue_t *q, adj_list_t *g, node_t *root); 
int k_dfs(queue_t *q, adj_list_t *g, node_t *root); 

#endif

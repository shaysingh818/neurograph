#ifndef SEARCH_H
#define SEARCH_H

#include "graph.h"
#include <data_structures/queue/includes/queue.h>

queue_t *bfs(graph_t *g, node_t *root); 
int dfs(queue_t *q, graph_t *g, node_t *root); 
int k_dfs(queue_t *q, graph_t *g, node_t *root); 

#endif

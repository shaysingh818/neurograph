#ifndef GRAPH_TEST_H
#define GRAPH_TEST_H


#include "../../src/includes/graph.h"
#include "../../src/includes/queue.h"


/* test adjacency list representation */ 
void test_adjacency_list();
void test_weighted_adjacency_list(); 


/* test searching methods */ 
void test_bfs_one(); 
void test_bfs_two(); 
void test_dfs_one(); 
void test_bellman_ford();
void test_random_walk();
void test_weighted_random_walk(); 
void test_degree_centrality(); 
void test_weighted_degree_centrality(); 

#endif

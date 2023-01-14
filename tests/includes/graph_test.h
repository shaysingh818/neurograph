#ifndef GRAPH_TEST_H
#define GRAPH_TEST_H

#include "../../src/includes/graph.h"
#include "../../src/includes/queue.h"

/* test adjacency list representation */ 
void test_adjacency_list();
void test_weighted_adjacency_list(); 
void test_transpose_adj_list();

/* test conversion methods */ 
void test_to_matrix();
void test_to_directed_matrix(); 
void test_to_weighted_matrix(); 
void test_to_directed_weighted_matrix(); 
void test_to_list(); 
void test_to_weighted_list(); 
void test_to_directed_list();
void test_to_directed_weighted_list(); 

#endif

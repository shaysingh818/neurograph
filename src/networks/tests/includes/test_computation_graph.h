#ifndef TEST_COMPUTATION_GRAPH_H
#define TEST_COMPUTATION_GRAPH_H


#include "../../includes/computation_graph.h"

/* node type methods */
void test_init_node_type(); 
void test_init_nodes(); 
void test_append_c_node();
void test_forward_all(); 
void test_backward_all();  

/* computation graph examples */
void test_mlp();
void test_dense();
// void test_forward_nodes(); 


#endif
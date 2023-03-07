#ifndef TEST_GRAPH_H
#define TEST_GRAPH_H

#include "../../includes/graph.h"
#include "../../../queue/includes/queue.h"

/* test conversion methods */ 
void test_to_list(); 
void test_to_weighted_list(); 
void test_to_directed_list();
void test_to_directed_weighted_list(); 

/* matrix conversions */
void test_to_matrix();
void test_to_directed_matrix(); 
void test_to_weighted_matrix(); 
void test_to_directed_weighted_matrix(); 

#endif

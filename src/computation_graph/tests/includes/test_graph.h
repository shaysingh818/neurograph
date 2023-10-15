#ifndef TEST_GRAPH_H
#define TEST_GRAPH_H

#include <assert.h>
#include "../../includes/computation_graph.h"
#include "../../includes/ops.h"
#include "../../includes/loss.h"

void test_create_graph();
void test_append_operation(); 
void test_forward_nodes(); 
void test_backward_nodes(); 

#endif
#ifndef TEST_ADJ_MAT_H
#define TEST_ADJ_MAT_H

#include "../../includes/adj_mat.h"
#include <assert.h>

/* test adjacency list representation */ 
void test_init_adj_mat();
void test_add_node_mat_undirected();
void test_add_node_mat_directed();
void test_search_by_id_mat(); 
void test_transpose_items_mat();  

#endif
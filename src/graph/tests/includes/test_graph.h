#ifndef TEST_GRAPH_H
#define TEST_GRAPH_H

#include "../../includes/graph.h"
#include "../../../data_structures/includes/queue.h"
#include <assert.h>

/* general utilties */
void test_get_max_vertex_count(); 
void test_get_nodes_from_file(); 
void test_get_nodes();  

/* graph markup language methods */
void test_gml_expression_adj_list(); 
void test_serialize_adj_list_sorted_labels(); 
void test_serialize_adj_list(); 
void test_deserialize_adj_list(); 
void test_serialize_mat_graph();
void test_deserialize_mat_graph(); 

/* frame to graph methods */
void test_frame_to_unweighted_graph(); 
void test_frame_to_weighted_graph(); 
void test_frame_to_matrice_graph(); 
void test_unused_slots();

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

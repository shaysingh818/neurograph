#ifndef TEST_GML_H
#define TEST_GML_H

#include "../../includes/gml.h"
#include <assert.h> 

void test_gml_expression_set();
void test_gml_expression_adj_list();  

void test_serialize_adj_list(); 
void test_deserialize_adj_list(); 

void test_serialize_mat_graph();
void test_deserialize_mat_graph(); 

#endif
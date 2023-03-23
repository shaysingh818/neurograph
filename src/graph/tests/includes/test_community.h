#ifndef TEST_COMMUNITY_H
#define TEST_COMMUNITY_H

#include "../../includes/community.h"
#include "../../includes/graph.h"

void test_degree_centrality();
void test_weighted_degree_centrality();
void test_closeness_centrality(); 
void test_normalized_closeness_centrality(); 
void test_kosaraju(); 

/* test matrice version */
void test_degree_centrality_mat();
void test_label_nodes(); 
void test_label_propogation();  

#endif

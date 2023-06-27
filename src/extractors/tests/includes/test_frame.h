#ifndef TEST_FRAME_H
#define TEST_FRAME_H

#include "../../includes/frame.h"
#include "../../../graph/includes/graph.h"

/* data frame helpers */
void test_extract_frame_headers(); 
void test_init_frame_rows(); 

/* data frame methods */
void test_init_frame_structure();

/* graph conversion */
void test_frame_to_unweighted_graph(); 
void test_frame_to_weighted_graph(); 
void test_frame_to_matrice_graph(); 
void test_unused_slots(); 

#endif
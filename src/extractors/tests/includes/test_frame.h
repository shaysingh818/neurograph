#ifndef TEST_FRAME_H
#define TEST_FRAME_H

#include "../../includes/frame.h"
#include "../../../graph/includes/graph.h"
#include <assert.h> 

/* data frame helpers */
void test_extract_frame_headers(); 
void test_init_frame_rows(); 

/* data frame methods */
void test_init_frame_structure();

/* graph conversion */
void test_hash_map_frame(); 

/* matrix conversion */
void test_frame_to_matrix(); 

#endif
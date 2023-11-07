#ifndef TEST_FRAME_H
#define TEST_FRAME_H

#include "../../includes/frame.h"
#include <assert.h> 

/* data frame helpers */
void test_create_frame();
void test_extract_frame_headers(); 
void test_init_rows(); 
void test_dataframe(); 
void test_frame_to_matrix();
void test_drop_cols(); 

#endif
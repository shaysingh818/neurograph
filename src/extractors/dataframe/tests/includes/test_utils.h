#ifndef TEST_UTILS_H
#define TEST_UTILS_H

#include "../../includes/utils.h"
#include <assert.h> 

/* data frame helpers */
void test_match_delimeter_file();
void test_allocate_frame_headers();
void test_copy_row_values();  
void test_match_header();  
void test_frame_to_matrix();

#endif
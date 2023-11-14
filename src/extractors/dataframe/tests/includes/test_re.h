#ifndef TEST_RE_H
#define TEST_RE_H

#include "../../includes/re.h"
#include "../../includes/gml.h"
#include <assert.h> 

/* test extracting headers from csv file */
void test_match_single();
void test_match_pattern(); 
void test_csv_line();
void test_blank_values();
void test_match_delimeter_file();

#endif
#ifndef TEST_CSV_H
#define TEST_CSV_H

#include "../../includes/csv.h"
#include "../../../graph/includes/graph.h"

/* test extracting headers from csv file */
void test_populate_headers();
void test_populate_headers_two();
void test_populate_headers_three();
void test_populate_headers_four();
void test_populate_headers_five();

/* test extracting rows from csv file */ 
void test_populate_rows(); 
void test_populate_rows_two(); 
void test_populate_rows_three(); 
void test_populate_rows_four(); 

/* test the structure itself  */
void test_invalid_file(); 
void test_csv_structure(); 

/* test csv to graph */ 
void test_csv_to_graph();
void test_csv_to_graph_two();
void test_csv_to_graph_three();
void test_csv_to_graph_four();

/* test multi feature select */ 
void test_even_pair_feature_pass(); 
void test_even_pair_feature_fail(); 
void test_odd_pair_feature_pass(); 
void test_odd_pair_feature_fail(); 



#endif
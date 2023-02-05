#ifndef CSV_TEST_H
#define CSV_TEST_H

#include "../../src/includes/csv.h"
#include "../../src/includes/graph.h"

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
void test_csv_to_graph_matrice(); 

#endif

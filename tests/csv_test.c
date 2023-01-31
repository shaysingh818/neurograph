#include "includes/csv_test.h"


void test_populate_headers() {

	/* test these */ 

}


void test_populate_rows() {

	/* test this */ 

}


void test_csv_structure() {

	csv_t *file = csv_init("../examples/data/test.csv", FILE_BUFFER_SIZE, 4);
	printf("Hi\n");

	/* validate what's inside the structure */
	print_cols(file); 	
	print_rows(file); 

}



#include "includes/test_csv.h"

int main(int argc, char **argv) {

	
	/* test csv data extraction */
   	test_populate_headers(); 
	test_populate_headers_two(); 
	test_populate_headers_three(); 
	test_populate_headers_four(); 
   	test_populate_rows(); 
	
	/* test csv structure */ 
	test_invalid_file(); 	
	test_csv_structure();

	/* test graph conversion from csv */
	test_csv_to_graph();
	test_csv_to_graph_two();
	test_csv_to_graph_three();

	/* test multi feature select */
	test_even_pair_feature_pass();
	test_even_pair_feature_fail();
	test_odd_pair_feature_pass();
	test_odd_pair_feature_fail();

}

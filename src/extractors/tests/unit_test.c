#include "includes/test_csv.h"
#include "includes/test_frame.h"
#include "includes/test_re.h"

int main(int argc, char **argv) {

	
	// /* test csv data extraction */
   	// test_populate_headers(); 
	// test_populate_headers_two(); 
	// test_populate_headers_three(); 
	// test_populate_headers_four(); 
   	// test_populate_rows(); 
	
	// /* test csv structure */ 
	// test_invalid_file(); 	
	// test_csv_structure();

	// /* test graph conversion from csv */
	// test_csv_to_graph();
	// test_csv_to_graph_two();
	// test_csv_to_graph_three();

	// /* test multi feature select */
	// test_even_pair_feature_pass();
	// test_even_pair_feature_fail();
	// test_odd_pair_feature_fail();

	/* tests for re library */
	test_match_single();
	test_csv_line();  

	/* dataframe library tests */
	test_extract_frame_headers();
	test_init_frame_rows(); 
	test_init_frame_structure();  
	test_frame_to_unweighted_graph();
	test_frame_to_weighted_graph(); 
	test_unused_slots();
	test_hash_map_frame();   

}

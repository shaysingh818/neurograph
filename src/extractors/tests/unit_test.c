#include "includes/test_frame.h"
#include "includes/test_re.h"
#include "includes/test_gml.h"

int main(int argc, char **argv) {

	
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

	/* gml testing */
	test_gml_expression_set(); 
	test_serialize_adj_list();   

}

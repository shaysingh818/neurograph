#include "includes/test_frame.h"
#include "includes/test_re.h"
#include "includes/test_gml.h"

int main(int argc, char **argv) {

	/* tests for re library */
	test_match_single();
	test_match_pattern(); 
	test_csv_line(); 
	test_blank_values();  

	/* dataframe library tests */
	test_extract_frame_headers();
	test_init_frame_rows(); 
	test_init_frame_structure();  
	test_hash_map_frame();
	test_frame_to_matrix();  

	/* gml testing */
	test_gml_expression_set();
	test_gml_weights_ids_expression();  

}

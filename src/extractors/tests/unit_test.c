#include "includes/test_frame.h"
#include "includes/test_re.h"
#include "includes/test_gml.h"
#include "includes/test_frame_memory.h"

int main(int argc, char **argv) {

	/* tests for re library */
	test_match_single();
	test_match_pattern(); 
	test_csv_line(); 
	test_blank_values();  

	/* dataframe library tests */
	// test_init_frame_rows(); 
	// test_init_frame_structure();  
	// test_match_frame_delimiter_file();  

	/* gml testing */
	test_gml_expression_set();
	test_gml_weights_ids_expression();  

	/* frame tests that actually work  */
	test_extract_frame_headers();
	test_frame_to_matrix();
	test_match_delimeter_file(); 
	test_allocate_frame_headers(); 
	test_copy_row_values(); 
	test_match_header();  


}

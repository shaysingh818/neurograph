#include "includes/test_frame.h"
#include "includes/test_re.h"
#include "includes/test_gml.h"

int main(int argc, char **argv) {

	/* tests for re library */
	test_match_single();
	test_csv_line();  

	/* dataframe library tests */
	test_extract_frame_headers();
	test_init_frame_rows(); 
	test_init_frame_structure();  
	test_hash_map_frame(); 

	/* gml testing */
	test_gml_expression_set(); 

}

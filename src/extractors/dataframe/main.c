#include "tests/includes/test_frame.h"
#include "tests/includes/test_utils.h"
#include "tests/includes/test_ops.h"
#include "tests/includes/test_gml.h"
#include "tests/includes/test_re.h"

int main(int argc, char **argv) {

    /* initializers */
    test_create_frame();
    test_extract_frame_headers();
    test_init_rows(); 
    test_dataframe(); 
    test_frame_to_matrix();  
    test_drop_cols();

    /* test operations */
    test_add_frame_cols(); 
    test_subtract_frame_cols(); 

	/* gml testing */
	test_gml_expression_set();
	test_gml_weights_ids_expression(); 

    /* regular expression testing */
	test_match_single();
	test_match_pattern(); 
	test_csv_line(); 
	test_blank_values();  

}

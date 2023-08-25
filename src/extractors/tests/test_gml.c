#include "includes/test_gml.h"


void test_gml_expression_set() {

	bool equality_status = true; 
	char *expected_node_set[7] = {
		"a", "b", "c", "d", "e", "f", "g"
	}; 

	/* variables */
    int file_size = 1024; 
    char *filename = "../../examples/gml/unit_tests/test.gmul"; 
	FILE* fp = fopen(filename, "r");
   	int row_count = 0;
    char *head_label; 
    char* buffer = malloc(file_size * sizeof(char));
    ordered_set_t *node_set =  init_array_set(10); 

	while(fgets(buffer, file_size, fp)) {

		/* null terminate the buffer */ 
		int len = strlen(buffer); 
		if(buffer[len-1] == '\n') {
			buffer[len-1] = 0; 
		}

		/* extract tokens from regular expression */
		tokens_t *row_values = match_single(buffer, RE_GML); 
		int size = row_values->result_size;

        /* extract node */
		tokens_t *r_quotes = match_single(row_values->tokens[0], REMOVE_QUOTES); 
        char *node = r_quotes->tokens[0];
        insert_ordered(node_set, row_count, node, 0); 

        /* extract neighbors */
        for(int i = 1; i < size; i++){
		    r_quotes = match_single(row_values->tokens[i], REMOVE_QUOTES); 
            char *neighbor = r_quotes->tokens[0];
            insert_ordered(node_set, row_count, neighbor, 0); 
        }

		row_count += 1;
	}

    printf("%s::%s... \e[0;32mPASSED\e[0m\n", __FILE__, __FUNCTION__);

}


void test_gml_weights_ids_expression() {

    int file_size = 1024; 
    char *filename = "../../examples/data/output/sample.gmul"; 
	FILE* fp = fopen(filename, "r");
   	int row_count = 0;
    char *head_label; 
    char* buffer = malloc(file_size * sizeof(char));

	while(fgets(buffer, file_size, fp)) {

		/* null terminate the buffer */ 
		int len = strlen(buffer); 
		if(buffer[len-1] == '\n') {
			buffer[len-1] = 0; 
		}

		/* extract tokens from regular expression */
		tokens_t *row_values = match_single(buffer, RE_GML_NODE); 
		int size = row_values->result_size;

		char *id_string = row_values->tokens[0]; 
		int src_id = atoi(id_string);
		char *src = row_values->tokens[1];

		assert(src_id >= 0); 
		assert(src != NULL); 

		/* Check if all neighbors info is there */
		assert((size-2) % 3 == 0); 
		if((size-2) % 3 != 0){
			printf("Line [%d]: Error with node neighbors config\n", row_count);
		}

		/* get neighbors */
		for(int i = 2; i < size; i+=3){
			int dst_id = atoi(row_values->tokens[i]);
			char *dst = row_values->tokens[i+1];
			int weight = atoi(row_values->tokens[i+2]);

			assert(dst_id >= 0); 
			assert(dst != NULL); 
			assert(weight >= 0); 

			remove_char(dst, '"');
			remove_char(src, '"'); 
		} 
		row_count += 1;
	}

	//assert(row_count == 6);  
    printf("%s::%s... \e[0;32mPASSED\e[0m\n", __FILE__, __FUNCTION__);
} 


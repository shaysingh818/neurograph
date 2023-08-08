#include "includes/test_gml.h"


void test_gml_expression_set() {

	bool equality_status = true; 
	char *expected_node_set[7] = {
		"a", "b", "c", "d", "e", "f", "g"
	}; 

	/* variables */
    int file_size = 1024; 
    char *filename = "../../examples/gml/test.gmul"; 
	FILE* fp = fopen(filename, "r");
   	int row_count = 0;
    char *head_label; 
    char* buffer = malloc(file_size * sizeof(char));
    set_t *node_set =  init_set(true); 

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

    //print_items_ordered(node_set); 
	int counter = 0;  
	while(node_set->root != NULL) {
		assert(strcmp(node_set->root->label, expected_node_set[counter]) == 0); 
		node_set->root = node_set->root->next; 
		counter += 1; 
	}

    if(!equality_status) {
        printf("%s::%s... FAILED\n", __FILE__, __FUNCTION__);
    }
    printf("%s::%s... \e[0;32mPASSED\e[0m\n", __FILE__, __FUNCTION__);

}


#include "includes/test.h"

test_t *init_test(
    char *set_input_file_name, 
    char *set_output_file_name, 
    int set_file_size,
    void (*test_method)(test_t *t, array_t *args, array_t *outputs)) {

	test_t *test = malloc(sizeof(test_t));
   	test->method_to_test = test_method;
    test->file_size = set_file_size; 

    /* set file names */
    size_t in_file_size = strlen(set_input_file_name)+1; 
    size_t out_file_size = strlen(set_output_file_name)+1; 
    test->input_file_name = malloc(in_file_size * sizeof(char));
    test->output_file_name = malloc(out_file_size * sizeof(char)); 
    strcpy(test->input_file_name, set_input_file_name); 
    strcpy(test->output_file_name, set_output_file_name);

    /* allocate buffers */
    test->infile_buffer = malloc(test->file_size * sizeof(char)); 
    test->outfile_buffer = malloc(test->file_size * sizeof(char)); 

    /* Check if input and output file paths exist */
	if(access(test->input_file_name, F_OK) == -1) {
   		strcpy(test->input_file_name, "");
		printf("File does not exist: %s\n", test->input_file_name);
	   	return test; 	
	}

	if(access(test->output_file_name, F_OK) == -1) {
   		strcpy(test->output_file_name, "");
		printf("File does not exist: %s\n", test->output_file_name);
	   	return test; 	
	}

    return test;  
} 


void run(test_t *test) {

	/* variables */
	FILE *in_fp, *out_fp; 
    in_fp = fopen(test->input_file_name, "r");
	out_fp = fopen(test->output_file_name, "r");
   	int row_count = 0;

	while(fgets(test->infile_buffer, test->file_size, in_fp) &&
        fgets(test->outfile_buffer, test->file_size, out_fp)) {

		/* null terminate the buffer */ 
		end_line_terminate(test->infile_buffer); 
		end_line_terminate(test->outfile_buffer); 

		/* extract tokens from regular expression */
    	array_t *args = match_delimeter_file(test->infile_buffer, ":");
    	array_t *outputs = match_delimeter_file(test->outfile_buffer, ":");

		int size = args->item_count;
        test->method_to_test(test, args, outputs); 
		row_count += 1;
	}

	printf("%s::%s...  \e[0;32mPASSED\e[0m\n", __FILE__, test->input_file_name); 
} 


harness_t *init_harness() {
	harness_t *harness = malloc(sizeof(harness_t));
    harness->initial_size = 2; 
    harness->current_count = 0; 
    harness->tests = malloc(harness->initial_size * sizeof(test_t*)); 
    for(int i = 0; i < harness->initial_size; i++){
        harness->tests[i] = malloc(sizeof(test_t)); 
    }
    return harness;  
} 


void add_test(harness_t *harness, test_t *t) {
    if(harness->current_count == harness->initial_size){
        int new_size = harness->current_count + harness->current_count; 
        harness->tests = realloc(harness->tests, new_size * sizeof(test_t*)); 
        for(int i = harness->initial_size; i < new_size; i++){
            harness->tests[i] = malloc(sizeof(test_t)); 
        } 
    }
    harness->tests[harness->current_count] = t; 
    harness->current_count += 1; 
}


void run_tests(harness_t *harness) {
    for(int i = 0; i < harness->current_count; i++){
        run(harness->tests[i]); 
    }
}


char **convert_input_file_char_array(array_t *tokens) {
    char **cols = malloc(tokens->item_count * sizeof(char*)); 
    for(int i = 0; i < tokens->item_count; i++){
        size_t result_size = strlen(tokens->items[i]->label) + 1; 
        cols[i] = malloc(result_size * sizeof(char)); 
        strcpy(cols[i], tokens->items[i]->label); 
    }
    return cols; 
} 
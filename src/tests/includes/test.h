#ifndef TEST_H
#define TEST_H

#include <stdbool.h>
#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
#include <assert.h>  
#include <data_structures/includes/array.h> 
#include "../../extractors/includes/frame.h" 


struct Test {
    int file_size; 
    char *input_file_name, *output_file_name; 
    char *infile_buffer, *outfile_buffer; 
	void(*method_to_test)(struct Test *t, array_t *args, array_t *outputs);
    bool pass;  
}; 

typedef struct Test test_t;


struct Harness {
    int initial_size, current_count; 
    test_t **tests; 
}; 

typedef struct Harness harness_t; 

/* create behavior test instance */
test_t *init_test(
    char *set_input_file_name, 
    char *set_output_file_name, 
    int set_file_size,
    void (*test_method)(test_t *t, array_t *args, array_t *outputs)
);

/* methods to run tests */
void run(test_t *test); 

/* harness methods  */
harness_t *init_harness();
void add_test(harness_t *harness, test_t *t);
void run_tests(harness_t *harness);  

/* conversions for input files */
char **convert_input_file_char_array(array_t *tokens);
char **convert_input_file_int_array(test_t *test, char *buffer); 
char **convert_input_file_double_array(test_t *test, char *buffer); 


#endif
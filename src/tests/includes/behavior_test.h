#ifndef BEHAVIOR_TEST_H
#define BEHAVIOR_TEST_H


struct BehaviorTest {
    char *input_file, *expected_output_file; 
    char **input_files, **output_files;
    void **args;  
	void*(*method_to_test)(void **args);
    void (*unit_test_logic)(struct BehaviorTest *btest); 
    bool pass;  
}; 

typedef struct BehaviorTest b_test_t; 

/* create behavior test instance */
b_test_t *init_btest(void *(*test_method)(void **args)); 
void set_expected_inputs_outputs(char *in_file, char *out_file); 
void set_expected_multi_inputs_outputs(char **in_files, char **out_files); 
void set_args(void **args); 

/* conversions for input files */
char **convert_input_file_char_array(b_test_t *test, char *buffer); 
char **convert_input_file_int_array(b_test_t *test, char *buffer); 
char **convert_input_file_double_array(b_test_t *test, char *buffer); 

/* methods to run tests */
void run_single_input_output_test(b_test_t *test); 
void run_multi_input_output_test(b_test_t *test); 

#endif
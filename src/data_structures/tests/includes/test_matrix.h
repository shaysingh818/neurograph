#ifndef TEST_MATRIX_H
#define TEST_MATRIX_H

#include "../../includes/matrix.h"
#include <assert.h>

#define TRUE 1
#define FALSE 0


/* test vector methods */
void test_init_vec(); 
void test_scalar_multiply(); 
void test_copy_vec(); 
void test_vector_multiplication();
void test_matrix_power();
void test_to_rows_cols(); 
void test_batch_rows();  
void test_uniform_distribution();
void test_load_and_save_matrix();
void test_copy_arr_to_matrix(); 

/* test matrix operations  */
void test_dot_product();
void test_dot_unequal_dimensions();
void test_backprop_dot_product(); 
void test_add_mat();
void test_scale_add();  
void test_transpose_mat(); 
void test_scale_multiply(); 
void test_elementwise_multiply(); 
void test_add_matrix(); 
void test_matrix_difference(); // @TODO


#endif

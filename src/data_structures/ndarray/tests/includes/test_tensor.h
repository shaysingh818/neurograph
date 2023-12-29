#ifndef TEST_TENSOR_H
#define TEST_TENSOR_H

#include "../../includes/ndarray.h"
#include <assert.h>

#define TRUE 1
#define FALSE 0


/* test tensor utils */
void test_ndimensional_index();
void test_get_tensor_indices();  
void test_set_tensor();
void test_reshape(); 
void test_tensor_apply(); 
void test_save_tensor(); 
void test_load_tensor();

#endif
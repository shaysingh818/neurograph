#ifndef TEST_OPS_H
#define TEST_OPS_H

#include "../../includes/ops.h"
#include <assert.h>

#define TRUE 1
#define FALSE 0


/* test tensor utils */
void test_add_tensor();
void test_subtract_tensor();  
void test_scale_add_tensor();
void test_tensor_dot_product();  
void test_tensor_transpose();
void test_tensor_permute(); 

#endif
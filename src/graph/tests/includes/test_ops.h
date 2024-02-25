
#ifndef TEST_OPS_H
#define TEST_OPS_H

#include "../../includes/operations.h"
#include <assert.h>


/* test scalar operations */
void test_scalar_add(); 
void test_scalar_multiply();
void test_scalar_tanh(); 

/* mlp operations */
void test_nd_dot();
void test_nd_scale_add(); 
void test_nd_apply_loss();  



#endif
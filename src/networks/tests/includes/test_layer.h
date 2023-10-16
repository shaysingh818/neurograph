#ifndef TEST_LAYER_H
#define TEST_LAYER_H

#include <assert.h>
#include "../../includes/layer.h"

void test_serialize_layer_struct(); 

void test_linear_layer();
void test_activation_layer(); 
void test_forward_all_layers(); 

/* test saving params for each layer*/
void test_save_linear_layer(); 

#endif
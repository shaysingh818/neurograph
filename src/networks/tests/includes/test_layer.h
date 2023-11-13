#ifndef TEST_LAYER_H
#define TEST_LAYER_H

#include <assert.h>
#include "../../includes/layer.h"

/* test loss map definition */
void test_loss_dict(); 

void test_linear_layer();
void test_activation_layer(); 
void test_forward_all_layers(); 

/* test saving params for each layer*/
void test_save_linear_layer(); 
void test_load_linear_layer();

void test_save_activation_layer(); 
void test_load_activation_layer(); 

/* test layer dictionary */
void test_layer_dict(); 

#endif
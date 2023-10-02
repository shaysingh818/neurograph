#ifndef TEST_NETWORK_H
#define TEST_NETWORK_H

#include <assert.h>
#include "../../includes/network.h"

void test_init_network();
void test_add_layer(); 
void test_train();
void test_loss(); 
void test_network_train(); 
void test_base_concept(); // for debugging and walking step by step
void test_save_model_params(); 
void test_load_model_params(); 

#endif

#ifndef LAYER_TYPES_H
#define LAYER_TYPES_H

#include "../../computation_graph/includes/value.h"

struct Linear {
    int input_size, output_size; 
    value_t *weights,*biases;
}; 

typedef struct Linear linear_t; 

struct Activation {
    int input_size, output_size; 
	void(*loss)(value_t *val); 
	void(*loss_prime)(value_t *val);
}; 

typedef struct Activation activation_t; 

#endif
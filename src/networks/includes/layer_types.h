
#ifndef LAYER_TYPES_H
#define LAYER_TYPES_H

#include "../../computation_graph/includes/value.h"
#include <unistd.h>


struct Activation {
    char *loss_function_name; 
    int input_size, output_size; 
	double(*loss)(double val); 
	mat_t*(*loss_prime)(mat_t *val);
}; 

typedef struct Activation activation_t; 


struct Linear {
    int input_size, output_size; 
    value_t *weights,*biases;
}; 

typedef struct Linear linear_t; 


#endif
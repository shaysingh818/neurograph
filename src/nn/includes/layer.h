#ifndef LAYER_H
#define LAYER_H

#include "../../matrice/includes/matrix.h"
#include "activations.h"


struct Layer {
	int input_size, output_size;
	bool activation; // bool if the layer is only activation 
	vec_t *inputs, *outputs; 
	vec_t *weights, *biases; 
	double(*activation_function)(double); 
	double(*activation_function_prime)(double); 
}; 

typedef struct Layer layer_t; 

/* init method */ 
layer_t *init_layer(int set_input_size, int set_output_size, bool activation); 

/* forward */ 
vec_t *forward(layer_t *layer, vec_t *inputs); 
vec_t *backward(layer_t *layer, vec_t *output_error, double learning_rate); 


#endif

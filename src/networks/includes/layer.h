#ifndef LAYER_H
#define LAYER_H

#include "../../data_structures/includes/matrix.h"
#include "activations.h"
#include "computation_graph.h"


struct MultiLayer {
	linear_t *linear; 
	loss_t *loss; 
	double(*activation_function)(double); 
}; 

typedef struct MultiLayer mlp_layer_t;


struct Layer {
	int input_size, output_size;
	bool activation; // bool if the layer is only activation 
	mat_t *inputs, *outputs; 
	mat_t *weights, *biases; 
	double(*activation_function)(double); 
	double(*activation_function_prime)(double); 
}; 

typedef struct Layer layer_t; 

/* init method */ 
layer_t *nn_layer(int set_input_size, int set_output_size, bool activation); 

/* forward */ 
mat_t *forward(layer_t *layer, mat_t *inputs); 
mat_t *backward(layer_t *layer, mat_t *output_error, double learning_rate); 


#endif

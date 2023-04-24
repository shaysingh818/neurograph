#include "includes/layer.h"


layer_t *init_layer(int set_input_size, int set_output_size, bool activation) {
	
    layer_t *layer = (layer_t*)malloc(sizeof(layer_t));
    layer->input_size = set_input_size;
    layer->output_size = set_output_size;
	layer->activation = activation; 

	if(activation) {
		layer->activation_function = sigmoid; 
		layer->activation_function_prime = sigmoid_prime; 
	} else {

		layer->weights = init_vec(layer->input_size, layer->output_size, false); 
		layer->biases = init_vec(1, layer->output_size, false);

		/* randomize weights for FC layer */ 
		randomize(layer->weights, layer->input_size); 
		randomize(layer->biases, layer->input_size);
	}

	return layer; 	
}


vec_t *forward(layer_t *layer, vec_t *inputs){

	layer->inputs = inputs;

	if(layer->activation){
		vec_t *sig = apply(sigmoid, inputs);
		layer->outputs = sig;  

	} else {
		vec_t *p = dot(inputs, layer->weights); 
		vec_t *biase = scale_add(p, layer->biases); 
		vec_t *activation = apply(sigmoid, biase); 
		layer->outputs = activation;
	}
	return layer->outputs;  
}


vec_t *backward(layer_t *layer, vec_t *output_error, double learning_rate) {

	vec_t *input_error; 

	if(!layer->activation){

		vec_t *weight = transpose(layer->weights);
		vec_t *inputs = transpose(layer->inputs);  
		vec_t *weights_error = dot(inputs, output_error);

		/* update params */
		vec_t *new_weights = scale(weights_error, learning_rate); 
		vec_t *new_biases = scale(output_error, learning_rate); 

		input_error = dot(output_error, weight); 

	} else {
		vec_t *sig_prime = apply(sigmoid_prime, layer->inputs); 
		input_error = multiply(layer->inputs, output_error); 
	}

	return input_error;  
}

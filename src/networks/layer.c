#include "includes/layer.h"


layer_t *nn_layer(int set_input_size, int set_output_size, bool activation) {
	
    layer_t *layer = (layer_t*)malloc(sizeof(layer_t));
    layer->input_size = set_input_size;
    layer->output_size = set_output_size;
	layer->activation = activation; 

    layer->activation_function = tanh_activation; 
    layer->weights = init_matrix(layer->input_size, layer->output_size); 
    layer->biases = init_matrix(1, layer->output_size);
    randomize(layer->weights, layer->input_size); 
    randomize(layer->biases, layer->input_size);

	return layer; 	
}


mat_t *forward(layer_t *layer, mat_t *inputs) {

    //mat_t *z1 = scale_add(dot(x, w1), b1);
    layer->inputs = inputs; 
    if(layer->activation) {
        layer->outputs = apply(tanh_activation, layer->inputs);
    } else {
        mat_t *dot_result = scale_add(dot(layer->inputs, layer->weights), layer->biases);
        layer->outputs = dot_result;
    }
	return layer->outputs; 
}


mat_t *backward(layer_t *layer, mat_t *output_error, double learning_rate) {
    
    if(layer->activation){

        // update sigmoid prime to mkrays version
        mat_t *activation_prime = tanh_prime(layer->inputs);
        mat_t *input_error = elementwise_multiply(output_error, activation_prime);
        return input_error; 

    } else {

        mat_t *input_error = dot(output_error, transpose(layer->weights));
        mat_t *weights_error = scale(dot(transpose(layer->inputs), output_error), learning_rate);
        mat_t *biase_error = scale(output_error, learning_rate);  

        layer->weights = add(layer->weights, weights_error);
        layer->biases = add(layer->biases, biase_error);

        return input_error; 
    }
}

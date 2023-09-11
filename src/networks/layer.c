#include "includes/layer.h"


value_t *linear_forward(computation_graph_t *graph, layer_t *layer, value_t *prev_output){
    linear_t *linear = layer->layer_type->linear; 
    layer->inputs = prev_output; 
    value_t *result =  scale_add_mat( 
        graph, 
        mat_mul(graph, layer->inputs, linear->weights),
        linear->biases
    );
    layer->outputs = result; 
    return result; 
}


value_t *update_linear(computation_graph_t *graph, layer_t *layer, int op_index) {
    linear_t *linear = layer->layer_type->linear;

    /* update weights and biases */
    linear->biases->mat_output = add(
        linear->biases->mat_output,
        scale(graph->operations[op_index]->mat_upstream_grad, 0.1)
    );

    linear->weights->mat_output = add(
        linear->weights->mat_output,
        scale(graph->operations[op_index-1]->mat_y_d_grad, 0.1)
    ); 

    return layer->outputs; 
} 

layer_t *linear(int set_input_size, int set_output_size) {

    /* create linear structure */
    linear_t *linear = (linear_t*)malloc(sizeof(linear_t));
    linear->input_size = set_input_size; 
    linear->output_size = set_output_size;
    mat_t *weights = init_matrix(set_input_size, set_output_size); 
    mat_t *biases = init_matrix(1, set_output_size); 
    randomize(weights, weights->rows); 
    randomize(biases, biases->rows); 
    linear->weights = input_node_mat(weights); 
    linear->biases = input_node_mat(biases);

    /* create base layer type for activation */
    layer_t *layer = (layer_t*)malloc(sizeof(layer_t));
    layer->layer_type = (layer_obj_t*)malloc(sizeof(layer_obj_t));
    layer->input_size = set_input_size; 
    layer->output_size = set_output_size;
    layer->layer_type->linear = linear;
    layer->forward = linear_forward; 
    layer->update_params = update_linear; 
    layer->op_count = 2;
    return layer;  
}


value_t *activation_forward(computation_graph_t *graph, layer_t *layer, value_t *prev_output) { 
    layer->inputs = prev_output; 
    activation_t *activation = layer->layer_type->activation; 
    value_t *result = apply_activation(
        graph,
        layer->inputs,
        activation->loss,
        activation->loss_prime
    );
    layer->outputs = result; 
    return result; 
} 


value_t *update_activation(computation_graph_t *graph, layer_t *layer, int op_index) {
    activation_t *activation = layer->layer_type->activation;
    return layer->outputs;  
} 

layer_t *activation(
    int set_input_size, int set_output_size,
    void(*set_loss)(value_t *val),
    void(*set_loss_prime)(value_t *val)) {

    /* create activation structure */
    activation_t *activation = (activation_t*)malloc(sizeof(activation_t));
    activation->input_size = set_input_size;
    activation->output_size = set_output_size; 
    activation->loss = set_loss; 
    activation->loss_prime = set_loss_prime;

    /* create base layer type for activation */
    layer_t *layer = (layer_t*)malloc(sizeof(layer_t));
    layer->layer_type = (layer_obj_t*)malloc(sizeof(layer_obj_t)); 
    layer->layer_type->activation = activation;
    layer->forward = activation_forward;
    layer->update_params = update_activation;  
    layer->op_count = 1;
    return layer;  
}
#include "includes/layer.h"


value_t *activation_forward(computation_graph_t *graph, layer_t *layer, value_t *prev_output) { 
    layer->inputs = prev_output; 
    activation_t *activation = layer->layer_type->activation; 
    value_t *result = apply_loss(
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
    char *loss_function_name,
    double(*set_loss)(double val),
    mat_t*(*set_loss_prime)(mat_t *val)) {


    /* create activation structure */
    activation_t *activation = (activation_t*)malloc(sizeof(activation_t));
    activation->input_size = set_input_size;
    activation->output_size = set_output_size; 
    activation->loss = set_loss; 
    activation->loss_prime = set_loss_prime;

    /* set loss function name */
    size_t loss_function_name_size = strlen(loss_function_name)+1;
    activation->loss_function_name = malloc(loss_function_name_size * sizeof(char)); 
    strcpy(activation->loss_function_name, loss_function_name);
    // loss_map_t val = map_loss_function(loss_function_name, 1); 

    /* create base layer type for activation */
    layer_t *layer = (layer_t*)malloc(sizeof(layer_t));
    layer->layer_type = (layer_obj_t*)malloc(sizeof(layer_obj_t)); 
    layer->layer_type->activation = activation;
    layer->forward = activation_forward;
    layer->update_params = update_activation;  
    layer->save = NULL;
    layer->load = NULL; 
    layer->save_layer_architecture = save_activation_architecture; 
    layer->input_size = set_input_size;
    layer->output_size = set_output_size; 
    layer->op_count = 1;

    /* set layer type name */
    size_t alias_size = strlen("loss")+1;
    layer->layer_name = malloc(alias_size * sizeof(char)); 
    strcpy(layer->layer_name, "loss");

    return layer;  
}


void save_activation_architecture(layer_t *activation, FILE *fp) {
    fprintf(
        fp, "[%s](%d, %d, %s)\n", 
        activation->layer_name,
        activation->input_size,
        activation->output_size,
        activation->layer_type->activation->loss_function_name
    );
} 
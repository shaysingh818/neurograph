#include "../data_structures/includes/matrix.h"
#include "includes/network.h"


net_t *init_network(double learning_rate, value_t *input) {
    net_t *nn = (net_t*)malloc(sizeof(net_t));
    nn->graph = create_graph(1.00); 
    nn->learning_rate = learning_rate;
    nn->num_layers = 2; 
    nn->layer_count = 0; 
    nn->front_index = nn->layer_count = 0; 
    nn->rear_index = nn->num_layers - 1; 
    nn->input = input; 

    /* allocate layers of the network */
    nn->layers = malloc(nn->num_layers * sizeof(layer_t*)); 
    for(int i = 0; i < nn->num_layers; i++){
        nn->layers[i] = malloc(sizeof(layer_t)); 
    }

    return nn; 
}


void layer(net_t *nn, layer_t *layer){

    /* queue insert method */
    if(nn->layer_count == nn->num_layers) {
        int new_size = nn->num_layers + nn->num_layers;
        nn->layers = realloc(nn->layers, new_size * sizeof(layer_t*)); 
        for(int i = nn->num_layers; i < new_size; i++){
            nn->layers[i] = malloc(sizeof(layer_t)); 
        }
        nn->num_layers = new_size; 
    }

    value_t *temp_inputs;
    if(nn->layer_count == 0){
        temp_inputs = nn->input; 
    } else {
        temp_inputs = nn->layers[nn->layer_count-1]->outputs;
    }

    nn->layers[nn->layer_count] = layer;
    nn->layers[nn->layer_count]->forward(
        nn->graph, 
        nn->layers[nn->layer_count], 
        temp_inputs
    );
    nn->layer_count  += 1;
}



void train(net_t *nn, int epochs, mat_t *y) {

    for(int i = 0; i < epochs; i++){

        forward_nodes(nn->graph);

        /* get output */
        int output_index = nn->graph->curr_index - 1;
        mat_t *output = nn->graph->operations[output_index]->mat_output; 
        double loss = mse(y, output);  
        mat_t *output_error = difference(y, output);
        if(NETWORK_DEBUG) {
            printf("Loss: %.2f\n", loss);
        }

        backward_nodes(nn->graph, output_error);
        update_network_params(nn); 
        
    }

} 


void update_network_params(net_t *nn) {
    int pass_index = nn->graph->curr_index-1;  
    for(int i = nn->num_layers-1; i >= 0; i--){
        nn->layers[i]->update_params(nn->graph, nn->layers[i], pass_index);  
        pass_index -= nn->layers[i]->op_count; 
    }
}


void save_model_params(net_t *nn, char *filepath){

    for(int i = 0; i < nn->num_layers; i++){

        /* make directory to store layer */
        char *value; 
        sprintf(value, "%s_%d", "layer", i); 
        printf("%s\n", value); 
    }

}



#include "../data_structures/includes/matrix.h"
#include "includes/network.h"
#include "includes/activations.h"

net_t *init_network(double learning_rate, int num_layers) {
    net_t *nn = (net_t*)malloc(sizeof(net_t));
    nn->learning_rate = learning_rate;
    nn->num_layers = num_layers; 
    nn->front_index = nn->layer_count = 0; 
    nn->rear_index = nn->num_layers - 1;  

    /* allocate layers of the network */
    nn->layers = malloc(nn->num_layers * sizeof(layer_t*)); 
    for(int i = 0; i < nn->num_layers; i++){
        nn->layers[i] = malloc(sizeof(layer_t)); 
    } 
    return nn; 
}


void add_layer(net_t *nn, int input_size, int output_size, bool activation){
    /* queue insert method */
    if(nn->layer_count == nn->num_layers) {
        printf("Max amount of layers added, increase layer count\n"); 
        return;
    } 

    nn->rear_index = (nn->rear_index+1) % nn->num_layers; 
    layer_t *layer = nn_layer(input_size, output_size, activation); 
    nn->layers[nn->rear_index] = layer; 
    nn->layer_count = nn->layer_count + 1; 
}


void train(net_t *nn, mat_t *x, mat_t *y, int epochs) {

    for(int i = 0; i < epochs; i++){

        /* forward */
        mat_t *forward_input = x; 
        for(int i = nn->front_index; i <= nn->rear_index; i++){
            mat_t *result = forward(nn->layers[i], forward_input);
            forward_input = copy_matrix(result);         
        }

        nn->loss = mse(y, forward_input);

        /* print loss */
        if(DEBUG) {
            printf(
                "Epoch: %d/%d  Error=%.4f\n",
                i+1, epochs, nn->loss
            ); 
        }

        /* Get derivative of error */
        mat_t *delta_error = difference(y, forward_input);

        /* backward */
        for(int n = nn->rear_index; n >= nn->front_index; n--){
            mat_t *result = backward(
                nn->layers[n], 
                delta_error, 
                nn->learning_rate
            );
            delta_error = copy_matrix(result);   
        }
    }
}

void debug(net_t *n){


}


mat_t *predict(net_t *nn, mat_t *x, mat_t *y){
    mat_t *forward_input = x; 
    for(int i = nn->front_index; i <= nn->rear_index; i++){
        mat_t *result = forward(nn->layers[i], forward_input);
        forward_input = copy_matrix(result);         
    }

    return forward_input; 
}
#include "../data_structures/includes/matrix.h"
#include "includes/network.h"
#include "includes/activations.h"


net_t *init_network(int num_layers, double learning_rate) {
    net_t *nn = (net_t*)malloc(sizeof(net_t));
    nn->learning_rate = learning_rate;
    nn->num_layers = num_layers; 
    nn->front_index = nn->layer_count = 0; 
    nn->rear_index = nn->num_layers - 1; 

    /* allocate layers of the network */
    nn->layers = malloc(nn->num_layers * sizeof(node_type_t*)); 
    for(int i = 0; i < nn->num_layers; i++){
        nn->layers[i] = malloc(sizeof(node_type_t)); 
    } 
    return nn; 
}


void layer(net_t *nn, node_type_t *layer_node){
    /* queue insert method */
    if(nn->layer_count == nn->num_layers) {
        printf("Max amount of layers added, increase layer count\n"); 
        return;
    } 

    nn->rear_index = (nn->rear_index+1) % nn->num_layers; 
    nn->layers[nn->rear_index] = layer_node; 
    nn->layer_count = nn->layer_count + 1; 
}



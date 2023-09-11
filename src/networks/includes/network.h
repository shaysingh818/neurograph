#ifndef NETWORK_H
#define NETWORK_H

#include "../../data_structures/includes/matrix.h"
#include "../../computation_graph/includes/computation_graph.h"
#include "../../computation_graph/includes/mse.h"
#include "layer.h"

#define DEBUG false
#define NETWORK_DEBUG false

struct Network {
    int num_layers, layer_count;
    int front_index, rear_index, pass_index;  
    double learning_rate, loss; 
    value_t *input;  
    computation_graph_t *graph; 
    layer_t **layers;  
}; 

typedef struct Network net_t; 

net_t *init_network(double learning_rate, value_t *inputs);
void layer(net_t *nn, layer_t *layer);
void train(net_t *nn, int epochs, mat_t *y);  
void update_network_params(net_t *nn);  


#endif
#ifndef NETWORK_H
#define NETWORK_H

#include "../../data_structures/includes/matrix.h"
#include "activations.h"
#include "computation_graph.h"

#define DEBUG false

struct Network {
    int num_layers, layer_count;
    int front_index, rear_index;  
    double learning_rate, loss;   
    node_type_t **layers; 
    node_type_t *front, *rear; 
}; 

typedef struct Network net_t; 

net_t *init_network(int num_layers, double learning_rate);
void layer(net_t *nn, node_type_t *layer_node);  
void train(net_t *nn, mat_t *x, mat_t *y, int epochs); 
void save_model(net_t *nn, char *file_path);
void debug(net_t *n);

/* test predictions */
mat_t *predict(net_t *nn, mat_t *x, mat_t *y); 


#endif
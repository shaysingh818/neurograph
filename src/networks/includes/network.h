#ifndef NETWORK_H
#define NETWORK_H

#include "../../data_structures/includes/matrix.h"
#include "../../computation_graph/includes/computation_graph.h"
#include "../../computation_graph/includes/loss.h"
#include "layer.h"

#define DEBUG false
#define NETWORK_DEBUG false

struct Network {
    int num_layers, layer_count, batch_size;
    int front_index, rear_index, pass_index;  
    double learning_rate, loss;
    bool batched;  
    value_t *input; 
    mat_t **input_batches;  
    computation_graph_t *graph; 
    layer_t **layers;  
}; 

typedef struct Network net_t; 

/* network methods */
net_t *init_network(double learning_rate, value_t *input, int batch_size);

void layer(net_t *nn, layer_t *layer);
void train(net_t *nn, int epochs, mat_t *y); 
void batch_train(net_t *nn, int epochs, mat_t *y);  
void update_network_params(net_t *nn);
void predict(net_t *nn, mat_t *input, mat_t *expected_output); 

/* save model */
void save_model_params(net_t *nn, char *filepath);
void load_model_params(net_t *n, char *filepath);   

/* Loading model archtectures */
net_t *load_model_architecture(char *model_architecture_path, value_t *inputs);



#endif
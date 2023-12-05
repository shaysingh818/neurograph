#ifndef NETWORK_H
#define NETWORK_H

#include <dirent.h>
#include "../../data_structures/list/includes/array.h"
#include "../../data_structures/matrix/includes/matrix.h"
#include "../../computation_graph/includes/computation_graph.h"
#include "../../computation_graph/includes/loss.h"
#include "../../extractors/dataframe/includes/utils.h"
#include "../../extractors/dataframe/includes/re.h"

#include "layer.h"

#define DEBUG false
#define NETWORK_DEBUG true

struct Network {
    int num_layers, layer_count, batch_size;
    int front_index, rear_index, pass_index;  
    double learning_rate, loss;
    bool batched; 
    mat_t **input_batches;  
    value_t *input; 
    layer_t **layers; 
    computation_graph_t *graph; 
}; 

typedef struct Network net_t; 

/* network methods */
net_t *init_network(double learning_rate, value_t *input, int batch_size);

/* network helper methods  */
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
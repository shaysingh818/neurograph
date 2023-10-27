#ifndef LAYER_H
#define LAYER_H

#include "../../data_structures/matrix/includes/matrix.h"
#include "../../computation_graph/includes/computation_graph.h"
#include "../../computation_graph/includes/ops.h"
#include "../../computation_graph/includes/loss.h"
#include "layer_types.h"
#include <sys/stat.h>

#define DEBUG false


union LayerObject {
    linear_t *linear; 
    activation_t *activation; 
}; 

typedef union LayerObject layer_obj_t;


struct Layer {
    char *layer_name;
    int input_size, output_size, op_count;
    layer_obj_t *layer_type;
    value_t *inputs, *outputs; 
	value_t *(*forward)(computation_graph_t *graph, struct Layer *layer, value_t *prev_output); 
	value_t *(*update_params)(computation_graph_t *graph, struct Layer *layer, int op_index);
    void (*save)(struct Layer *layer, char *filepath);
    void (*load)(struct Layer *layer, char *filepath);
    void (*save_layer_architecture)(struct Layer *layer, FILE *fp);
    void (*load_layer_architecture)(struct Layer *layer, FILE *fp); 
}; 

typedef struct Layer layer_t;

void serialize_layer(char *filepath, layer_t *layer); 
void deserialize_layer(char *filepath, layer_t *layer); 

/* linear methods */
value_t *linear_forward(computation_graph_t *graph, layer_t *layer, value_t *prev_output);
value_t *update_linear(computation_graph_t *graph, layer_t *layer, int op_index);
layer_t *linear(int set_input_size, int set_output_size);
void save_linear(layer_t *linear, char *filepath);
void load_linear(layer_t *linear, char *filepath); 
void save_linear_architecture(layer_t *linear, FILE *fp); 
void set_linear_inputs(layer_t *linear, mat_t *input); 

/* loss layer methods */
value_t *activation_forward(computation_graph_t *graph, layer_t *layer, value_t *prev_output); 
value_t *update_activation(computation_graph_t *graph, layer_t *layer, int op_index);
layer_t *activation(
    int set_input_size, int set_output_size,
    char *loss_function_name,
    double(*set_loss)(double val),
    mat_t*(*set_loss_prime)(mat_t *val)
);
void save_activation_architecture(layer_t *activation, FILE *fp);  





#endif

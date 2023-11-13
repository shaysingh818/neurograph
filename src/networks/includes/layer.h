#ifndef LAYER_H
#define LAYER_H

#include "../../data_structures/map/includes/table.h"
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
    struct Layer *(*load)(char *filepath);
}; 

typedef struct Layer layer_t;

/* loss function map */
hash_table_t *loss_map();
hash_table_t *layer_map();  

/* linear methods */
value_t *linear_forward(computation_graph_t *graph, layer_t *layer, value_t *prev_output);
value_t *update_linear(computation_graph_t *graph, layer_t *layer, int op_index);
layer_t *linear(int set_input_size, int set_output_size);
layer_t *load_linear(char *filepath); 
void save_linear(layer_t *linear, char *filepath);
void set_linear_inputs(layer_t *linear, mat_t *input); 

/* loss layer methods */
value_t *activation_forward(computation_graph_t *graph, layer_t *layer, value_t *prev_output); 
value_t *update_activation(computation_graph_t *graph, layer_t *layer, int op_index);
layer_t *activation(int set_input_size, int set_output_size, char *loss_function_name);
layer_t *load_activation(char *filepath); 
void save_activation(layer_t *linear, char *filepath); 





#endif

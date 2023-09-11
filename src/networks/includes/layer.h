#ifndef LAYER_H
#define LAYER_H

#include "../../data_structures/includes/matrix.h"
#include "../../computation_graph/includes/computation_graph.h"
#include "../../computation_graph/includes/mat_ops.h"
#include "../../computation_graph/includes/tanh.h"
#include "layer_types.h"

#define DEBUG false

union LayerObject {
    linear_t *linear; 
    activation_t *activation; 
}; 

typedef union LayerObject layer_obj_t;


struct Layer {
    layer_obj_t *layer_type;
    value_t *inputs, *outputs; 
    int input_size, output_size, op_count; 
	value_t *(*forward)(computation_graph_t *graph, struct Layer *layer, value_t *prev_output); 
	value_t *(*update_params)(computation_graph_t *graph, struct Layer *layer, int op_index);
}; 

typedef struct Layer layer_t;


value_t *linear_forward(computation_graph_t *graph, layer_t *layer, value_t *prev_output);
value_t *update_linear(computation_graph_t *graph, layer_t *layer, int op_index);
layer_t *linear(int set_input_size, int set_output_size); 


value_t *activation_forward(computation_graph_t *graph, layer_t *layer, value_t *prev_output); 
value_t *update_activation(computation_graph_t *graph, layer_t *layer, int op_index); 
layer_t *activation(
    int set_input_size, int set_output_size,
    void(*set_loss)(value_t *val),
    void(*set_loss_prime)(value_t *val)
);






#endif

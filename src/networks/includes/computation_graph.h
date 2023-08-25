#ifndef COMPUTATION_GRAPH_H
#define COMPUTATION_GRAPH_H

#include <math.h>
#include "activations.h"
#include "../../data_structures/includes/matrix.h"

typedef enum {LINEAR, LOSS} layer_type_t;


struct NodeType {
    layer_type_t layer_type; 
    void *node_structure; 
}; 

typedef struct NodeType node_type_t; 


struct CNode {
    int input_size, output_size; 
    mat_t *inputs, *outputs, *gradients; 
	void(*forward)(void*, mat_t*); 
	void(*backward)(void*, mat_t*); 
};

typedef struct CNode c_node_t; 

/* Node Type Methods */
node_type_t *init_node_type(layer_type_t layer_type, void *node); 
node_type_t **init_nodes(int length); 
void add_c_node(node_type_t **nodes, node_type_t *node, int index); 
void forward_all(node_type_t **nodes, int length, mat_t *inputs); 
void backward_all(node_type_t **nodes, int length, mat_t *output_error); 


/* linear node */
struct Linear {
    c_node_t *node; 
    mat_t *weights, *biases;
    double learning_rate; 
}; 

typedef struct Linear linear_t; 


/* linear node methods */
void linear_forward(void *linear_ptr, mat_t *set_inputs);
void linear_backward(void *linear_ptr, mat_t *output_delta); 
linear_t *linear(int input_size,int output_size, double learning_rate);
void debug_linear(linear_t *linear);


/* loss layer node */
struct Loss {
    c_node_t *node; 
	double(*loss)(double value); 
	mat_t*(*loss_prime)(mat_t *inputs);
}; 

typedef struct Loss loss_t; 


/* loss methods  */
void loss_forward(void *loss_ptr, mat_t *set_inputs);
void loss_backward(void *loss_ptr, mat_t *output_error);
loss_t *loss(
    int input_size, int output_size, 
    double(*loss)(double value),
    mat_t*(*loss_prime)(mat_t *inputs)
); 
void debug_loss(loss_t *loss);


#endif
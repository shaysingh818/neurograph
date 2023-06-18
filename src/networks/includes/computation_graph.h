#ifndef COMPUTATION_GRAPH_H
#define COMPUTATION_GRAPH_H

#include <math.h>
#include "../../data_structures/includes/matrix.h"
#include "activations.h"

typedef enum {
    LINEAR,
    LOSS
} LayerType; 


struct CNode {
    int input_size, output_size; 
    mat_t *inputs, *outputs, *gradients; 
	void(*forward)(void*, mat_t*); 
	void(*backward)(void*, mat_t*); 
};

typedef struct CNode c_node_t; 


/* linear node */
struct Linear {
    c_node_t *node; 
    mat_t *weights, *biases;
    double learning_rate; 
}; 

typedef struct Linear linear_t; 


/* linear node methods */
linear_t *linear(int input_size,int output_size, double learning_rate);
void feedforward(void *linear_ptr, mat_t *set_inputs);
void backprop(void *linear_ptr, mat_t *output_delta); 
void debug_linear(linear_t *linear); 



/* loss layer node */
struct Loss {
    c_node_t *node; 
	double(*loss)(double value); 
	mat_t*(*loss_prime)(mat_t *inputs); 
}; 

typedef struct Loss loss_t; 


/* loss methods  */
loss_t *loss(
    int input_size, int output_size, 
    double(*loss)(double value),
    mat_t*(*loss_prime)(mat_t *inputs)
); 
void feedforward_activation(void *loss_ptr, mat_t *set_inputs);
void backward_activation(void *loss_ptr, mat_t *output_error);
void debug_loss(loss_t *loss);



#endif
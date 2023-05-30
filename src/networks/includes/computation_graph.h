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
    mat_t *inputs, *outputs; 
	void(*forward)(void*); 
	void(*backward)(void*); 
};

typedef struct CNode c_node_t; 


struct Linear {
    c_node_t *node; 
    mat_t *weights, *biases; 
}; 

typedef struct Linear linear_t; 


struct Loss {
    c_node_t *node; 
	double(*loss)(double value); 
	mat_t*(*loss_prime)(mat_t *inputs); 
}; 

typedef struct Loss loss_t; 

/* linear methods */
linear_t *linear(mat_t *inputs, int input_size, int output_size);
void feedforward(void *linear_ptr);
void debug_linear(linear_t *linear); 

/* loss methods */
loss_t *loss(
    mat_t *inputs, int input_size, int output_size, 
    double(*loss)(double value),
    mat_t*(*loss_prime)(mat_t *inputs)
); 
void feedforward_activation(void *loss_ptr);
void debug_loss(loss_t *loss);


/* General computation graph methods */
void forward_all(void *nodes[]); 
void backward_all(void *nodes[]); 

#endif
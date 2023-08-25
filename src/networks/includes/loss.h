#ifndef LOSS_H
#define LOSS_H

#include <math.h>
#include "computation_graph.h"
#include "activations.h"

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
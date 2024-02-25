#ifndef OPERATION_H
#define OPERATION_H

#include "computation.h"

// SCALAR OPS

/* add */
node_t *_add(computation_graph_t *g, node_t *inputs[], int inputs_size);
void *_add_forward(void *graph, int node_id);
void *_add_backward(void *graph, int node_id);

/* multiply */
node_t *_multiply(computation_graph_t *g, node_t *inputs[], int input_size);
void *_mult_forward(void *graph, int node_id);
void *_mult_backward(void *graph, int node_id);

/* tanh */
node_t *_tanh(computation_graph_t *g, node_t *inputs[], int input_size);
void *_tanh_forward(void *graph, int node_id);
void *_tanh_backward(void *graph, int node_id);

// NDARARY OPS 

/* dot */
node_t *nd_dot(computation_graph_t *g, node_t *inputs[], int inputs_size);
void *dot_forward(void *graph, int node_id);
void *dot_backward(void *graph, int node_id);

/* scale add */
node_t *nd_scale_add(computation_graph_t *g, node_t *inputs[], int inputs_size);
void *nd_scale_add_forward(void *graph, int node_id);
void *nd_scale_add_backward(void *graph, int node_id);

/* apply loss */
node_t *nd_apply_loss(
    computation_graph_t *g, 
    node_t *inputs[], 
    int inputs_size,
    double(*loss)(double val),
    ndarray_t*(*loss_prime)(ndarray_t *val)
);
void *nd_apply_loss_forward(void *graph, int node_id);
void *nd_apply_loss_backward(void *graph, int node_id);


#endif
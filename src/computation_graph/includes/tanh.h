#ifndef TANH_H
#define TANH_H

#include "value.h"

double tanh_activation(double x);
mat_t *tanh_prime(mat_t *x); 
void tanh_forward(value_t *val); 
void tanh_backward(value_t *val); 


#endif
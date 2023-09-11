#ifndef SIGMOID_H
#define SIGMOID_H

#include "value.h"

double sigmoid(double x);
mat_t *sigmoid_prime(mat_t *x);
value_t *sigmoid_forward(value_t *val); 
value_t *sigmoid_backward(value_t *val); 


#endif
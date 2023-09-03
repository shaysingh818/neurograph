#ifndef ACTIVATIONS_H
#define ACTIVATIONS_H

#include <math.h>
#include "../../data_structures/includes/matrix.h"

double sigmoid(double x);
mat_t *sigmoid_prime(mat_t *x);

double tanh_activation(double x);
mat_t *tanh_prime(mat_t *x); 

double mse(mat_t *y_true, mat_t *y_pred);
mat_t *mse_prime(mat_t *y_true, mat_t *y_pred);  


#endif
#ifndef LOSS_H
#define LOSS_H

#include "../../data_structures/matrix/includes/matrix.h"
#include "value.h"

/* Tanh */
double tanh_activation(double x); 
mat_t *tanh_prime(mat_t *x);

/* Sigmoid */
double sigmoid(double x);
mat_t *sigmoid_prime(mat_t *x);

/* MSE */
double mse(mat_t *y_true, mat_t *y_pred);
mat_t *mse_prime(mat_t *y_true, mat_t *y_pred); 

#endif
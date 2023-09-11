#ifndef MSE_H
#define MSE_H

#include "value.h"

double mse(mat_t *y_true, mat_t *y_pred);
mat_t *mse_prime(mat_t *y_true, mat_t *y_pred);  

#endif
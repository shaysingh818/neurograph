#include "includes/mse.h"

double mse(mat_t *y_true, mat_t *y_pred) {
    double sum = 0.0; 
    for(int i = 0; i < y_true->rows; i++){
        for(int j = 0; j < y_true->cols; j++){
            double diff = y_true->arr[i][j] - y_pred->arr[i][j]; 
            sum += diff * diff; 
        }
    }
    return sum / (y_true->rows * y_true->cols);
}

mat_t *mse_prime(mat_t *y_true, mat_t *y_pred) {
    mat_t *result = init_vec(y_true->rows, y_true->cols, false); 
    for(int i = 0; i < y_true->rows; i++){
        for(int j = 0; j < y_true->cols; j++){
            double diff = y_true->arr[i][j] - y_pred->arr[i][j]; 
            result->arr[i][j] = 2.0 * (diff) / (y_true->rows * y_true->cols); 
        }
    }
    return result; 
}
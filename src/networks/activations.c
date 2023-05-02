#include "includes/activations.h"

// Sigmoid function
double sigmoid(double x) {
    return 1.0 / (1.0 + exp(-x));
}


double tanh_activation(double x) {
    return tanh(x); 
}


double mse(mat_t *y_true, mat_t *y_pred) {
    double sum = 0.0; 
    for(int i = 0; i < y_true->rows; i++){
        for(int j = 0; j < y_true->cols; j++){
            double diff = y_true->arr[i][j] - y_pred->arr[i][j]; 
            sum += diff * diff; 
        }
    }
    double mse = sum / (y_true->rows * y_true->cols); 
}


mat_t *sigmoid_prime(mat_t *x) {
    mat_t *result = init_vec(x->rows, x->cols, false); 
    for(int i = 0; i < x->rows; i++){
        for(int j = 0; j < x->cols; j++){
            double sig_x = sigmoid(x->arr[i][j]);
            result->arr[i][j] = sig_x * (1 - sig_x); 
        }
    }  
    return result; 
}


mat_t *tanh_prime(mat_t *x){
    mat_t *result = init_vec(x->rows, x->cols, false); 
    for(int i = 0; i < x->rows; i++){
        for(int j = 0; j < x->cols; j++){
            double tanh_x = tanh(x->arr[i][j]); 
            result->arr[i][j] = 1.0 - pow(tanh_x, 2.0); 
        }
    }
    return result; 
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

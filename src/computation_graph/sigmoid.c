#include "includes/sigmoid.h"


// Sigmoid function
double sigmoid(double x) {
    return 1.0 / (1.0 + exp(-x));
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


void sigmoid_forward(value_t *val) {
    val->mat_output = apply(sigmoid, val->left->mat_output); 
    if(FORWARD_DEBUG){
        print_vec(val->left->mat_output); 
        printf("Sigmoid \n\n"); 
        print_vec(val->mat_output);
    }
}


void sigmoid_backward(value_t *val) {
    val->mat_x_d_grad = sigmoid_prime(val->left->mat_output); 
    if(FORWARD_DEBUG){
        print_vec(val->left->mat_output); 
        printf("Sigmoid \n\n"); 
        print_vec(val->mat_output);
    }
} 
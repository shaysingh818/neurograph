#include "includes/tanh.h"


double tanh_activation(double x) {
    return tanh(x); 
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


void tanh_forward(value_t *val) {
    val->mat_output = apply(tanh_activation, val->left->mat_output); 
    if(FORWARD_DEBUG){
        print_vec(val->left->mat_output); 
        printf("Sigmoid \n\n"); 
        print_vec(val->mat_output);
    }
}


void tanh_backward(value_t *val) {
    val->mat_x_d_grad = tanh_prime(val->left->mat_output); 
    if(FORWARD_DEBUG){
        print_vec(val->left->mat_output); 
        printf("Sigmoid \n\n"); 
        print_vec(val->mat_output);
    }
} 
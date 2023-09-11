#include "includes/test_layer.h"

void test_linear_layer() { 

    layer_t *l1 = linear(2, 3); 
    assert(l1->layer_type->linear->weights->mat_output->rows == 2); 
    assert(l1->layer_type->linear->weights->mat_output->cols == 3); 
    assert(l1->layer_type->linear->biases->mat_output->rows == 1); 
    assert(l1->layer_type->linear->biases->mat_output->cols == 3);

    printf("%s::%s... \e[0;32mPASSED\e[0m\n", __FILE__, __FUNCTION__);

}


void test_activation_layer() {

    layer_t *l1 = activation(
        2, 3, 
        tanh_forward, 
        tanh_backward
    );

    assert(l1->layer_type->activation->input_size == 2); 
    assert(l1->layer_type->activation->output_size == 3);

    printf("%s::%s... \e[0;32mPASSED\e[0m\n", __FILE__, __FUNCTION__);

}



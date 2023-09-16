#include "includes/test_nn_train.h"


void test_train_save_nn_params() { 

	/* neural net library  */
    double learning_rate = 0.1; 
    double inputs[4][2] = {{0,0},{0,1},{1,0},{1,1}};
    double outputs[4][1] = {{0},{1},{1},{0}};

    /* create x input */
    mat_t *x = copy_arr_to_matrix(4, 2, inputs); 
    mat_t *y = copy_arr_to_matrix(4, 1, outputs);
    value_t *input = input_node_mat(x);
    net_t *nn = init_network(learning_rate, input);

    /* define model architecture */
    layer(nn, linear(2, 3));
    layer(nn, activation(2, 3, tanh_forward, tanh_backward)); 
    layer(nn, linear(3, 1)); 
    layer(nn, activation(3, 1, tanh_forward, tanh_backward));
    train(nn, 1000, y);

    /* get output */
    int output_index = nn->graph->curr_index - 1;
    mat_t *output = nn->graph->operations[output_index]->mat_output;
    print_vec(output);  

}	

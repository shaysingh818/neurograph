#include "includes/test_nn_train.h"


void test_train_diabetes_model() { 

	/* neural net library  */
    double learning_rate = 0.09;

    /* load data into data frame */ 
    frame_t *f = init_frame("../../examples/data/iris.csv", 1024, 150);
    assert(f->status == true);
    f_cols(f);
    end_line_terminate(f->headers[f->header_count-1]->name); 
    printf("Test: %s", f->headers[f->header_count-1]->name); 

    array_t *input_cols = init_array(); 
    insert_char(input_cols, "f1"); 
    insert_char(input_cols, "f2"); 
    insert_char(input_cols, "f3"); 
    insert_char(input_cols, "f4"); 

    mat_t *inputs = frame_to_mat(f, input_cols);
    value_t *input = value(inputs);
    printf("\n\n"); 

    /* create output matrix */
    array_t *output_cols = init_array(); 
    insert_char(output_cols, "f5"); 
    mat_t *outputs = frame_to_mat(f, output_cols);


    // /* create network model */
    net_t *nn = init_network(learning_rate, input, 4); 
    layer(nn, linear(4, 5));
    layer(nn, activation(4, 5, "tanh", tanh, tanh_prime)); 
    layer(nn, linear(5, 1)); 
    layer(nn, activation(5, 1, "tanh", tanh, tanh_prime));
    batch_train(nn, 9000, outputs);

    mat_t **x_train = batch_matrix(input->val, 4); 
    mat_t **y_train = batch_matrix(outputs, 4);


    int row = 49; 
    set_linear_inputs(nn->layers[0], x_train[row]);
    forward_nodes(nn->graph);

    printf("Curr Input\n"); 
    print_vec(x_train[row]);

    printf("Input: \n"); 
    print_vec(nn->layers[0]->outputs->left->left->val);

    printf("Expected output\n"); 
    print_vec(y_train[row]); 
    printf("\n"); 

    int output_index = nn->graph->curr_index - 1;
    mat_t *output = nn->graph->nodes[output_index]->val;
    print_vec(output); 

    // printf("Test\n"); 


}	

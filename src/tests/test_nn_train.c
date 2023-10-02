#include "includes/test_nn_train.h"


void test_train_diabetes_model() { 

	/* neural net library  */
    double learning_rate = 0.1;

    /* load data into data frame */ 
    frame_t *f = init_frame("../../examples/data/asthma.csv", 1024, 100);
    assert(f->status == true);
    f_cols(f); 

    // // /* create input matrix */
    char *input_cols[100] = {
        "Dry-Cough", 
        "Difficulty-in-Breathing", 
        "Pains", 
        "Nasal-Congestion", 
        "Runny-Nose"
    }; 
    mat_t *inputs = frame_to_mat(f, input_cols, 5);

    mat_t **values = batch_rows(inputs, 100); 
    //value_t *input = input_node_mat(inputs);
    for(int i = 0; i < 100; i++){
        print_vec(values[i]); 
        printf("\n"); 
    }

    /* create output matrix */
    // char *output_cols[100] = {"Severity_Moderate"}; 
    // mat_t *outputs = frame_to_mat(f, output_cols, 1);

    // // /* create network model */
    // net_t *nn = init_network(learning_rate, input); 
    // layer(nn, linear(5, 6));
    // layer(nn, activation(5, 6, "tanh", tanh_forward, tanh_backward)); 
    // layer(nn, linear(6, 1)); 
    // layer(nn, activation(6, 1, "tanh", tanh_forward, tanh_backward));
    // train(nn, 3000, outputs);
    // // forward_nodes(nn->graph);

    // int output_index = nn->graph->curr_index - 1;
    // mat_t *output = nn->graph->operations[output_index]->mat_output;
    // print_vec(output); 

    printf("Test\n"); 


}	

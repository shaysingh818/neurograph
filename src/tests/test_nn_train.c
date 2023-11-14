#include "includes/test_nn_train.h"


void test_train_iris_model() { 

	/* neural net library  */
    double learning_rate = 0.09;

    /* load data into data frame */ 
    frame_t *f = dataframe("../../examples/data/iris.csv", 1024, 150, NULL);
    assert(f->status == true);
    // end_line_terminate(f->headers[f->header_count-1]->label); 

    array_t *input_cols = init_array(); 
    insert_char(input_cols, "f1"); 
    insert_char(input_cols, "f2"); 
    insert_char(input_cols, "f3"); 
    insert_char(input_cols, "f4"); 

    mat_t *inputs = frame_to_matrix(f, input_cols);
    value_t *input = value(inputs);

    /* create output matrix */
    array_t *output_cols = init_array(); 
    insert_char(output_cols, "f5"); 
    mat_t *outputs = frame_to_matrix(f, output_cols);


    // /* create network model */
    net_t *nn = init_network(learning_rate, input, 4); 
    layer(nn, linear(4, 5));
    layer(nn, activation(4, 5, "tanh")); 
    layer(nn, linear(5, 1)); 
    layer(nn, activation(5, 1, "tanh"));
    batch_train(nn, 3000, outputs);

    mat_t **x_train = batch_matrix(input->val, 4); 
    mat_t **y_train = batch_matrix(outputs, 4);

    int row = 49;
	predict(nn, x_train[row], y_train[row]); 	

}	



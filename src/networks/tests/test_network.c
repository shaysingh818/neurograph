#include "includes/test_network.h"

void test_init_network() {

    double learning_rate = 0.1; 
    double inputs[4][2] = {{0,0},{0,1},{1,0},{1,1}};
    double outputs[4][1] = {{0},{1},{1},{0}};

    /* create x input */
    mat_t *x = copy_arr_to_matrix(4, 2, inputs); 
    mat_t *y = copy_arr_to_matrix(4, 1, outputs);
    value_t *input = input_node_mat(x);
    net_t *nn = init_network(learning_rate, input);

    char *expected_ops[100] = {
        "mat_mul", "scale_add_mat", 
        "apply_loss",
        "mat_mul", "scale_add_mat", 
        "apply_loss"
    };

    /* define model architecture */
    layer(nn, linear(2, 3));
    layer(nn, activation(2, 3, "tanh", tanh_forward, tanh_backward)); 
    layer(nn, linear(3, 1)); 
    layer(nn, activation(3, 1, "tanh", tanh_forward, tanh_backward));

    forward_nodes(nn->graph); 

    assert(nn->graph->curr_index == 6); 
    assert(nn->layer_count == 4); 

    for(int i = 0; i < nn->graph->curr_index; i++){
        char *op = nn->graph->operations[i]->alias; 
        bool condition = strcmp(op, expected_ops[i]) == 0; 
        assert(condition == true); 
    } 

    printf("%s::%s... \e[0;32mPASSED\e[0m\n", __FILE__, __FUNCTION__);
}


void test_add_layer() {

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
    assert(nn->num_layers == 2); 
    assert(nn->layer_count == 1);  

    layer(nn, activation(2, 3, "tanh", tanh_forward, tanh_backward));
    assert(nn->num_layers == 2); 
    assert(nn->layer_count == 2);  

    layer(nn, linear(3, 1));
    assert(nn->num_layers == 4); 
    assert(nn->layer_count == 3);  

    layer(nn, activation(3, 1, "tanh", tanh_forward, tanh_backward));
    assert(nn->num_layers == 4); 
    assert(nn->layer_count == 4); 

    printf("%s::%s... \e[0;32mPASSED\e[0m\n", __FILE__, __FUNCTION__);

}

void test_train() {

    bool equality_status = true;
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
    layer(nn, activation(2, 3, "tanh", tanh_forward, tanh_backward)); 
    layer(nn, linear(3, 1)); 
    layer(nn, activation(3, 1, "tanh", tanh_forward, tanh_backward));
    train(nn, 1000, y);

    // assert(nn->layers[0]->inputs->mat_output->rows == )

    assert(nn->num_layers == 4);  

    int output_index = nn->graph->curr_index - 1;
    mat_t *output = nn->graph->operations[output_index]->mat_output; 

    double v0 = output->arr[0][0], v1 = output->arr[1][0], v2 = output->arr[2][0], v3 = output->arr[3][0]; 
    bool condition = (v0 < v1 && v0 < v2) && (v3 < v1 && v3 < v2); 
    assert(condition); 

    printf("%s::%s... \e[0;32mPASSED\e[0m\n", __FILE__, __FUNCTION__);

}


void test_save_model_params() {

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
    layer(nn, activation(2, 3, "tanh", tanh_forward, tanh_backward)); 
    layer(nn, linear(3, 1)); 
    layer(nn, activation(3, 1, "tanh", tanh_forward, tanh_backward));
    train(nn, 1000, y);

    /* save model parameters from each layer */
    save_model_params(nn, "../../examples/models/testnet");   

    char *expected_paths[100] = {
        "../../examples/models/testnet/layer_0/weights",
        "../../examples/models/testnet/layer_0/biases", 
        "../../examples/models/testnet/layer_2/weights",
        "../../examples/models/testnet/layer_2/biases" 
    }; 

    /* Params for first layer */
    mat_t *w1 = load_matrix(expected_paths[0]);
    assert(w1->rows == 2 && w1->cols == 3); 

    mat_t *b1 = load_matrix(expected_paths[1]); 
    assert(b1->rows == 1 && b1->cols == 3); 

    /* Params for second layer */
    mat_t *w2 = load_matrix(expected_paths[2]);
    assert(w2->rows == 3 && w2->cols == 1);  

    mat_t *b2 = load_matrix(expected_paths[3]);
    assert(b2->rows == 1 && b2->cols == 1); 

    printf("%s::%s... \e[0;32mPASSED\e[0m\n", __FILE__, __FUNCTION__);
}


void test_load_model_params() {

    double learning_rate = 0.1; 
    double inputs[4][2] = {{0,0},{0,1},{1,0},{1,1}};
    double outputs[4][1] = {{0},{1},{1},{0}};

    /* create x input */
    mat_t *x = copy_arr_to_matrix(4, 2, inputs); 
    mat_t *y = copy_arr_to_matrix(4, 1, outputs);
    value_t *input = input_node_mat(x);

    /* model architecture */
    net_t *nn = init_network(learning_rate, input);
    layer(nn, linear(2, 3));
    layer(nn, activation(2, 3, "tanh", tanh_forward, tanh_backward)); 
    layer(nn, linear(3, 1)); 
    layer(nn, activation(3, 1, "tanh", tanh_forward, tanh_backward));


    /* load parameters */
    load_model_params(nn, "../../examples/models/testnet");
    forward_nodes(nn->graph); 

    /* output index */
    int output_index = nn->graph->curr_index - 1;
    mat_t *output = nn->graph->operations[output_index]->mat_output;

    /* assert values */
    double v0 = output->arr[0][0], v1 = output->arr[1][0], v2 = output->arr[2][0], v3 = output->arr[3][0]; 
    bool condition = (v0 < v1 && v0 < v2) && (v3 < v1 && v3 < v2); 
    assert(condition); 

    printf("%s::%s... \e[0;32mPASSED\e[0m\n", __FILE__, __FUNCTION__);

} 
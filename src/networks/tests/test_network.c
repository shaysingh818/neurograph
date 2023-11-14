#include "includes/test_network.h"

void test_init_network() {

    double learning_rate = 0.1; 
    double inputs[4][2] = {{0,0},{0,1},{1,0},{1,1}};
    double outputs[4][1] = {{0},{1},{1},{0}};

    /* create x input */
    mat_t *x = copy_arr_to_matrix(4, 2, inputs); 
    mat_t *y = copy_arr_to_matrix(4, 1, outputs);
    value_t *input = value(x);
    net_t *nn = init_network(learning_rate, input, 0);

    char *expected_ops[100] = {
        "mat_mul", "scale_add", 
        "apply_loss",
        "mat_mul", "scale_add", 
        "apply_loss"
    };

    /* define model architecture */
    layer(nn, linear(2, 3));
    layer(nn, activation(2, 3, "tanh")); 
    layer(nn, linear(3, 1)); 
    layer(nn, activation(3, 1, "tanh"));
    forward_nodes(nn->graph); 


    assert(nn->graph->curr_index == 6); 
    assert(nn->layer_count == 4); 

    for(int i = 0; i < nn->graph->curr_index; i++){
        char *op = nn->graph->nodes[i]->alias; 
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
    value_t *input = value(x);
    net_t *nn = init_network(learning_rate, input, 0);

    /* define model architecture */
    layer(nn, linear(2, 3));
    assert(nn->num_layers == 2); 
    assert(nn->layer_count == 1);  

    layer(nn, activation(2, 3, "tanh"));
    assert(nn->num_layers == 2); 
    assert(nn->layer_count == 2);  

    layer(nn, linear(3, 1));
    assert(nn->num_layers == 4); 
    assert(nn->layer_count == 3);  

    layer(nn, activation(3, 1, "tanh"));
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
    value_t *input = value(x);
    net_t *nn = init_network(learning_rate, input, 0);

    /* define model architecture */
    layer(nn, linear(2, 3));
    layer(nn, activation(2, 3, "tanh")); 
    layer(nn, linear(3, 1)); 
    layer(nn, activation(3, 1, "tanh"));
    train(nn, 5000, y);

    // assert(nn->layers[0]->inputs->val->rows == )

    assert(nn->num_layers == 4);  

    int output_index = nn->graph->curr_index - 1;
    mat_t *output = nn->graph->nodes[output_index]->val; 

    double v0 = output->arr[0][0], v1 = output->arr[1][0], v2 = output->arr[2][0], v3 = output->arr[3][0]; 
    bool condition = (v0 < v1 && v0 < v2) && (v3 < v1 && v3 < v2); 
    assert(condition); 

    printf("%s::%s... \e[0;32mPASSED\e[0m\n", __FILE__, __FUNCTION__);

}


void test_batch_train() {

    bool equality_status = true;
    double learning_rate = 0.1; 

    /* emulate batch size training  */
    double inputs[8][2] = {
        {0,0},{0,1},{1,0},{1,1},
        {0,0},{1,1},{1,0},{0,1}
    };

    double outputs[8][1] = {
        {0},{1},{1},{0},
        {0},{0},{1},{1}
    };

    /* create x input */
    mat_t *x = copy_arr_to_matrix(8, 2, inputs); 
    mat_t *y = copy_arr_to_matrix(8, 1, outputs);
    value_t *input = value(x);
    net_t *nn = init_network(learning_rate, input, 4);

    /* define model architecture */
    layer(nn, linear(2, 3));
    layer(nn, activation(2, 3, "tanh")); 
    layer(nn, linear(3, 1)); 
    layer(nn, activation(3, 1, "tanh"));
    batch_train(nn, 4000, y); 

    mat_t **x_train = batch_matrix(x, 4); 
    mat_t **y_train = batch_matrix(y, 4);

    set_linear_inputs(nn->layers[0], x_train[0]);
    forward_nodes(nn->graph);  

    int output_index = nn->graph->curr_index - 1;
    mat_t *output = nn->graph->nodes[output_index]->val;

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
    char *model_path = "../../examples/models/testnet"; 

    /* create x input */
    mat_t *x = copy_arr_to_matrix(4, 2, inputs); 
    mat_t *y = copy_arr_to_matrix(4, 1, outputs);
    value_t *input = value(x);
    net_t *nn = init_network(learning_rate, input, 0);

    /* define model architecture */
    layer(nn, linear(2, 3));
    layer(nn, activation(2, 3, "tanh")); 
    layer(nn, linear(3, 1)); 
    layer(nn, activation(3, 1, "tanh"));
    train(nn, 1000, y);

    /* save model parameters from each layer */
    save_model_params(nn, model_path);  

    /* find expected paths */
    DIR *dir; 
    struct dirent *ent; 


    char *expected_files[100] = {
        "1_loss",
        "0_linear", 
        "2_linear",
        "3_loss",
        "architecture" 
    };

    for(int i = 0; i < 5; i++){

        char *test_path, curr_path; 
        size_t path_size = strlen(model_path)+1 + strlen(expected_files[i])+1; 
        test_path = malloc(path_size * sizeof(char)); 
        sprintf(test_path, "%s/%s", model_path, expected_files[i]);

        /* validate path exists */
        assert(access(test_path, F_OK) != -1); 
        
    }


    printf("%s::%s... \e[0;32mPASSED\e[0m\n", __FILE__, __FUNCTION__);
}


void test_load_model_params() {


    double learning_rate = 0.1; 
    double inputs[16][2] = {{0,0},{0,1},{1,0},{1,1}};
    double outputs[4][1] = {{0},{1},{1},{0}};
    char *model_path = "../../examples/models/testnet"; 

    /* create x input */
    mat_t *x = copy_arr_to_matrix(4, 2, inputs); 
    mat_t *y = copy_arr_to_matrix(4, 1, outputs);
    value_t *input = value(x);

    /* model architecture */
    net_t *nn = init_network(learning_rate, input, 0);
    load_model_params(nn, model_path);
    forward_nodes(nn->graph); 

    int output_index = nn->graph->curr_index - 1;
    mat_t *output = nn->graph->nodes[output_index]->val;

    /* assert values */
    double v0 = output->arr[0][0], v1 = output->arr[1][0], v2 = output->arr[2][0], v3 = output->arr[3][0]; 
    bool condition = (v0 < v1 && v0 < v2) && (v3 < v1 && v3 < v2); 
    assert(condition);

    /* remove the entire testnet */
    char cmd[100];
    sprintf(cmd, "rm -rf %s", model_path);
    int rm_result = system(cmd);
    assert(rm_result == 0);  

    printf("%s::%s... \e[0;32mPASSED\e[0m\n", __FILE__, __FUNCTION__);
} 
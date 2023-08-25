#include "includes/test_network.h"

void test_init_network() {

    int sizes[3] = {2,3,1}; 
    bool equality_status = true;
    double learning_rate = 0.1;  
    net_t *nn = init_network(4, learning_rate);

    assert(nn->num_layers == 4); 
    assert(nn->learning_rate == 0.1);  
    assert(nn->rear_index == 3 && nn->front_index == 0); 

    /* first MLP layer */
    linear_t *l1 = linear(2, 3, learning_rate);
    loss_t *loss1 = loss(2, 3, tanh, tanh_prime);

    /* second MLP layer */
    linear_t *l2 = linear(3, 1, learning_rate);
    loss_t *loss2 = loss(3, 1, tanh, tanh_prime);


    nn->layers[0]->layer_type = LINEAR; 
    nn->layers[0]->node_structure = l1; 

    nn->layers[1]->layer_type = LOSS; 
    nn->layers[1]->node_structure = loss1; 

    nn->layers[2]->layer_type = LINEAR; 
    nn->layers[2]->node_structure = l2; 

    nn->layers[3]->layer_type = LOSS; 
    nn->layers[3]->node_structure = loss2;

    /* check layers */
    assert(nn->layers[0]->layer_type == LINEAR); 
    assert(nn->layers[1]->layer_type == LOSS); 
    assert(nn->layers[2]->layer_type == LINEAR); 
    assert(nn->layers[3]->layer_type == LOSS); 

    printf("%s::%s... \e[0;32mPASSED\e[0m\n", __FILE__, __FUNCTION__);
}

void test_add_layer() {

    bool equality_status = true;
    double learning_rate = 0.1;  
    int num_layers = 4; 
    net_t *nn = init_network(num_layers, learning_rate);

    /* create network architecture here  */
    linear_t *l1 = linear(2, 3, learning_rate); 
    layer(nn, init_node_type(LINEAR, l1));

    assert(nn->layer_count == 1); 
    assert(nn->rear_index == 0);  

    loss_t *loss1 = loss(2, 3, tanh, tanh_prime);
    layer(nn, init_node_type(LOSS, loss1));

    assert(nn->layer_count == 2);  
    assert(nn->rear_index == 1);  

    linear_t *l2 = linear(3, 1, learning_rate);
    layer(nn, init_node_type(LINEAR, l2));

    assert(nn->layer_count == 3);  
    assert(nn->rear_index == 2);  

    loss_t *loss2 = loss(3, 1, tanh, tanh_prime);
    layer(nn, init_node_type(LOSS, loss2));

    assert(nn->layer_count == 4);  
    assert(nn->rear_index == 3);  

    /* validate layers are in network structure */
    assert(nn->layers[0]->layer_type == LINEAR); 
    assert(nn->layers[1]->layer_type == LOSS); 
    assert(nn->layers[2]->layer_type == LINEAR); 
    assert(nn->layers[3]->layer_type == LOSS); 

    printf("%s::%s... \e[0;32mPASSED\e[0m\n", __FILE__, __FUNCTION__);
}


void test_train() {

    double inputs[4][2] = {{0,0},{0,1},{1,0},{1,1}};
    double outputs[4][1] = {{0},{1},{1},{0}};

    mat_t *x = copy_arr_to_matrix(4, 2, inputs); 
    mat_t *y = copy_arr_to_matrix(4, 1, outputs);

    /* training data */
    mat_t **train_x = to_rows(x);
    mat_t **train_y = to_rows(y); 

    /* create network */
    double learning_rate = 0.1; 
    bool equality_status = true; 
    int epochs = 1000, num_layers = 4;
    net_t *nn = init_network(num_layers, learning_rate);

    /* create network architecture here  */
    linear_t *l1 = linear(2, 3, learning_rate); 
    layer(nn, init_node_type(LINEAR, l1));

    loss_t *loss1 = loss(2, 3, tanh, tanh_prime);
    layer(nn, init_node_type(LOSS, loss1));

    linear_t *l2 = linear(3, 1, learning_rate);
    layer(nn, init_node_type(LINEAR, l2));

    loss_t *loss2 = loss(3, 1, tanh, tanh_prime);
    layer(nn, init_node_type(LOSS, loss2));


    for(int i = 0; i < epochs; i++){
        
        forward_all(nn->layers, nn->layer_count,  x);

        /* get loss and output error */
        double loss = mse(y, loss2->node->outputs);  
        mat_t *output_error = difference(y, loss2->node->outputs);

        backward_all(nn->layers, nn->layer_count, output_error);

    }

    mat_t *a2 = loss2->node->outputs; 
    double v0 = a2->arr[0][0], v1 = a2->arr[1][0], v2 = a2->arr[2][0], v3 = a2->arr[3][0]; 

    bool condition = (v0 < v1 && v0 < v2) && (v3 < v1 && v3 < v2); 
    assert(condition);

    printf("%s::%s... \e[0;32mPASSED\e[0m\n", __FILE__, __FUNCTION__);
}

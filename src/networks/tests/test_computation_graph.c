#include "includes/test_computation_graph.h"
#include <assert.h>


void test_init_node_type() {

    bool equality_status = true;
    int weight_dims[4] = {2, 3, 1, 3};

    /* create linear node */
    double inputs[4][2] = {{0,0},{0,1},{1,0},{1,1}};
    double outputs[4][1] = {{0},{1},{1},{0}};

    /* create x input */
    mat_t *x = copy_arr_to_matrix(4, 2, inputs); 
    mat_t *y = copy_arr_to_matrix(4, 1, outputs);

    linear_t *l1 = linear(2, 3, 0.1);
    l1->node->forward(l1, x);
    void *linear_value = (void*)l1; 
    node_type_t *node_type = init_node_type(LINEAR, linear_value);

    loss_t *l2 = loss(3, 1, tanh, tanh_prime); 
    void *loss_value = (void*)l2; 
    node_type_t *node_type_loss = init_node_type(LOSS, loss_value); 

    node_type_t *node_types[2] = {node_type, node_type_loss};
    void *curr_node = linear_value; 

    for(int i = 0; i < 2; i++){

        switch(node_types[i]->layer_type){

            case LINEAR: ;
                linear_t *linear = (linear_t*)linear_value; 
                assert(linear->learning_rate <= 0.1); 
                assert(linear->weights->rows == 2 && linear->weights->cols == 3);
                assert(linear->biases->rows == 1 && linear->biases->cols == 3); 
                curr_node = (void*)linear; 
                break;

            case LOSS: ; 
                loss_t *loss = (loss_t*)loss_value; 
                double loss_output = loss->loss(1.00); 
		        double rounded_value = round(loss_output*100)/100; 
                assert(rounded_value == 0.76);

            default:
                break; 
        }
    } 


    if(!equality_status) {
        printf("%s::%s... FAILED\n", __FILE__, __FUNCTION__);
    } else {
        printf("%s::%s... \e[0;32mPASSED\e[0m\n", __FILE__, __FUNCTION__);
    } 

} 


void test_init_nodes() {

    bool equality_status = true;
    double learning_rate = 0.1; 
    node_type_t **nodes = init_nodes(4); 

    /* first MLP layer */
    linear_t *l1 = linear(2, 3, learning_rate);
    loss_t *loss1 = loss(2, 3, tanh, tanh_prime);

    /* second MLP layer */
    linear_t *l2 = linear(3, 1, learning_rate);
    loss_t *loss2 = loss(3, 1, tanh, tanh_prime);

    nodes[0]->layer_type = LINEAR; 
    nodes[0]->node_structure = l1; 

    nodes[1]->layer_type = LOSS; 
    nodes[1]->node_structure = loss1; 

    nodes[2]->layer_type = LINEAR; 
    nodes[2]->node_structure = l2; 

    nodes[3]->layer_type = LOSS; 
    nodes[3]->node_structure = loss2;

    assert(nodes[0]->layer_type == LINEAR && nodes[1]->layer_type == LOSS); 
    assert(nodes[2]->layer_type == LINEAR && nodes[3]->layer_type == LOSS); 

    linear_t *first = (linear_t*)nodes[0]->node_structure; 
    loss_t *second = (loss_t*)nodes[1]->node_structure; 
    linear_t *third = (linear_t*)nodes[2]->node_structure; 
    loss_t *fourth = (loss_t*)nodes[3]->node_structure; 

    assert(first->weights->rows == 2 && first->weights->cols == 3); 
    assert(first->biases->rows == 1 && first->biases->cols == 3);

    assert(third->weights->rows == 3 && third->weights->cols == 1); 
    assert(third->biases->rows == 1 && third->biases->cols == 1);

    /* validate loss functions */
    double second_rounded_value = round(second->loss(1.00)*100)/100;
    double fourth_rounded_value = round(fourth->loss(1.00)*100)/100; 
    assert(second_rounded_value == 0.76);
    assert(fourth_rounded_value == 0.76);

    if(!equality_status) {
        printf("%s::%s... FAILED\n", __FILE__, __FUNCTION__);
    } else {
        printf("%s::%s... \e[0;32mPASSED\e[0m\n", __FILE__, __FUNCTION__);
    } 

} 


void test_append_c_node(){

    bool equality_status = true;
    double learning_rate = 0.1; 
    node_type_t **nodes = init_nodes(4);
    
    /* validate adding nodes */
    linear_t *l1 = linear(2, 3, learning_rate);
    add_c_node(nodes, init_node_type(LINEAR, l1), 0); 

    assert(l1->weights->rows == 2 && l1->weights->cols == 3); 
    assert(l1->biases->rows == 1 && l1->biases->cols == 3); 
    assert(nodes[0]->layer_type == LINEAR); 

    loss_t *loss1 = loss(2, 3, tanh, tanh_prime);
    add_c_node(nodes, init_node_type(LOSS, loss1), 1);

    double rounded_val = round(loss1->loss(1.00)*100)/100; 
    assert(rounded_val == 0.76); 
    assert(nodes[1]->layer_type == LOSS); 

    linear_t *l2 = linear(3, 1, learning_rate);
    add_c_node(nodes, init_node_type(LINEAR, l2), 2);

    assert(l2->weights->rows == 3 && l2->weights->cols == 1); 
    assert(l2->biases->rows == 1 && l2->biases->cols == 1); 
    assert(nodes[2]->layer_type == LINEAR); 

    loss_t *loss2 = loss(3, 1, tanh, tanh_prime);
    add_c_node(nodes, init_node_type(LOSS, loss2), 3);

    rounded_val = round(loss2->loss(1.00)*100)/100; 
    assert(rounded_val == 0.76); 
    assert(nodes[3]->layer_type == LOSS);

    if(!equality_status) {
        printf("%s::%s... FAILED\n", __FILE__, __FUNCTION__);
    } else {
        printf("%s::%s... \e[0;32mPASSED\e[0m\n", __FILE__, __FUNCTION__);
    } 

}


void test_forward_all(){

    bool equality_status = true;
    double learning_rate = 0.1; 
    node_type_t **nodes = init_nodes(4);

    /* create linear node */
    double inputs[4][2] = {{0,0},{0,1},{1,0},{1,1}};
    double outputs[4][1] = {{0},{1},{1},{0}};

    /* create x input */
    mat_t *x = copy_arr_to_matrix(4, 2, inputs); 
    mat_t *y = copy_arr_to_matrix(4, 1, outputs);

    /* network architecture */
    linear_t *l1 = linear(2, 3, learning_rate);
    add_c_node(nodes, init_node_type(LINEAR, l1), 0); 

    loss_t *loss1 = loss(2, 3, tanh, tanh_prime);
    add_c_node(nodes, init_node_type(LOSS, loss1), 1);

    linear_t *l2 = linear(3, 1, learning_rate);
    add_c_node(nodes, init_node_type(LINEAR, l2), 2);

    loss_t *loss2 = loss(3, 1, tanh, tanh_prime);
    add_c_node(nodes, init_node_type(LOSS, loss2), 3);

    assert(l1->node->inputs == NULL && l1->node->outputs == NULL);
    assert(loss1->node->inputs == NULL && loss1->node->outputs == NULL);
    assert(l2->node->inputs == NULL && l2->node->outputs == NULL);
    assert(loss2->node->inputs == NULL && loss2->node->outputs == NULL);

    /* forward all methods */
    forward_all(nodes, 4,  x); 

    /* verify node inputs and outputs */
    assert(l1->node->inputs->rows == 4 && l1->node->inputs->cols == 2);  
    assert(l1->node->outputs->rows == 4 && l1->node->outputs->cols == 3);  

    assert(loss1->node->inputs->rows == 4 && loss1->node->inputs->cols == 3); 
    assert(loss1->node->outputs->rows == 4 && loss1->node->outputs->cols == 3);

    bool compare_loss = compare_matrix(loss1->node->inputs, loss1->node->outputs); 
    assert(compare_loss == false); 

    assert(l2->node->inputs->rows == 4 && l2->node->inputs->cols == 3);  
    assert(l2->node->outputs->rows == 4 && l2->node->outputs->cols == 1); 

    assert(loss2->node->inputs->rows == 4 && loss2->node->inputs->cols == 1);  
    assert(loss2->node->outputs->rows == 4 && loss2->node->outputs->cols == 1); 

    compare_loss = compare_matrix(loss2->node->inputs, loss2->node->outputs); 
    assert(compare_loss == false);

    if(!equality_status) {
        printf("%s::%s... FAILED\n", __FILE__, __FUNCTION__);
    } else {
        printf("%s::%s... \e[0;32mPASSED\e[0m\n", __FILE__, __FUNCTION__);
    } 

}


void test_backward_all(){

    bool equality_status = true;
    double learning_rate = 0.1; 
    node_type_t **nodes = init_nodes(4);

    /* create linear node */
    double inputs[4][2] = {{0,0},{0,1},{1,0},{1,1}};
    double outputs[4][1] = {{0},{1},{1},{0}};

    /* create x input */
    mat_t *x = copy_arr_to_matrix(4, 2, inputs); 
    mat_t *y = copy_arr_to_matrix(4, 1, outputs);

    /* network architecture */
    linear_t *l1 = linear(2, 3, learning_rate);
    add_c_node(nodes, init_node_type(LINEAR, l1), 0); 

    loss_t *loss1 = loss(2, 3, tanh, tanh_prime);
    add_c_node(nodes, init_node_type(LOSS, loss1), 1);

    linear_t *l2 = linear(3, 1, learning_rate);
    add_c_node(nodes, init_node_type(LINEAR, l2), 2);

    loss_t *loss2 = loss(3, 1, tanh, tanh_prime);
    add_c_node(nodes, init_node_type(LOSS, loss2), 3);

    /* forward all nodes */
    forward_all(nodes, 4,  x);

    /* get loss and output error */
    double loss = mse(y, loss2->node->outputs);  
    mat_t *output_error = difference(y, loss2->node->outputs);

    /* backward propagate all nodes */
    backward_all(nodes, 4, output_error);

    assert(loss2->node->gradients->rows == 4 && loss2->node->gradients->cols == 1); 
    assert(l2->node->gradients->rows == 4 && l2->node->gradients->cols == 3); 
    assert(loss1->node->gradients->rows == 4 && loss1->node->gradients->cols == 3); 
    assert(l1->node->gradients->rows == 4 && l1->node->gradients->cols == 2); 

    if(!equality_status) {
        printf("%s::%s... FAILED\n", __FILE__, __FUNCTION__);
    } else {
        printf("%s::%s... \e[0;32mPASSED\e[0m\n", __FILE__, __FUNCTION__);
    } 
}


void test_mlp() {

    bool equality_status = true; 
    int node_count = 2, epochs = 5000; 
    double learning_rate = 0.1;
    node_type_t **nodes = init_nodes(4);

    /* create linear node */
    double inputs[4][2] = {{0,0},{0,1},{1,0},{1,1}};
    double outputs[4][1] = {{0},{1},{1},{0}};

    /* create x input */
    mat_t *x = copy_arr_to_matrix(4, 2, inputs); 
    mat_t *y = copy_arr_to_matrix(4, 1, outputs);

    assert(x->rows == 4 && x->cols == 2); 
    assert(y->rows == 4 && y->cols == 1); 

    /* network architecture */
    linear_t *l1 = linear(2, 3, learning_rate);
    add_c_node(nodes, init_node_type(LINEAR, l1), 0); 

    loss_t *loss1 = loss(2, 3, tanh, tanh_prime);
    add_c_node(nodes, init_node_type(LOSS, loss1), 1);

    linear_t *l2 = linear(3, 1, learning_rate);
    add_c_node(nodes, init_node_type(LINEAR, l2), 2);

    loss_t *loss2 = loss(3, 1, tanh, tanh_prime);
    add_c_node(nodes, init_node_type(LOSS, loss2), 3);

    for(int i = 0; i < epochs; i++){
        
        forward_all(nodes, 4,  x);

        /* get loss and output error */
        double loss = mse(y, loss2->node->outputs);  
        mat_t *output_error = difference(y, loss2->node->outputs);

        backward_all(nodes, 4, output_error);

    }

    mat_t *a2 = loss2->node->outputs; 
    double v0 = a2->arr[0][0], v1 = a2->arr[1][0], v2 = a2->arr[2][0], v3 = a2->arr[3][0]; 

    bool condition = (v0 < v1 && v0 < v2) && (v3 < v1 && v3 < v2); 
    assert(condition);

    /* validate test results */
    if(!equality_status) {
        printf("%s::%s... FAILED\n", __FILE__, __FUNCTION__);
    } else {
        printf("%s::%s... \e[0;32mPASSED\e[0m\n", __FILE__, __FUNCTION__);
    } 
 
}


void test_dense() {

    bool equality_status = true; 
    int node_count = 2, epochs = 5000; 
    double learning_rate = 0.1;

    /* create linear node */
    double inputs[4][2] = {{0,0},{0,1},{1,0},{1,1}};
    double outputs[4][1] = {{0},{1},{1},{0}};

    /* create x input */
    mat_t *x = copy_arr_to_matrix(4, 2, inputs); 
    mat_t *y = copy_arr_to_matrix(4, 1, outputs);
     
    /* first MLP layer */
    linear_t *l1 = linear(2, 3, learning_rate);
    loss_t *loss1 = loss(2, 3, tanh, tanh_prime);

    /* second MLP layer */
    linear_t *l2 = linear(3, 3, learning_rate);
    loss_t *loss2 = loss(3, 3, tanh, tanh_prime);

    /* Compressed layer */
    linear_t *l3 = linear(3, 2, learning_rate);
    loss_t *loss3 = loss(3, 2, tanh, tanh_prime);

    /* Decompression layer  */
    linear_t *l4 = linear(2, 3, learning_rate);
    loss_t *loss4 = loss(2, 3, tanh, tanh_prime);

    /* third MLP layer */
    linear_t *l5 = linear(3, 3, learning_rate);
    loss_t *loss5 = loss(3, 3, tanh, tanh_prime);

    /* third MLP layer */
    linear_t *l6 = linear(3, 1, learning_rate);
    loss_t *loss6 = loss(3, 1, tanh, tanh_prime);


    for(int i = 0; i < epochs; i++){
        
        /* forward */
        l1->node->forward(l1, x);
        loss1->node->forward(loss1, l1->node->outputs);
        l2->node->forward(l2, loss1->node->outputs);
        loss2->node->forward(loss2, l2->node->outputs);
        l3->node->forward(l3, loss2->node->outputs);
        loss3->node->forward(loss3, l3->node->outputs);
        l4->node->forward(l4, loss3->node->outputs);
        loss4->node->forward(loss4, l4->node->outputs);
        l5->node->forward(l5, loss4->node->outputs);
        loss5->node->forward(loss5, l5->node->outputs);
        l6->node->forward(l6, loss5->node->outputs);
        loss6->node->forward(loss6, l6->node->outputs);

        /* get loss and output error */
        double loss = mse(y, loss3->node->outputs);  
        mat_t *output_error = difference(y, loss3->node->outputs);

        // /* backprop error */
        loss6->node->backward(loss6, output_error); 
        l6->node->backward(l6, loss6->node->gradients);
        loss5->node->backward(loss5, l6->node->gradients); 
        l5->node->backward(l5, loss5->node->gradients);
        loss4->node->backward(loss4, l5->node->gradients); 
        l4->node->backward(l4, loss4->node->gradients);
        loss3->node->backward(loss3, l4->node->gradients); 
        l3->node->backward(l3, loss3->node->gradients);
        loss2->node->backward(loss2, l3->node->gradients); 
        l2->node->backward(l2, loss2->node->gradients);
        loss1->node->backward(loss1, l2->node->gradients); 
        l1->node->backward(l1,loss1->node->gradients);

    }

    /* None of this is accurate, it's just to see if it's possible lol*/ 
    if(!equality_status) {
        printf("%s::%s... FAILED\n", __FILE__, __FUNCTION__);
    } else {
        printf("%s::%s... \e[0;32mPASSED\e[0m\n", __FILE__, __FUNCTION__);
    } 

}


void test_forward_nodes() {

    bool equality_status = true; 
    int node_count = 2, epochs = 5000; 
    double learning_rate = 0.1;

    /* create linear node */
    double inputs[4][2] = {{0,0},{0,1},{1,0},{1,1}};
    double outputs[4][1] = {{0},{1},{1},{0}};

    /* create x input */
    mat_t *x = copy_arr_to_matrix(4, 2, inputs); 
    mat_t *y = copy_arr_to_matrix(4, 1, outputs);
 
    /* first MLP layer */
    linear_t *l1 = linear(2, 3, learning_rate);
    loss_t *loss1 = loss(2, 3, tanh, tanh_prime);

    /* second MLP layer */
    linear_t *l2 = linear(3, 1, learning_rate);
    loss_t *loss2 = loss(3, 1, tanh, tanh_prime);


    /* forward hidden */
    // for(int i = 1; i < 3; i++){
    //     layers[i]->forward(layers[i], layers[i-1]->outputs); 
    // }

}
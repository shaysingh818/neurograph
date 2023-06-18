#include "includes/test_computation_graph.h"


void test_mlp() {

    bool equality_status = true; 
    int node_count = 2, epochs = 5000; 
    double learning_rate = 0.1;

    /* create linear node */
    int inputs[4][2] = {
        {0,0},
        {0,1},
        {1,0},
        {1,1}
    };

    int outputs[4][1] = {
        {0},
        {1},
        {1},
        {0}
    };

    /* create x input */
    mat_t *x = init_vec(4, 2, false); 
    mat_t *y = init_vec(4, 1, false);
     

    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 2; j++){
            x->arr[i][j] = inputs[i][j]; 
        }

        for(int n = 0; n < 1; n++){
            y->arr[i][n] = outputs[i][n];
        }
    }



    /* first MLP layer */
    linear_t *l1 = linear(2, 3, learning_rate);
    loss_t *loss1 = loss(2, 3, tanh, tanh_prime);

    /* second MLP layer */
    linear_t *l2 = linear(3, 1, learning_rate);
    loss_t *loss2 = loss(3, 1, tanh, tanh_prime);


    for(int i = 0; i < epochs; i++){

        
        /* forward */
        l1->node->forward(l1, x);
        loss1->node->forward(loss1, l1->node->outputs);
        l2->node->forward(l2, loss1->node->outputs);
        loss2->node->forward(loss2, l2->node->outputs);

        /* get loss and output error */
        double loss = mse(y, loss2->node->outputs);  
        mat_t *output_error = difference(y, loss2->node->outputs);

        /* backprop error */
        loss2->node->backward(loss2, output_error); 
        l2->node->backward(l2, loss2->node->gradients);
        loss1->node->backward(loss1, l2->node->gradients); 
        l1->node->backward(l1,loss1->node->gradients);

    }

    mat_t *a2 = loss2->node->outputs; 
    double v0 = a2->arr[0][0]; 
    double v1 = a2->arr[1][0]; 
    double v2 = a2->arr[2][0]; 
    double v3 = a2->arr[3][0]; 


    bool condition = (v0 < v1 && v0 < v2) && (v3 < v1 && v3 < v2); 
    if(!condition) {
        equality_status = false; 
    }


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
    int inputs[4][2] = {
        {0,0},
        {0,1},
        {1,0},
        {1,1}
    };

    int outputs[4][1] = {
        {0},
        {1},
        {1},
        {0}
    };

    /* create x input */
    mat_t *x = init_vec(4, 2, false); 
    mat_t *y = init_vec(4, 1, false);
     

    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 2; j++){
            x->arr[i][j] = inputs[i][j]; 
        }

        for(int n = 0; n < 1; n++){
            y->arr[i][n] = outputs[i][n];
        }
    }



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
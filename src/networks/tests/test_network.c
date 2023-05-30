#include "includes/test_network.h"

void test_init_network() {

    int sizes[3] = {2,3,1}; 
    bool equality_status = true;
    double learning_rate = 0.01;  
    net_t *nn = init_network(learning_rate, 3);

    if(nn->learning_rate != learning_rate){
        equality_status = false; 
    }    

    if(!equality_status) {
        printf("%s::%s... FAILED\n", __FILE__, __FUNCTION__);
    } else {
        printf("%s::%s... \e[0;32mPASSED\e[0m\n", __FILE__, __FUNCTION__);
    } 

}

void test_add_layer() {

    bool equality_status = true;
    double learning_rate = 0.1;  
    int num_layers = 4; 
    net_t *nn = init_network(learning_rate, num_layers);

    add_layer(nn, 2, 3, false); 
    add_layer(nn, 2, 3, true); 
    add_layer(nn, 3, 1, false); 
    add_layer(nn, 3, 1, true);

    /* store counts for each type of layer */
    int dense_counter = 0;
    int activation_counter = 0; 
    
    /* feed forward */
    for(int i = nn->front_index; i <= nn->rear_index; i++){
        if(nn->layers[i]->activation) {
            activation_counter += 1; 
        } else {
            dense_counter += 1; 
        }
    } 

    if(dense_counter != 2 && activation_counter != 2){
        equality_status = false; 
    } 

    if(!equality_status) {
        printf("%s::%s... FAILED\n", __FILE__, __FUNCTION__);
    } else {
        printf("%s::%s... \e[0;32mPASSED\e[0m\n", __FILE__, __FUNCTION__);
    } 

}


void test_train() {

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

    /* training data */
    mat_t **train_x = to_rows(x);
    mat_t **train_y = to_rows(y); 


    /* create network */
    double learning_rate = 0.1; 
    bool equality_status = true; 
    int epochs = 1000; 


    /* create collection of layers */
    int num_layers = 4;

    /* create instance of network */
    net_t *nn = init_network(learning_rate, num_layers);
    add_layer(nn, 2, 3, false); 
    add_layer(nn, 2, 3, true); 
    add_layer(nn, 3, 1, false); 
    add_layer(nn, 3, 1, true);


    for(int i = 0; i < epochs; i++){

        /* forward */
        mat_t *forward_input = x; 
        for(int i = nn->front_index; i <= nn->rear_index; i++){
            mat_t *result = forward(nn->layers[i], forward_input);
            forward_input = copy_matrix(result);         
        }

        nn->loss = mse(y, forward_input);

        /* Get derivative of error */
        mat_t *delta_error = difference(y, forward_input);

        /* backward */
        for(int n = nn->rear_index; n >= nn->front_index; n--){
            mat_t *result = backward(
                nn->layers[n], 
                delta_error, 
                nn->learning_rate
            );
            delta_error = copy_matrix(result);   
        }

    }

    /* predict */
    mat_t *result = predict(nn, x, y);

    if(nn->loss > 0.1) {
        equality_status = false; 
    } 


    if(!equality_status) {
        printf("%s::%s... FAILED\n", __FILE__, __FUNCTION__);
    } else {
        printf("%s::%s... \e[0;32mPASSED\e[0m\n", __FILE__, __FUNCTION__);
    } 


}

void test_loss() {


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

    //srand(time(NULL));


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

    /* training data */
    mat_t **train_x = to_rows(x);
    mat_t **train_y = to_rows(y); 

    bool equality_status = true; 
    int input_size = 2, hidden_size = 3, output_size = 1; 
    int epochs = 1000; 
    double learning_rate = 0.1; 
    double loss; 

    srand(time(NULL));

    mat_t *w1 = init_vec(input_size, hidden_size, false);
    mat_t *w2 = init_vec(hidden_size, output_size, false);
    mat_t *b1 = init_vec(1, hidden_size, false);
    mat_t *b2 = init_vec(1, output_size, false);


    randomize(w1, 2); 
    randomize(w2, 1);

    randomize(b1, 3); 
    randomize(b2, 1); 

    for(int i = 0; i < epochs; i++){

        /* forward */
        mat_t *z1 = scale_add(dot(x, w1), b1);
        mat_t *a1 = apply(tanh_activation, z1); 
        mat_t *z2 = scale_add(dot(a1, w2), b2); 
        mat_t *a2 = apply(tanh_activation, z2); 


        loss = mse(y, a2); 

        /* back prop*/
        mat_t *output_error = difference(y, a2); 
        mat_t *output_delta = elementwise_multiply(output_error, tanh_prime(z2));
        mat_t *hidden_error = dot(output_delta, transpose(w2));
        mat_t *hidden_delta = elementwise_multiply(hidden_error, tanh_prime(z1)); 


        mat_t *dw2 = scale(dot(transpose(a1), output_delta), learning_rate); 
        mat_t *dw1 = scale(dot(transpose(x), hidden_delta), learning_rate);
        mat_t *db2 = scale(output_delta, learning_rate); 
        mat_t *db1 = scale(hidden_delta, learning_rate); 

        w2 = add(w2, dw2); 
        w1 = add(w1, dw1);
        b2 = add(b2, db2); 
        b1 = add(b1, db1); 

    }

    /* check the loss value */
    if(loss > 0.1){
        equality_status = false; 
    }

    /* predict */
    mat_t *z1 = scale_add(dot(x, w1), b1); 
    mat_t *a1 = apply(tanh, z1); 
    mat_t *z2 = scale_add(dot(a1, w2), b1); 
    mat_t *a2 = apply(tanh, z2); 

    /* validate test results */
    if(!equality_status) {
        printf("%s::%s... FAILED\n", __FILE__, __FUNCTION__);
    } else {
        printf("%s::%s... \e[0;32mPASSED\e[0m\n", __FILE__, __FUNCTION__);
    } 


}


void test_network_train() {

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

    srand(time(NULL));


    bool equality_status = true; 
    double learning_rate = 0.1; 
    int epochs = 1000, num_layers = 4; 
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


    /* create instance of network */
    net_t *nn = init_network(learning_rate, num_layers);
    add_layer(nn, 2, 3, false); 
    add_layer(nn, 2, 3, true); 
    add_layer(nn, 3, 1, false); 
    add_layer(nn, 3, 1, true);


    /* fit and train */
    train(nn, x, y, epochs);

    /* predict */
    mat_t *result = predict(nn, x, y);

    if(nn->loss > 0.1) {
        equality_status = false; 
    }

    /* validate test results */
    if(!equality_status) {
        printf("%s::%s... FAILED\n", __FILE__, __FUNCTION__);
    } else {
        printf("%s::%s... \e[0;32mPASSED\e[0m\n", __FILE__, __FUNCTION__);
    } 

}


void test_base_concept() {


    /* create computation graph simple feed forward net */
    int network_depth = 2, epochs=10000; 
    double learning_rate = 0.1; 
    bool equality_status = true; 

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

    /* store wieghts, biases and outputs */
    mat_t **W = malloc(network_depth * sizeof(mat_t*));  // weights
    mat_t **b = malloc(network_depth * sizeof(mat_t*));  // biases

    for(int i = 0; i < network_depth; i++){
        W[i] = malloc(sizeof(mat_t)); 
        b[i] = malloc(sizeof(mat_t)); 
    }    

    /* require inputs and outputs */
    mat_t *x = init_matrix(4, 2);
    mat_t *y = init_matrix(4, 1); 

    for(int i = 0; i < x->rows; i++){
        for(int j = 0; j < x->cols; j++){
            x->arr[i][j] = inputs[i][j];
        }
    }

    for(int i = 0; i < y->rows; i++){
        for(int j = 0; j < y->cols; j++){
            y->arr[i][j] = outputs[i][j];
        }
    }
 
    /* require weight matrices of model */
    mat_t *w1 = init_matrix(2, 3); 
    mat_t *w2 = init_matrix(3, 1);
    randomize(w1, 2); 
    randomize(w2, 1);  


    /* require biase matrices of model */
    b[0] = init_matrix(1, 3); 
    b[1] = init_matrix(1, 3); 
    randomize(b[0], b[0]->rows); 
    randomize(b[1], b[1]->rows);  

    for(int i = 0; i < epochs; i++) {

        mat_t *z1 = dot(x, w1); 
        mat_t *a1 = apply(tanh, z1); 
        mat_t *z2 = dot(a1, w2); 
        mat_t *a2 = apply(tanh, z2); 


        double loss = mse(y, a2); 

        /* get output and expected output*/
        mat_t *output_error = difference(y, a2);
        mat_t *output_delta = elementwise_multiply(
            output_error, 
            tanh_prime(z2)
        ); 

        /* back propagate activation  */
        mat_t *hidden_error = dot(output_delta, transpose(w2));
        mat_t *hidden_delta = elementwise_multiply(
            hidden_error,
            tanh_prime(z1)
        );

        // /* adjust weights and biases */
        mat_t *dw2 = scale(dot(transpose(a1), output_delta), learning_rate);
        mat_t *dw1 = scale(dot(transpose(x), hidden_delta), learning_rate);

        w2 = add(w2, dw2); 
        w1 = add(w1, dw1);

    }

    mat_t *z1 = dot(x, w1);
    mat_t *a1 = apply(tanh, z1); 
    mat_t *z2 = dot(a1, w2); 
    mat_t *a2 = apply(tanh, z2); 

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
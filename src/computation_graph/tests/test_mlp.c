#include "includes/test_mlp.h"


void test_xor() {

    computation_graph_t *graph = create_graph(); 
    double inputs[4][2] = {{0,0},{1,1},{1,0},{0,1}};
    double outputs[4][1] = {{0},{0},{1},{1}};

    mat_t *x = copy_arr_to_matrix(4, 2, inputs); 
    mat_t *y = copy_arr_to_matrix(4, 1, outputs);
    value_t *input = value(x); 

    /* create mlp graph */
    value_t *w1 = value(init_matrix(2, 3));
    randomize(w1->val, w1->val->rows);

    value_t *b1 = value(init_matrix(1, 3)); 
    randomize(b1->val, b1->val->rows); 

    value_t *w2 = value(init_matrix(3, 1)); 
    randomize(w2->val, w2->val->rows); 

    value_t *b2 = value(init_matrix(1, 1)); 
    randomize(b2->val, b2->val->rows); 


    /* first layer */
    value_t *layer1 = scale_add_mat(
        graph,
        mat_mul(graph, input, w1),
        b1
    ); 

    /* second layer */
    value_t *act1 = apply_loss(
        graph,
        layer1,
        tanh_activation, 
        tanh_prime
    );

    /* first layer */
    value_t *layer2 = scale_add_mat(
        graph,
        mat_mul(graph, act1, w2),
        b2
    );

    /* second layer */
    value_t *act2 = apply_loss(
        graph,
        layer2,
        tanh_activation, 
        tanh_prime
    );

    /* train for 1000 epochs  */
    for(int i = 0; i < 1000; i++){

        /* forward and backward pass */
        forward_nodes(graph); 
        double loss = mse(y, act2->val);   
        mat_t *output_error = difference(y, act2->val);
        backward_nodes(graph, output_error);

        /* layer 2 */    
        b2->val = add(
            b2->val, 
            scale(layer2->left->upstream_gradient, 0.1)
        );

        w2->val = add(
            w2->val, 
            scale(layer2->left->right_grad, 0.1)
        );

        /* layer 1 */
        b1->val = add(
            b1->val, 
            scale(layer1->left->upstream_gradient, 0.1)
        );

        w1->val = add(
            w1->val, 
            scale(layer1->left->right_grad, 0.1)
        );

    }

    /* feed in different combos of inputs */
    forward_nodes(graph);
    int output_index = graph->curr_index - 1;
    mat_t *output = graph->nodes[output_index]->val;

    /* validate first output */
    double v0 = output->arr[0][0], v1 = output->arr[1][0], v2 = output->arr[2][0], v3 = output->arr[3][0]; 
    bool condition = (v0 < v2 && v0 < v3) && (v1 < v2 && v1 < v3); 
    assert(condition);
 
    double inputs2[4][2] = {{0,0},{0,1},{1,1},{1,0}};
    graph->nodes[0]->left->val = copy_arr_to_matrix(4, 2, inputs2);
    forward_nodes(graph); 
    output = graph->nodes[output_index]->val;

    /* validate second output */
    v0 = output->arr[0][0], v1 = output->arr[1][0], v2 = output->arr[2][0], v3 = output->arr[3][0]; 
    condition = (v0 < v1 && v0 < v3) && (v2 < v1 && v2 < v3); 
    assert(condition);

    printf("%s::%s... \e[0;32mPASSED\e[0m\n", __FILE__, __FUNCTION__);
} 

void train_mlp() {

    computation_graph_t *graph = create_graph(); 

    double inputs[8][2] = {
        {0,0},
        {0,1},
        {1,0},
        {1,1},
        {0,0},
        {1,1},
        {1,0},
        {0,1}
    };

    double outputs[8][1] = {
        {0},
        {1},
        {1},
        {0},
        {0},
        {0},
        {1},
        {1}
    };

    mat_t *x = copy_arr_to_matrix(8, 2, inputs); 
    mat_t *y = copy_arr_to_matrix(8, 1, outputs); 

    /* moment of truth */
    mat_t **x_train = batch_matrix(x, 4); 
    mat_t **y_train = batch_matrix(y, 4); 
    value_t *input = value(x_train[0]); 

    /* create mlp graph */
    value_t *w1 = value(init_matrix(2, 3));
    randomize(w1->val, w1->val->rows);

    value_t *b1 = value(init_matrix(1, 3)); 
    randomize(b1->val, b1->val->rows); 

    value_t *w2 = value(init_matrix(3, 1)); 
    randomize(w2->val, w2->val->rows); 

    value_t *b2 = value(init_matrix(1, 1)); 
    randomize(b2->val, b2->val->rows); 

    /* first layer */
    value_t *layer1 = scale_add_mat(
        graph,
        mat_mul(graph, input, w1),
        b1
    ); 

    /* second layer */
    value_t *act1 = apply_loss(
        graph,
        layer1,
        tanh_activation, 
        tanh_prime
    );

    /* first layer */
    value_t *layer2 = scale_add_mat(
        graph,
        mat_mul(graph, act1, w2),
        b2
    );

    /* second layer */
    value_t *act2 = apply_loss(
        graph,
        layer2,
        tanh_activation, 
        tanh_prime
    );



    for(int i = 0; i < 5000; i ++){

        int sample_count = x->rows - 4; 
        for(int n = 0; n < sample_count; n++){

            mat_t *curr_x = x_train[n]; 
            mat_t *curr_y = y_train[n];
            // graph->nodes[0]->left->val = curr_x;
            layer1->left->left->val = curr_x;  


            /* forward pass */
            forward_nodes(graph); 
            double loss = mse(curr_y, act2->val);   
            mat_t *output_error = difference(curr_y, act2->val);
            backward_nodes(graph, output_error);

            /* layer 2 */    
            b2->val = add(
                b2->val, 
                scale(layer2->left->upstream_gradient, 0.1)
            );

            w2->val = add(
                w2->val, 
                scale(layer2->left->right_grad, 0.1)
            );

            /* layer 1 */
            b1->val = add(
                b1->val, 
                scale(layer2->left->upstream_gradient, 0.1)
            );

            w1->val = add(
                w1->val, 
                scale(layer1->left->right_grad, 0.1)
            );

        }

    }

    printf("\n\n"); 
    printf("Input\n");

    graph->nodes[0]->left->val = x_train[0]; 
    print_vec(graph->nodes[0]->left->val); 
    forward_nodes(graph);


    int output_index = graph->curr_index - 1;
    mat_t *output = graph->nodes[output_index]->val;
    printf("Output\n"); 
    print_vec(output);  


}
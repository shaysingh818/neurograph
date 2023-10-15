#include "includes/test_graph.h"


void test_create_graph() {

    computation_graph_t *graph = create_graph(1.00); 
    assert(graph->curr_index == 0); 
    assert(graph->size == 2); 
    for(int i = 0; i < graph->size; i++){
        assert(graph->nodes[i] != NULL); 
    }  

    assert(graph->curr_index == 0);  
    printf("%s::%s... \e[0;32mPASSED\e[0m\n", __FILE__, __FUNCTION__);

}


void test_append_operation() {

    computation_graph_t *graph = create_graph(1.00);
    double inputs[4][2] = {{0,0},{0,1},{1,0},{1,1}};

    double exepected_mult_vals[4][3] = {
        {0, 0, 0},
        {2, 2, 2},
        {2, 2, 2},
        {4, 4, 4}
    };

    double exepected_scale_vals[4][3] = {
        {1, 1, 1},
        {3, 3, 3},
        {3, 3, 3},
        {5, 5, 5}
    }; 

    /* expression */
    value_t *biase = value(init_matrix(1, 3)); 
    value_t *weight = value(init_matrix(2, 3)); 
    value_t *input = value(copy_arr_to_matrix(4, 2, inputs));

    /* populate weights and biases */
    fill_mat(weight->val, 2); 
    fill_mat(biase->val, 1); 

    value_t *mult_op = mat_mul(graph, input, weight); 
    value_t *scale_op = scale_add_mat(graph, mult_op, biase); 

    /* forward the ops */
    mult_op->forward_operation(mult_op); 
    scale_op->forward_operation(scale_op);

    /* validate dims of output*/
    assert(mult_op->val->rows == 4); 
    assert(mult_op->val->cols == 3); 

    assert(scale_op->val->rows == 4); 
    assert(scale_op->val->cols == 3); 

    /* validate results */
    mat_t *mult_vals = copy_arr_to_matrix(4, 3, exepected_mult_vals); 
    mat_t *scale_vals = copy_arr_to_matrix(4, 3, exepected_scale_vals);

    bool mult_result = compare_matrix(mult_vals, mult_op->val); 
    bool scale_result = compare_matrix(scale_vals, scale_op->val); 

    assert(mult_result == true); 
    assert(scale_result == true); 

    printf("%s::%s... \e[0;32mPASSED\e[0m\n", __FILE__, __FUNCTION__);
}


void test_forward_nodes() {


    double inputs[4][2] = {{0,0},{0,1},{1,0},{1,1}};

    double expected_l1_vals[4][3] = {
        {1, 1, 1},
        {3, 3, 3},
        {3, 3, 3},
        {5, 5, 5}
    }; 

    double expected_a1_vals[4][3] = {
        {0.76, 0.76, 0.76},
        {1, 1, 1},
        {1, 1, 1},
        {1, 1, 1}
    }; 

    double expected_l2_vals[4][1] = {5.57, 6.97, 6.97, 7.00}; 
    double expected_a2_vals[4][1] = {1.00, 1.00, 1.00, 1.00}; 

    /* create graph */
    computation_graph_t *graph = create_graph(1.00);

    /* weights and biases for each layer  */
    value_t *input = value(copy_arr_to_matrix(4, 2, inputs));
    value_t *b1 = value(init_matrix(1, 3)); 
    value_t *w1 = value(init_matrix(2, 3)); 
    fill_mat(b1->val, 1); 
    fill_mat(w1->val, 2); 

    value_t *b2 = value(init_matrix(1, 1)); 
    value_t *w2 = value(init_matrix(3, 1)); 
    fill_mat(b2->val, 1); 
    fill_mat(w2->val, 2);


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

    forward_nodes(graph);

    mat_t *l1_vals = copy_arr_to_matrix(4, 3, expected_l1_vals); 
    assert(compare_matrix(l1_vals, layer1->val));  

    mat_t *a1_vals = copy_arr_to_matrix(4, 3, expected_a1_vals); 
    assert(compare_matrix(a1_vals, act1->val));  

    mat_t *l2_vals = copy_arr_to_matrix(4, 3, expected_l2_vals); 
    assert(compare_matrix(a1_vals, act1->val));  

    mat_t *a2_vals = copy_arr_to_matrix(4, 3, expected_l2_vals); 
    assert(compare_matrix(a1_vals, act1->val));  


    printf("%s::%s... \e[0;32mPASSED\e[0m\n", __FILE__, __FUNCTION__);
}


void test_backward_nodes() {

    double inputs[4][2] = {{0,0},{0,1},{1,0},{1,1}};
    double outputs[4][1] = {{0},{1},{1},{0}};

    double expected_l1_vals[4][3] = {
        {1, 1, 1},
        {3, 3, 3},
        {3, 3, 3},
        {5, 5, 5}
    }; 

    double expected_a1_vals[4][3] = {
        {0.76, 0.76, 0.76},
        {1, 1, 1},
        {1, 1, 1},
        {1, 1, 1}
    }; 

    double expected_l2_vals[4][1] = {5.57, 6.97, 6.97, 7.00}; 
    double expected_a2_vals[4][1] = {1.00, 1.00, 1.00, 1.00}; 

    /* create graph */
    computation_graph_t *graph = create_graph(1.00);

    /* weights and biases for each layer  */
    value_t *input = value(copy_arr_to_matrix(4, 2, inputs));
    value_t *b1 = value(init_matrix(1, 3)); 
    value_t *w1 = value(init_matrix(2, 3)); 
    fill_mat(b1->val, 1); 
    fill_mat(w1->val, 2); 

    value_t *b2 = value(init_matrix(1, 1)); 
    value_t *w2 = value(init_matrix(3, 1)); 
    fill_mat(b2->val, 1); 
    fill_mat(w2->val, 2);


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

    /* call forward and backward methods */
    forward_nodes(graph);

    /* get loss */
    mat_t *y = copy_arr_to_matrix(4, 1, outputs);
    double loss = mse(y, act2->val);   
    mat_t *output_error = difference(y, act2->val);

    backward_nodes(graph, output_error); 

    /* gradients layer 2*/
    mat_t *db2 = layer2->left->upstream_gradient; 
    mat_t *dw2 = layer2->left->right_grad; 

    /* gradients layer 1*/
    mat_t *db1 = layer1->left->upstream_gradient; 
    mat_t *dw1 = layer1->left->right_grad;

    /* validate dimensions */
    assert(db2->rows == 4 && db2->cols == 1); 
    assert(dw2->rows == 3 && dw2->cols == 1); 
    assert(db1->rows == 4 && db1->cols == 3); 
    assert(dw1->rows == 2 && dw1->cols == 3); 

    printf("%s::%s... \e[0;32mPASSED\e[0m\n", __FILE__, __FUNCTION__);

    printf("%s::%s... \e[0;32mPASSED\e[0m\n", __FILE__, __FUNCTION__);
}
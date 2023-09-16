#include "includes/test_mat_ops.h"
#include "../includes/tanh.h"
#include "../includes/mse.h"


void test_mlp_ops() {


    computation_graph_t *graph = create_graph(1.00); 
    double inputs[4][2] = {{0,0},{0,1},{1,0},{1,1}};
    double outputs[4][1] = {{0},{1},{1},{0}};

    /* create x input */
    mat_t *x = copy_arr_to_matrix(4, 2, inputs); 
    mat_t *y = copy_arr_to_matrix(4, 1, outputs);

    /* weights and biases for layer 1 */
    mat_t *w1 = init_matrix(2, 3);
    mat_t *b1 = init_matrix(1, 3);
    randomize(w1, w1->rows); 
    randomize(b1, b1->rows);

    /* weights and biases for layer 2 */
    mat_t *w2 = init_matrix(3, 1);
    mat_t *b2 = init_matrix(1, 1);
    randomize(w2, w2->rows); 
    randomize(b2, b2->rows);


    value_t *input = input_node_mat(x);
    value_t *weight1 = input_node_mat(w1);
    value_t *biase1 = input_node_mat(b1);


    value_t *weight2 = input_node_mat(w2);
    value_t *biase2 = input_node_mat(b2);


    value_t *layer1 = scale_add_mat( 
        graph, 
        mat_mul(graph, input, weight1),
        biase1
    );

    /* apply activation */
    value_t *act1 = apply_activation(
        graph,
        layer1,
        tanh_forward,
        tanh_backward
    );

    value_t *layer2 = scale_add_mat(
        graph, 
        mat_mul(graph, act1, weight2),
        biase2
    );

    /* apply activation */
    value_t *act2 = apply_activation(
        graph,
        layer2,
        tanh_forward,
        tanh_backward
    );

    for(int i = 0; i < 2000; i++){

        forward_nodes(graph);

        double loss = mse(y, act2->mat_output);  
        mat_t *output_error = difference(y, act2->mat_output);
        // printf("Loss: %.2f\n", loss);

        backward_nodes(graph, output_error); 

        /* layer 2 */    
        biase2->mat_output = add(
            biase2->mat_output, 
            scale(graph->operations[4]->mat_upstream_grad, 0.1)
        );

        weight2->mat_output = add(
            weight2->mat_output, 
            scale(graph->operations[3]->mat_y_d_grad, 0.1)
        );

        /* layer 1 */
        biase1->mat_output = add(
            biase1->mat_output, 
            scale(graph->operations[1]->mat_upstream_grad, 0.1)
        );

        weight1->mat_output = add(
            weight1->mat_output, 
            scale(graph->operations[0]->mat_y_d_grad, 0.1)
        );


    }


    int output_index = graph->curr_index - 1;
    mat_t *output = graph->operations[output_index]->mat_output; 

    double v0 = output->arr[0][0], v1 = output->arr[1][0], v2 = output->arr[2][0], v3 = output->arr[3][0]; 
    bool condition = (v0 < v1 && v0 < v2) && (v3 < v1 && v3 < v2); 
    assert(condition);

    printf("%s::%s... \e[0;32mPASSED\e[0m\n", __FILE__, __FUNCTION__);


} 
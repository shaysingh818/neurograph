#include "includes/test_mat_ops.h"


void test_mat_multiply() {


    computation_graph_t *graph = create_graph(8, 1.00); 
    double inputs[4][2] = {{0,0},{0,1},{1,0},{1,1}};
    double outputs[4][1] = {{0},{1},{1},{0}};

    /* create x input */
    mat_t *x = copy_arr_to_matrix(4, 2, inputs); 
    mat_t *y = copy_arr_to_matrix(4, 1, outputs);

    /* weights and biases for layer 1 */
    mat_t *w1 = init_matrix(2, 3);
    mat_t *b1 = init_matrix(3, 1);
    randomize(w1, w1->rows); 
    randomize(b1, b1->rows); 

    value_t *input = input_node_mat(x);
    value_t *weight1 = input_node_mat(w1);
    value_t *biase1 = input_node_mat(b1);

    value_t *output = scale_add_mat(
        graph, 
        mat_mul(graph, input, weight1),
        biase1
    );

    forward_nodes(graph); 

    print_vec(graph->operations[0]->mat_output); 
    printf("\n");  
    print_vec(graph->operations[1]->mat_output);  



} 
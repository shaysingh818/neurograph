#include "includes/test_ops.h"


void test_mat_mult() {


    computation_graph_t *graph = create_graph(); 
    double inputs[4][2] = {{0,0},{0,1},{1,0},{1,1}};
    mat_t *x = copy_arr_to_matrix(4, 2, inputs); 
    mat_t *weights = init_matrix(2, 3); 
    fill_mat(weights, 2); 

    value_t *mult_op = mat_mul(graph, value(x), value(weights)); 
    
    /* assert values are set */
    bool compare_left = compare_matrix(mult_op->left->val, x); 
    bool compare_right = compare_matrix(mult_op->right->val, weights);
    assert(compare_left == true && compare_right == true); 

    /* call forward */
    mult_op->forward_operation(mult_op); 

    double exepected_mult_vals[4][3] = {
        {0, 0, 0},
        {2, 2, 2},
        {2, 2, 2},
        {4, 4, 4}
    };

    mat_t *mult_output = copy_arr_to_matrix(4, 3, exepected_mult_vals); 
    assert(compare_matrix(mult_output, mult_op->val)); 

    mat_t *mock_upstream_grad = init_matrix(4, 3); 
    fill_mat(mock_upstream_grad, 2); 
    mult_op->upstream_gradient = mock_upstream_grad; 

    /* call backward */
    mult_op->backward_operation(mult_op);

    mat_t *mock_left_grad = init_matrix(4, 2); 
    fill_mat(mock_left_grad, 12); 

    mat_t *mock_right_grad = init_matrix(2, 3); 
    fill_mat(mock_right_grad, 4);

    /* validate grads */
    assert(compare_matrix(mult_op->left_grad, mock_left_grad));
    assert(compare_matrix(mult_op->right_grad, mock_right_grad));
    assert(mult_op->left_grad->rows == 4); 
    assert(mult_op->left_grad->cols == 2); 
    assert(mult_op->right_grad->rows == 2); 
    assert(mult_op->right_grad->cols == 3); 

    printf("%s::%s... \e[0;32mPASSED\e[0m\n", __FILE__, __FUNCTION__);

}
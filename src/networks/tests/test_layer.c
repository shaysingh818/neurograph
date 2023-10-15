#include "includes/test_layer.h"




void test_linear_layer() { 

    layer_t *l1 = linear(2, 3); 
    assert(l1->layer_type->linear->weights->val->rows == 2); 
    assert(l1->layer_type->linear->weights->val->cols == 3); 
    assert(l1->layer_type->linear->biases->val->rows == 1); 
    assert(l1->layer_type->linear->biases->val->cols == 3);


    /* test forward */


    /* test backward update params */

    printf("%s::%s... \e[0;32mPASSED\e[0m\n", __FILE__, __FUNCTION__);

}


void test_save_linear_layer() {

    layer_t *l1 = linear(2, 3); 
    assert(l1->layer_type->linear->weights->val->rows == 2); 
    assert(l1->layer_type->linear->weights->val->cols == 3); 
    assert(l1->layer_type->linear->biases->val->rows == 1); 
    assert(l1->layer_type->linear->biases->val->cols == 3);

    /* setup paths */
    char *path = "../../examples/models/layers/linear"; 
    char weight_path[100], biase_path[100]; 

    /* call save method */
    save_linear(l1, path);

    int layer_path_access = access(path, F_OK) == 0; 
    assert(layer_path_access == true); 

    /* format weight and biase paths */
    sprintf(weight_path, "%s/%s", path, "weights"); 
    sprintf(biase_path, "%s/%s", path, "biases");

    int weight_path_access = access(weight_path, F_OK) == 0; 
    assert(weight_path_access == true); 

    int biase_path_access = access(biase_path, F_OK) == 0; 
    assert(biase_path_access == true); 

    mat_t *weights = load_matrix(weight_path);
    mat_t *biases = load_matrix(biase_path);
    assert(weights->rows == 2 && weights->cols == 3); 
    assert(biases->rows == 1 && biases->cols == 3);

    /* remove directory */
    char cmd[32];
    sprintf(cmd, "rm -rf %s", path);
    int rm_result = system(cmd);
    assert(rm_result == 0);  

    printf("%s::%s... \e[0;32mPASSED\e[0m\n", __FILE__, __FUNCTION__);

} 


void test_activation_layer() {

    layer_t *l1 = activation(
        2, 3, "tanh",  
        tanh_activation, 
        tanh_prime
    );

    /* matrix values */
    double expected_vals[2][3] = {
        {0.96, 0.96, 0.96},
        {0.96, 0.96, 0.96}
    };

    /* convert to matrix representation */ 
    mat_t *expct = copy_arr_to_matrix(2, 3, expected_vals); 

    /* test loss functions  */
    mat_t *x = init_vec(2, 3, false);
    mat_t *y = init_vec(2, 3, false);

    /* create mock values */
    value_t *mock_value = value(x);
    value_t *mock_value_two = value(y);

    /* set mock value attributes */
    mock_value->left = mock_value;
    mock_value->upstream_gradient = mock_value->val;  

    mock_value_two->left = mock_value_two;
    mock_value_two->upstream_gradient = expct;  

    fill_mat(x, 2);
    fill_mat(y, 1);

    /* set inputs outputs */
    l1->inputs = mock_value; 
    l1->outputs = mock_value;

    assert(l1->layer_type->activation->input_size == 2); 
    assert(l1->layer_type->activation->output_size == 3);

    apply(l1->layer_type->activation->loss, l1->inputs->val);
    l1->layer_type->activation->loss_prime(l1->inputs->val);

    // /* compare matrix values once done */
    // bool compare_mat = compare_matrix(expct, mock_value->val); 
    // assert(compare_mat == true); 

    // bool compare_mock_two = compare_matrix(y, mock_value_two->val); 
    // assert(compare_mock_two == true); 

    printf("%s::%s... \e[0;32mPASSED\e[0m\n", __FILE__, __FUNCTION__);

}
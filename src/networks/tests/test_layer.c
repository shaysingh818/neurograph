#include "includes/test_layer.h"


void test_loss_dict() {

    /* expected outputs */
    double expected_vals[2][3] = {
        {0.96, 0.96, 0.96},
        {0.96, 0.96, 0.96}
    };

    double expected_deriv_vals[2][3] = {
        {0.07, 0.07, 0.07},
        {0.07, 0.07, 0.07}
    };

    double expected_sig_vals[2][3] = {
        {0.88, 0.88, 0.88},
        {0.88, 0.88, 0.88}
    };

    /* matrix conversion */
    mat_t *expct = copy_arr_to_matrix(2, 3, expected_vals); 
    mat_t *expct_prime = copy_arr_to_matrix(2, 3, expected_deriv_vals); 
    mat_t *expct_sig = copy_arr_to_matrix(2, 3, expected_sig_vals); 

    /* create instance of linear layer */
    mat_t *outputs  = init_vec(2, 3, false);
    fill_mat(outputs, 2); 

    /* test loss map/dictionary */
    hash_table_t *loss_table = loss_map(); 
    loss_value_t *tanh_value = lookup_table_key(loss_table, "tanh"); 
    loss_value_t *sigmoid_value = lookup_table_key(loss_table, "sigmoid"); 

    /* tanh results */
    mat_t *tanh_result = apply(tanh_value->loss, outputs); 
    mat_t *tanh_prime_result = tanh_value->loss_prime(outputs); 

    bool compare_tanh = compare_matrix(tanh_result, expct); 
    bool compare_tanh_prime = compare_matrix(tanh_prime_result, expct_prime);

    assert(compare_tanh); 
    assert(compare_tanh_prime); 

    /* sigmoid results */
    mat_t *sigmoid_result = apply(sigmoid_value->loss, outputs); 
    mat_t *sigmoid_prime_result = sigmoid_value->loss_prime(outputs);
    
    bool compare_sigmoid = compare_matrix(sigmoid_result, expct_sig);

    printf("%s::%s... \e[0;32mPASSED\e[0m\n", __FILE__, __FUNCTION__);
}


void test_linear_layer() { 

    layer_t *l1 = linear(2, 3); 
    assert(l1->layer_type->linear->weights->val->rows == 2); 
    assert(l1->layer_type->linear->weights->val->cols == 3); 
    assert(l1->layer_type->linear->biases->val->rows == 1); 
    assert(l1->layer_type->linear->biases->val->cols == 3);

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

    printf("%s::%s... \e[0;32mPASSED\e[0m\n", __FILE__, __FUNCTION__);

} 


void test_load_linear_layer() {

    char *path = "../../examples/models/layers/linear";
    char *path_str = malloc(strlen(path)+1 * sizeof(char));
    strcpy(path_str, path); 

    layer_t *l1 = load_linear(path_str);
    assert(l1->layer_type->linear->weights->val->rows == 2); 
    assert(l1->layer_type->linear->weights->val->cols == 3); 
    assert(l1->layer_type->linear->biases->val->rows == 1); 
    assert(l1->layer_type->linear->biases->val->cols == 3);

    // /* remove directory */
    
    printf("%s::%s... \e[0;32mPASSED\e[0m\n", __FILE__, __FUNCTION__);

} 

void test_activation_layer() {

    layer_t *l1 = activation(2, 3, "tanh");

    /* matrix values */
    double expected_vals[2][3] = {
        {0.96, 0.96, 0.96},
        {0.96, 0.96, 0.96}
    };

    /* matrix values */
    double expected_deriv_vals[2][3] = {
        {0.07, 0.07, 0.07},
        {0.07, 0.07, 0.07}
    };

    /* convert to matrix representation */ 
    mat_t *expct = copy_arr_to_matrix(2, 3, expected_vals); 
    mat_t *expct_derivs = copy_arr_to_matrix(2, 3, expected_deriv_vals); 

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

    mat_t *result = apply(l1->layer_type->activation->loss, l1->inputs->val);
    mat_t *result_derivs = l1->layer_type->activation->loss_prime(l1->inputs->val);

    /* compare result value itself */
    bool compare = compare_matrix(expct, result); 
    assert(compare); 

    /* compare the derivative values */
    bool compare_deriv = compare_matrix(expct_derivs, result_derivs); 
    assert(compare_deriv); 

    printf("%s::%s... \e[0;32mPASSED\e[0m\n", __FILE__, __FUNCTION__);

}


void test_save_activation_layer() {

    layer_t *l1 = activation(2, 3, "tanh");

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

    /* apply loss and it's derivative */
    apply(l1->layer_type->activation->loss, l1->inputs->val);
    l1->layer_type->activation->loss_prime(l1->inputs->val);

    /* call save method */
    char *path = "../../examples/models/layers/activation";
    save_activation(l1, path);

    printf("%s::%s... \e[0;32mPASSED\e[0m\n", __FILE__, __FUNCTION__);

} 


void test_load_activation_layer() {


    char *path = "../../examples/models/layers/activation";
    char *path_str = malloc(strlen(path)+1 * sizeof(char));
    strcpy(path_str, path); 

    layer_t *l1 = load_activation(path);
 
    /* matrix values */
    double expected_vals[2][3] = {
        {0.96, 0.96, 0.96},
        {0.96, 0.96, 0.96}
    };

    /* matrix values */
    double expected_deriv_vals[2][3] = {
        {0.07, 0.07, 0.07},
        {0.07, 0.07, 0.07}
    };

    /* convert to matrix representation */ 
    mat_t *expct = copy_arr_to_matrix(2, 3, expected_vals); 
    mat_t *expct_deriv = copy_arr_to_matrix(2, 3, expected_deriv_vals); 

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

    /* apply loss and it's derivative */
    mat_t *result = apply(l1->layer_type->activation->loss, l1->inputs->val);
    bool compare_mock = compare_matrix(expct, result); 
    assert(compare_mock); 

    mat_t *result_deriv = l1->layer_type->activation->loss_prime(l1->inputs->val); 
    bool compare_mock_two = compare_matrix(result_deriv, expct_deriv); 
    assert(compare_mock_two); 

    printf("%s::%s... \e[0;32mPASSED\e[0m\n", __FILE__, __FUNCTION__);
}


void test_layer_dict() {

    /* layer mapping */
    hash_table_t *layers = layer_map(); 

    /* save paths */
    char *linear_path = "../../examples/models/layers/linear"; 
    char *act_path = "../../examples/models/layers/activation";

    /* save linear */    
    layer_t *l1 = linear(2, 3); 
    save_linear(l1, linear_path);

    /* test layer map  */
    layer_t *(*load_layer)(char*) = lookup_table_key(layers, "linear"); 
    layer_t *l3 = load_layer(linear_path);

    assert(l3->layer_type->linear->weights->val->rows == 2); 
    assert(l3->layer_type->linear->weights->val->cols == 3); 
    assert(l3->layer_type->linear->biases->val->rows == 1); 
    assert(l3->layer_type->linear->biases->val->cols == 3);

    // /* test layer map  */
    layer_t *(*load_layer_2)(char*) = lookup_table_key(layers, "loss"); 
    layer_t *l4 = load_layer_2(act_path);

    char cmd[100], cmd2[100];
    sprintf(cmd, "rm -rf %s", act_path);
    int rm_result = system(cmd);
    assert(rm_result == 0);  

    sprintf(cmd2, "rm -rf %s", linear_path);
    rm_result = system(cmd2);
    assert(rm_result == 0);  

    printf("%s::%s... \e[0;32mPASSED\e[0m\n", __FILE__, __FUNCTION__);
}
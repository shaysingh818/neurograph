#include "includes/layer.h"


value_t *linear_forward(computation_graph_t *graph, layer_t *layer, value_t *prev_output){
    linear_t *linear = layer->layer_type->linear; 
    layer->inputs = prev_output; 
    value_t *result =  scale_add_mat( 
        graph, 
        mat_mul(graph, layer->inputs, linear->weights),
        linear->biases
    );
    layer->outputs = result; 
    return result; 
}


value_t *update_linear(computation_graph_t *graph, layer_t *layer, int op_index) {
    linear_t *linear = layer->layer_type->linear;

    /* update weights and biases */
    linear->biases->val = add(
        linear->biases->val,
        scale(layer->outputs->left->upstream_gradient, 0.1)
    );

    linear->weights->val = add(
        linear->weights->val,
        scale(layer->outputs->left->right_grad, 0.1)
    ); 

    return layer->outputs; 
} 

layer_t *linear(int set_input_size, int set_output_size) {

    /* create linear structure */
    linear_t *linear = (linear_t*)malloc(sizeof(linear_t));
    linear->input_size = set_input_size; 
    linear->output_size = set_output_size;
    mat_t *weights = init_matrix(set_input_size, set_output_size); 
    mat_t *biases = init_matrix(1, set_output_size); 
    randomize(weights, weights->rows); 
    randomize(biases, biases->rows); 
    linear->weights = value(weights); 
    linear->biases = value(biases);

    /* create base layer type for activation */
    layer_t *layer = (layer_t*)malloc(sizeof(layer_t));
    layer->layer_type = (layer_obj_t*)malloc(sizeof(layer_obj_t));
    layer->input_size = set_input_size; 
    layer->output_size = set_output_size;
    layer->layer_type->linear = linear;
    layer->forward = linear_forward; 
    layer->save = save_linear;
    layer->load = load_linear; 
    layer->save_layer_architecture = save_linear_architecture;  
    layer->update_params = update_linear; 
    layer->op_count = 2;

    /* set layer name  */
    size_t alias_size = strlen("linear")+1;
    layer->layer_name = malloc(alias_size * sizeof(char)); 
    strcpy(layer->layer_name, "linear");

    return layer;  
}


void save_linear(layer_t *linear, char *filepath) {

    /* create filepath */
    if(access(filepath, F_OK) == -1){
        int result = mkdir(filepath, 0777);  
        if(result){
            printf("Unable to create and save model to %s\n", filepath);
            exit(0);  
        }
    }

    mat_t *weights = linear->layer_type->linear->weights->val; 
    mat_t *biases = linear->layer_type->linear->biases->val;

    char *weight_path, *biase_path;
    size_t weight_path_size = strlen(filepath) + strlen("weights") + 1;
    size_t biase_path_size = strlen(filepath) + strlen("biases") + 1; 
    weight_path = malloc(weight_path_size * sizeof(char)); 
    biase_path = malloc(weight_path_size * sizeof(char)); 

    sprintf(weight_path, "%s/%s", filepath, "weights");
    save_matrix(weights, weight_path); 

    sprintf(biase_path, "%s/%s", filepath, "biases"); 
    save_matrix(biases, biase_path); 

}


void load_linear(layer_t *linear, char *filepath) {

    /* create filepath */
    if(access(filepath, F_OK) == -1){
        printf("Path does not exist for %s\n", filepath);
        exit(0);  
    }

    /* allocate size for each path */
    char *weight_path, *biase_path;
    size_t weight_path_size = strlen(filepath) + strlen("weights") + 1;
    size_t biase_path_size = strlen(filepath) + strlen("biases") + 1; 
    weight_path = malloc(weight_path_size * sizeof(char)); 
    biase_path = malloc(weight_path_size * sizeof(char));

    /* format paths */
    sprintf(weight_path, "%s/%s", filepath, "weights");
    sprintf(biase_path, "%s/%s", filepath, "biases"); 

    linear->layer_type->linear->weights->val = load_matrix(weight_path); 
    linear->layer_type->linear->biases->val = load_matrix(biase_path); 
}


void save_linear_architecture(layer_t *linear, FILE *fp) {
    fprintf(
        fp, "[%s](%d, %d)\n", 
        linear->layer_name,
        linear->input_size,
        linear->output_size
    );
} 


void set_linear_inputs(layer_t *linear, mat_t *input){
    linear->outputs->left->left->val = input; 
}
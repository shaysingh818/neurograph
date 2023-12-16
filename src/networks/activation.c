#include "includes/layer.h"


value_t *activation_forward(computation_graph_t *graph, layer_t *layer, value_t *prev_output) {  
    layer->inputs = prev_output; 
    activation_t *activation = layer->layer_type->activation; 
    value_t *result = apply_loss(
        graph,
        layer->inputs,
        activation->loss,
        activation->loss_prime
    );
    layer->outputs = result;
    return result; 
} 


value_t *update_activation(computation_graph_t *graph, layer_t *layer, int op_index) {
    activation_t *activation = layer->layer_type->activation;
    return layer->outputs;  
} 

layer_t *activation(int set_input_size, int set_output_size, char *loss_function_name) {

    /* map key to loss function */
    hash_table_t *loss_val = loss_map();  
    loss_value_t *loss_functions = lookup_table_key(loss_val, str(loss_function_name)); 

    /* create activation structure */
    activation_t *activation = (activation_t*)malloc(sizeof(activation_t));
    activation->input_size = set_input_size;
    activation->output_size = set_output_size; 
    activation->loss = loss_functions->loss; 
    activation->loss_prime = loss_functions->loss_prime;

    /* set loss function name */
    size_t loss_function_name_size = strlen(loss_function_name)+1;
    activation->loss_function_name = malloc(loss_function_name_size * sizeof(char));
    strcpy(activation->loss_function_name, loss_function_name);

    /* create base layer type for activation */
    layer_t *layer = (layer_t*)malloc(sizeof(layer_t));
    layer->layer_type = (layer_obj_t*)malloc(sizeof(layer_obj_t)); 
    layer->layer_type->activation = activation;
    layer->forward = activation_forward;
    layer->update_params = update_activation;  
    layer->save = save_activation;
    layer->load = load_activation; 
    layer->input_size = set_input_size;
    layer->output_size = set_output_size; 
    layer->op_count = 1;

    /* set layer type name */
    char *type = "loss"; 
    size_t alias_size = strlen(type)+1;
    layer->layer_name = malloc(alias_size * sizeof(char)); 
    strcpy(layer->layer_name, type);

    return layer;  
}

void save_activation(layer_t *activation, char *filepath) {

    /* create filepath */
    if(access(filepath, F_OK) == -1){
        int result = mkdir(filepath, 0777);  
        if(result){
            printf("Unable to create and save model to %s\n", filepath);
            exit(0);  
        }
    }

    /* save matrice outputs */
    char *outputs_path;
    mat_t *outputs = activation->outputs->val; 
    size_t output_path_size = strlen(filepath) + strlen("outputs") + 1;
    outputs_path = malloc(output_path_size * sizeof(char));
    sprintf(outputs_path, "%s/%s", filepath, "outputs");
    save_matrix(outputs, outputs_path); 

    /* save activation function configs */
    char *activations_path;
    size_t activation_path_size = strlen(filepath) + strlen("activations") + 1;
    activations_path = malloc(activation_path_size * sizeof(char)); 
    sprintf(activations_path, "%s/%s", filepath, "activations");

	FILE* file = fopen(activations_path, "w");
	fprintf(file, "function_name: %s\n", activation->layer_type->activation->loss_function_name);
	fclose(file);

}


layer_t *load_activation(char *filepath) {

    /* create filepath */
    if(access(filepath, F_OK) == -1){
        printf("Path does not exist for %s\n", filepath);
        exit(0);  
    }

    /* grab outputs  */
    char *output_path; 
    size_t output_path_size = strlen(filepath) + strlen("outputs") + 1;
    output_path = malloc(output_path_size * sizeof(char)); 
    sprintf(output_path, "%s/%s", filepath, "outputs");
    mat_t *outputs = load_matrix(output_path); 


    /* grab activation function config */
    char *activation_path; 
    size_t activation_path_size = strlen(filepath) + strlen("activations") + 1;
    activation_path = malloc(activation_path_size * sizeof(char)); 
    sprintf(activation_path, "%s/%s", filepath, "activations");

    if(access(activation_path, F_OK) == -1){
        printf("Path does not exist for %s\n", activation_path);
        exit(0);  
    }


    FILE *file = fopen(activation_path, "r");
    if(file == NULL){
        printf("Opening file: %s\n", activation_path);
        exit(0);  
    }


    /* read activation config */
    char *loss_name; 
    fscanf(file, "function_name: %ms\n", &loss_name);

    layer_t *l1 = activation(
        outputs->rows, 
        outputs->cols,
        loss_name
    ); 
    return l1; 

}
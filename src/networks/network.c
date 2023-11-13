#include "includes/network.h"


net_t *init_network(double learning_rate, value_t *input, int batch_size) {
    net_t *nn = (net_t*)malloc(sizeof(net_t));
    nn->graph = create_graph(1.00); 
    nn->learning_rate = learning_rate;
    nn->num_layers = 2; 
    nn->layer_count = 0; 
    nn->front_index = nn->layer_count = 0; 
    nn->rear_index = nn->num_layers - 1; 
    nn->input = input;
    nn->batched = false; 

    /* check if we're batching the inputs */
    if(batch_size > 0){
        nn->batch_size = batch_size; 
        nn->batched = true; 
        nn->input_batches = batch_matrix(nn->input->val, nn->batch_size); 
    }

    /* allocate layers of the network */
    nn->layers = malloc(nn->num_layers * sizeof(layer_t*)); 
    for(int i = 0; i < nn->num_layers; i++){
        nn->layers[i] = malloc(sizeof(layer_t)); 
    }

    return nn; 
}




void layer(net_t *nn, layer_t *layer){

    /* queue insert method */
    if(nn->layer_count == nn->num_layers) {
        int new_size = nn->num_layers + nn->num_layers;
        nn->layers = realloc(nn->layers, new_size * sizeof(layer_t*)); 
        for(int i = nn->num_layers; i < new_size; i++){
            nn->layers[i] = malloc(sizeof(layer_t)); 
        }
        nn->num_layers = new_size; 
    }

    value_t *temp_inputs;
    if(nn->layer_count == 0){
        if(nn->batched){
            value_t *batch_value = value(nn->input_batches[0]); 
            temp_inputs = batch_value; 
        } else {
            temp_inputs = nn->input; 
        }
    } else {
        temp_inputs = nn->layers[nn->layer_count-1]->outputs;
    }

    nn->layers[nn->layer_count] = layer;
    nn->layers[nn->layer_count]->forward(
        nn->graph, 
        nn->layers[nn->layer_count], 
        temp_inputs
    );
    nn->layer_count  += 1;
}



void train(net_t *nn, int epochs, mat_t *y) {

    for(int i = 0; i < epochs; i++){

        forward_nodes(nn->graph);

        /* get output */
        int output_index = nn->graph->curr_index - 1;
        mat_t *output = nn->graph->nodes[output_index]->val; 
        double loss = mse(y, output);  
        mat_t *output_error = difference(y, output);
        if(NETWORK_DEBUG) {
            printf("Loss: %.2f\n", loss);
        }
        backward_nodes(nn->graph, output_error);
        update_network_params(nn);
        
    }

} 

void batch_train(net_t *nn, int epochs, mat_t *y) {

    if(nn->batched == true){

        /* batch outputs */
        int samples = y->rows - nn->batch_size; 
        mat_t **outputs = batch_matrix(y, nn->batch_size);

        for(int j = 0; j < epochs; j++){


            double err = 0.00; 
            for(int i = 0; i < samples; i++){

                /* set inputs for epoch set */
                mat_t *x = nn->input_batches[i]; 
                mat_t *y = outputs[i];
                nn->layers[0]->outputs->left->left->val = x; 


                forward_nodes(nn->graph);

                /* get output */
                int output_index = nn->graph->curr_index - 1;
                mat_t *output = nn->graph->nodes[output_index]->val; 
                double loss = mse(y, output);  
                err += loss; 
                mat_t *output_error = difference(y, output);
                backward_nodes(nn->graph, output_error);
                update_network_params(nn);
            }

            err /= samples; 
            if(j % 1000 == 0){
                if(NETWORK_DEBUG) {
                    printf("Loss: %.2f\n", err); 
                }
            }

        }

    } else {
        printf("network is not configured to use batching\n");
    }

}

void update_network_params(net_t *nn) {
    int pass_index = nn->graph->curr_index-1;  
    for(int i = nn->layer_count-1; i >= 0; i--){
        nn->layers[i]->update_params(nn->graph, nn->layers[i], pass_index);  
        pass_index -= nn->layers[i]->op_count; 
    }
}


void save_model_params(net_t *nn, char *filepath){

    if(access(filepath, F_OK) == -1){
        int result = mkdir(filepath, 0777);  
        if(result){
            printf("Unable to create and save model to %s\n", filepath);
            exit(0);  
        }
    }

    /* save model architecture */
    size_t architecture_path_size = strlen(filepath) + strlen("architecture") + 1;
    char *model_architecture_path = malloc(architecture_path_size * sizeof(char));   
    sprintf(model_architecture_path, "%s/%s", filepath, "architecture");
    FILE *fp = fopen(model_architecture_path, "w"); 

    /* create layers within base directory */
    for(int i = 0; i < nn->layer_count; i++){
        size_t layer_path_size = strlen(filepath) + strlen("layer") + 1;
        char *layer_path = malloc(layer_path_size * sizeof(char));  
        sprintf(layer_path, "%s/%d_%s", filepath, i, nn->layers[i]->layer_name);

        /* create layer path */
        if(access(layer_path, F_OK) == -1){
            int result = mkdir(layer_path, 0777);  
            if(result){
                printf("Unable to create and save model to %s\n", layer_path);
                exit(0);  
            }
        }

        /* save to layer path */
        nn->layers[i]->save(nn->layers[i], layer_path); 
        fprintf(fp, "%s:%s\n", nn->layers[i]->layer_name, layer_path);  
    }

    fclose(fp); 

}


void load_model_params(net_t *nn, char *filepath) {

    if(access(filepath, F_OK) == -1){
        printf("No saved model exists in %s\n", filepath);
        exit(0);  
    }

    /* create layers from architecture file */
    char buffer[1000]; 
    hash_table_t *layers = layer_map(); 
    FILE *fp = fopen(filepath, "r"); 
    int counter = 0, count; 
    while(fgets(buffer, 1000, fp)) {

        end_line_terminate(buffer); 
        array_t *vals = match_delimeter_file(buffer, ":"); 

        char *layer_type = vals->items[0]->label; 
        char *path = vals->items[1]->label; 

        layer_t *(*load_layer)(char*) = lookup_table_key(layers, layer_type); 
        layer_t *layer_instance = load_layer(path);        
        layer(nn, layer_instance); 

        counter += 1; 
    }


} 


void predict(net_t *nn, mat_t *input, mat_t *expected_output) {

    /* forward inputs */
    set_linear_inputs(nn->layers[0], input); 
    forward_nodes(nn->graph);

    /* print output */
    int output_index = nn->graph->curr_index - 1;
    mat_t *output = nn->graph->nodes[output_index]->val;

    if(NETWORK_DEBUG == true) {

        printf("Expected output\n"); 
        print_vec(expected_output); 

        printf("Output\n"); 
        print_vec(output); 

    }
} 



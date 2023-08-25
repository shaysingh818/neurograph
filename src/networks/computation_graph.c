#include "includes/computation_graph.h"


node_type_t *init_node_type(layer_type_t layer_type, void *node) {
    node_type_t *node_type = malloc(sizeof(node_type_t)); 
    node_type->layer_type = layer_type; 
    node_type->node_structure = node; 
    return node_type; 
}


node_type_t **init_nodes(int length){
    node_type_t **nodes = malloc(length * sizeof(node_type_t*)); 
    for(int i = 0; i < length; i++){
        nodes[i] = malloc(sizeof(node_type_t)); 
    }
    return nodes; 
}


void add_c_node(node_type_t **nodes, node_type_t *node, int index) {
    nodes[index] = node; 
}


void forward_all(node_type_t **nodes, int length, mat_t *inputs) {

    mat_t *prev_outputs; 

    for(int i = 0; i < length; i++){

        node_type_t *value = nodes[i]; 
        switch(value->layer_type){

            case LINEAR: ;  

                linear_t *linear = (linear_t*)value->node_structure;
                if(i == 0){
                    linear->node->forward(linear, inputs); 
                    prev_outputs = linear->node->outputs;
                } else {
                    linear->node->forward(linear, prev_outputs);
                    prev_outputs = linear->node->outputs; 
                }
                break;  

            case LOSS: ; 
                loss_t *loss = (loss_t*)value->node_structure;
                loss->node->forward(loss, prev_outputs);
                prev_outputs = loss->node->outputs;  
                break; 
        }
    }
}


void backward_all(node_type_t **nodes, int length, mat_t *output_error) {

    mat_t *curr_output_err = output_error;  

    for(int i = length-1; i >= 0; i--){

        node_type_t *value = nodes[i]; 

        switch(value->layer_type){

            case LINEAR: ;  
                linear_t *linear = (linear_t*)value->node_structure;
                linear->node->backward(linear, curr_output_err); 
                curr_output_err = linear->node->gradients; 
                break;  

            case LOSS: ; 
                loss_t *loss = (loss_t*)value->node_structure;
                loss->node->backward(loss, curr_output_err); 
                curr_output_err = loss->node->gradients;
                break; 
        }
    }
}


void linear_forward(void *linear_ptr, mat_t *set_inputs) {
    linear_t *linear = (linear_t*)linear_ptr; 
    linear->node->inputs = set_inputs; 
    mat_t *mult = dot(linear->node->inputs, linear->weights);
    mat_t *scaled = scale_add(mult, linear->biases); 
    linear->node->outputs = scaled;
}


void linear_backward(void *linear_ptr, mat_t *delta_error) {

    /* dereference inputs */
    linear_t *linear = (linear_t*)linear_ptr; 

    /* update weights and biases */
    mat_t *input_error = dot(delta_error, transpose(linear->weights));
    mat_t *db = scale(delta_error, linear->learning_rate); 
    mat_t *dw = scale(
        dot(transpose(linear->node->inputs), delta_error), 
        linear->learning_rate
    );

    linear->weights = add(linear->weights, dw); 
    linear->biases = add(linear->biases, db); 
    linear->node->gradients = input_error;
}


linear_t *linear(int input_size, int output_size, double learning_rate) {

    linear_t *linear = malloc(sizeof(linear_t)); 
    linear->node = malloc(sizeof(c_node_t)); 
    linear->node->input_size = input_size; 
    linear->node->output_size = output_size;
    linear->node->forward = linear_forward;
    linear->node->backward = linear_backward;
    linear->node->outputs = NULL; 
    linear->node->inputs = NULL; 
    linear->weights = init_matrix(input_size, output_size); 
    linear->biases = init_matrix(1, output_size);
    linear->learning_rate = learning_rate;
    randomize(linear->weights, linear->weights->rows); 
    randomize(linear->biases, linear->biases->rows); 
    return linear; 
} 


void debug_linear(linear_t *linear) {

    printf(
        "Weights: (%d X %d)\n", 
        linear->weights->rows, linear->weights->cols
    );
    print_vec(linear->weights);
    printf("\n");  

    printf(
        "Biases: (%d X %d)\n", 
        linear->biases->rows, linear->biases->cols
    );
    print_vec(linear->biases); 
    printf("\n"); 

}


void loss_forward(void *loss_ptr, mat_t *set_inputs) {
    loss_t *loss_layer = (loss_t*)loss_ptr;
    loss_layer->node->inputs = set_inputs; 
    mat_t *result = apply(
        loss_layer->loss,
        loss_layer->node->inputs
    );    
    loss_layer->node->outputs = result; 
}


void loss_backward(void *loss_ptr, mat_t *output_error) {

    /* Dereference structures */
    loss_t *loss_layer = (loss_t*)loss_ptr;

    /* get input error */
    mat_t *result = elementwise_multiply(
        output_error, 
        loss_layer->loss_prime(loss_layer->node->inputs)
    );
    loss_layer->node->gradients = result; 
}


loss_t *loss(
    int input_size, int output_size,
    double(*loss)(double value),
    mat_t*(*loss_prime)(mat_t *inputs)) {

    loss_t *loss_layer = malloc(sizeof(loss_t));
    loss_layer->node = malloc(sizeof(c_node_t));
    loss_layer->node->input_size = input_size; 
    loss_layer->node->output_size = output_size;
    loss_layer->node->forward = loss_forward;
    loss_layer->node->backward = loss_backward;
    loss_layer->node->outputs = NULL; 
    loss_layer->node->inputs = NULL; 
    loss_layer->loss = loss; 
    loss_layer->loss_prime = loss_prime; 
    return loss_layer; 
} 


void debug_loss(loss_t *loss) {

    printf("Before Activation\n");
    print_vec(loss->node->inputs);
    printf("\n");  

    printf("After Activation\n");
    print_vec(loss->node->outputs); 
    printf("\n"); 
    
}
#include "includes/computation_graph.h"


linear_t *linear(mat_t *inputs, int input_size, int output_size) {
    linear_t *linear = malloc(sizeof(linear_t)); 
    linear->node = malloc(sizeof(c_node_t)); 
    linear->node->inputs = inputs;
    linear->node->input_size = input_size; 
    linear->node->output_size = output_size;
    linear->weights = init_matrix(input_size, output_size); 
    linear->biases = init_matrix(output_size, 1);
    linear->node->forward = feedforward;
    randomize(linear->weights, linear->weights->rows); 
    randomize(linear->biases, linear->biases->rows); 
    return linear; 
} 


void feedforward(void *linear_ptr) {
    linear_t *linear = (linear_t*)linear_ptr; 
    mat_t *mult = dot(linear->node->inputs, linear->weights);
    mat_t *scaled = scale_add(mult, linear->biases); 
    linear->node->outputs = scaled; 
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

loss_t *loss(
    mat_t *inputs, int input_size, int output_size,
    double(*loss)(double value),
    mat_t*(*loss_prime)(mat_t *inputs)) {

    loss_t *loss_layer = malloc(sizeof(loss_t));
    loss_layer->node = malloc(sizeof(c_node_t));
    loss_layer->node->input_size = input_size; 
    loss_layer->node->output_size = output_size;
    loss_layer->node->inputs = inputs;
    loss_layer->node->forward = feedforward_activation;
    loss_layer->loss = loss; 
    loss_layer->loss_prime = loss_prime; 
    return loss_layer; 
} 


void feedforward_activation(void *loss_ptr) {
    loss_t *loss_layer = (loss_t*)loss_ptr;
    mat_t *result = apply(
        loss_layer->loss,
        loss_layer->node->inputs
    );    
    loss_layer->node->outputs = result; 
}


void debug_loss(loss_t *loss) {

    printf("Before Activation\n");
    print_vec(loss->node->inputs);
    printf("\n");  

    printf("After Activation\n");
    print_vec(loss->node->outputs); 
    printf("\n"); 
    
}
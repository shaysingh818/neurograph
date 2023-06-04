#include "includes/computation_graph.h"


linear_t *linear(int input_size, int output_size, double learning_rate) {

    linear_t *linear = malloc(sizeof(linear_t)); 
    linear->node = malloc(sizeof(c_node_t)); 
    linear->node->input_size = input_size; 
    linear->node->output_size = output_size;
    linear->node->forward = feedforward;
    linear->node->backward = backprop;
    linear->weights = init_matrix(input_size, output_size); 
    linear->biases = init_matrix(1, output_size);
    linear->learning_rate = learning_rate;
    randomize(linear->weights, linear->weights->rows); 
    randomize(linear->biases, linear->biases->rows); 
    return linear; 
} 


void feedforward(void *linear_ptr, mat_t *set_inputs) {
    linear_t *linear = (linear_t*)linear_ptr; 
    linear->node->inputs = set_inputs; 
    mat_t *mult = dot(linear->node->inputs, linear->weights);
    mat_t *scaled = scale_add(mult, linear->biases); 
    linear->node->outputs = scaled;
}


void backprop(void *linear_ptr, mat_t *delta_error) {

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


void debug_linear(linear_t *linear) {

    printf(
        "Weights: (%d X %d)\n", 
        linear->weights->rows, linear->weights->cols
    );
    print_vec(linear->weights);
    printf("\n");  

    // printf(
    //     "Biases: (%d X %d)\n", 
    //     linear->biases->rows, linear->biases->cols
    // );
    // print_vec(linear->biases); 
    //printf("\n"); 

}

loss_t *loss(
    int input_size, int output_size,
    double(*loss)(double value),
    mat_t*(*loss_prime)(mat_t *inputs)) {

    loss_t *loss_layer = malloc(sizeof(loss_t));
    loss_layer->node = malloc(sizeof(c_node_t));
    loss_layer->node->input_size = input_size; 
    loss_layer->node->output_size = output_size;
    loss_layer->node->forward = feedforward_activation;
    loss_layer->node->backward = backward_activation;
    loss_layer->loss = loss; 
    loss_layer->loss_prime = loss_prime; 
    return loss_layer; 
} 


void feedforward_activation(void *loss_ptr, mat_t *set_inputs) {
    loss_t *loss_layer = (loss_t*)loss_ptr;
    loss_layer->node->inputs = set_inputs; 
    mat_t *result = apply(
        loss_layer->loss,
        loss_layer->node->inputs
    );    
    loss_layer->node->outputs = result; 
}


void backward_activation(void *loss_ptr, mat_t *output_error) {

    /* Dereference structures */
    loss_t *loss_layer = (loss_t*)loss_ptr;

    /* get input error */
    mat_t *result = elementwise_multiply(
        output_error, 
        loss_layer->loss_prime(loss_layer->node->inputs)
    );
    loss_layer->node->gradients = result; 
}


void debug_loss(loss_t *loss) {

    printf("Before Activation\n");
    print_vec(loss->node->inputs);
    printf("\n");  

    printf("After Activation\n");
    print_vec(loss->node->outputs); 
    printf("\n"); 
    
}


void forward_all(void *nodes[], int length) {
    for(int i = 0; i < length; i++){
        printf("Node: %d\n", i);  
        c_node_t *value = (c_node_t*)nodes[i]; 
        //value->forward(value);       
    }
}
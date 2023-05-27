#include "includes/test_layer.h"


void test_create_layer() {

    bool equality_status = false; 

	int inputs[4][2] = {
        {0,1},
        {1,0},
        {1,1},
        {0,0}
    };

    int outputs[4][1] = {
        {1},
        {1},
        {0},
        {0}
    };

	/* copy inputs to mat structure */
    mat_t *input = init_vec(1, 2, false);
    for(int i = 0; i < input->rows; i++){
        for(int j = 0; j < input->cols; j++){
            input->arr[i][j] = inputs[0][j];
        }
    }


    /* copy outputs to mat structure */
    mat_t *output = init_vec(4, 1, false);
    for(int i = 0; i < output->rows; i++){
        for(int j = 0; j < output->cols; j++){
            output->arr[i][j] = outputs[i][j];
        }
    }


	/* first layer */ 
	layer_t **layers = malloc(2 * sizeof(layer_t*)); 
	layer_t *input_layer = nn_layer(2, 3, false); 
   	layer_t *hidden = nn_layer(3, 1, false); 

	/* add layers to networks */ 
	layers[0] = input_layer; 
	layers[1] = hidden;

    int x1 = input_layer->weights->rows == 2 && input_layer->weights->cols == 3; 
    int x2 = hidden->weights->rows == 3 && hidden->weights->cols == 1; 
    if(x1 && x2){
        equality_status = true;         
    } 

    if(!equality_status) {
        printf("%s::%s... FAILED\n", __FILE__, __FUNCTION__);
    } else {
        printf("%s::%s... \e[0;32mPASSED\e[0m\n", __FILE__, __FUNCTION__);
    }

}


void test_forward() {

    bool equality_status = true; 

	int inputs[4][2] = {
        {0,1},
        {1,0},
        {1,1},
        {0,0}
    };

    int outputs[4][1] = {
        {1},
        {1},
        {0},
        {0}
    };

	    /* copy inputs to mat structure */
    mat_t *input = init_vec(1, 2, false);
    for(int i = 0; i < input->rows; i++){
        for(int j = 0; j < input->cols; j++){
            input->arr[i][j] = inputs[0][j];
        }
    }


    /* copy outputs to mat structure */
    mat_t *output = init_vec(1, 1, false);
    for(int i = 0; i < output->rows; i++){
        for(int j = 0; j < output->cols; j++){
            output->arr[i][j] = outputs[0][j];
        }
    }

    int expected_dims[4] = {3, 3, 1, 1}; 

    /* create layers for network */
    layer_t **layers = malloc(4  * sizeof(layer_t*)); 
    layer_t *l1 = nn_layer(2, 3, false); 
    layer_t *a1 = nn_layer(0, 0, true);

    layer_t *l2 = nn_layer(3, 1, false); 
    layer_t *a2 = nn_layer(0, 0, true); 

    layers[0] = l1; 
    layers[1] = a1; 
    layers[2] = l2; 
    layers[3] = a2;

    mat_t *temp_output = input; 
    for(int i = 0; i < 4; i++){
        temp_output = forward(layers[i], temp_output); 
        if(temp_output->cols != expected_dims[i]){
            equality_status = false; 
        }
    }

    if(!equality_status) {
        printf("%s::%s... FAILED\n", __FILE__, __FUNCTION__);
    } else {
        printf("%s::%s... \e[0;32mPASSED\e[0m\n", __FILE__, __FUNCTION__);
    }

}



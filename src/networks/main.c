#include "tests/includes/test_network.h"
#include "tests/includes/test_layer.h"

int main(int argc, char **argv) {

    /* loss map test */
    test_loss_dict(); 

    /* layer tests */
    test_linear_layer();
    test_save_linear_layer();
    test_load_linear_layer();
    test_activation_layer();
    test_save_activation_layer(); 
    test_load_activation_layer(); 
    test_layer_dict();  
	
	/* network tests */
	test_init_network();
    test_add_layer(); 
    test_train();
    test_batch_train(); 
    test_save_model_params();
    test_load_model_params();  
}

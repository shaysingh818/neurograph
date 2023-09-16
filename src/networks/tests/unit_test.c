#include "includes/test_network.h"
#include "includes/test_layer.h"

int main(int argc, char **argv) {

    /* layer tests */
    test_linear_layer();
    test_activation_layer();
	
	/* network tests */
	test_init_network();
    test_add_layer(); 
    test_train();
    test_save_model_params(); 
}

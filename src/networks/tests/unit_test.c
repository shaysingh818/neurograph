#include "includes/test_layer.h" 
#include "includes/test_network.h"
#include "includes/test_computation_graph.h"

int main(int argc, char **argv) {
	
	/* conversion methods */ 
   	test_create_layer();
	test_forward();

	/* network tests */
	test_init_network();
    test_create_layer(); 
    test_train();
    test_loss(); 
    test_network_train();
	test_base_concept(); 

	/* computation graph tests */
	test_linear();  

}

#include "includes/test_network.h"
#include "includes/test_computation_graph.h"

int main(int argc, char **argv) {

	/* computation graph tests */
	test_init_node_type();
	test_init_nodes();
	test_append_c_node();
	test_forward_all(); 
	test_backward_all();  	
	test_mlp();
	test_dense();  
	
	/* network tests */
	test_init_network();
    test_add_layer(); 
    test_train();
}

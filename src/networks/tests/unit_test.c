#include "includes/test_network.h"
#include "includes/test_computation_graph.h"
#include "includes/test_value.h"
#include "includes/test_ops.h"

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

	/* refactored comp graph */
	// test_value_init();
	// test_create_graph();
	// test_append_operation(); 
	// test_forward_nodes();
	test_backward_nodes();  

	/* ops */
	test_add_operation();
	test_multiply_operation();  
	test_expression();

 


}

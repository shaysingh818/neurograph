#include "tests/includes/test_graph.h"
#include "tests/includes/test_ops.h"
#include "tests/includes/test_mlp.h"

int main(int argc, char **argv) {

	/* computation graph tests */	
	test_create_graph();
	test_append_operation();
	test_forward_nodes(); 
	test_backward_nodes(); 

	/* test ops */
	test_mat_mult();

	/* test training */
	test_xor();  

}

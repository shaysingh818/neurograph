#include "includes/test_computation_graph.h"
#include "includes/test_value.h"
#include "includes/test_ops.h"
#include "includes/test_mat_ops.h"


int main(int argc, char **argv) {

	/* value creation */
	test_value_init();

	/* computation graph tests */	
	test_create_graph();
	test_append_operation(); 
	test_forward_nodes();
	test_backward_nodes();  

	/* ops */
	test_add_operation();
	test_multiply_operation();  
	test_expression();

	/* matrice operations */
	test_mat_multiply(); 

}
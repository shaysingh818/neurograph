#include "includes/test_matrix.h"


int main(int argc, char **argv) {

	/* matrix utility methods */
	test_init_matrix();
	test_directed_matrix();

	/* test vector methods */ 
	test_init_vec();
	test_scalar_multiply(); 
	test_vector_multiplication(); 
	test_matrix_power();  

}

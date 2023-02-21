#include "includes/matrix.h"


int main(int argc, char **argv) {

	/* create adjacency matrix graph with size 5 */ 
	mat_t *m = init_mat(5, 5); 
	entry(m, 0, 1); 
	entry(m, 0, 2); 
	entry(m, 1, 2); 
	entry(m, 2, 0); 
	entry(m, 2, 3);

}

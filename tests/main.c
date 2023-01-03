#include "includes/graph_test.h" 
#include "includes/matrix_test.h"
#include "includes/queue_test.h"

int main(int argc, char **argv) {

	/* run all tests here */ 
	printf("\n");

	/* queue methods */ 
	test_init_queue();
   	test_pop_queue(); 	

	/* graph utility methods */ 
	test_adjacency_list();
   	test_weighted_adjacency_list(); 	
	test_bfs_one();
	test_bfs_two();
	test_dfs_one();
	test_bellman_ford();
   	test_random_walk();
	test_weighted_random_walk(); 	

	/* matrix utility methods */ 
	test_init_matrix(); 


	printf("\n"); 
	
}

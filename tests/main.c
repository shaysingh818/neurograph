
/* main headers */ 
#include "includes/graph_test.h" 
#include "includes/matrix_test.h"
#include "includes/queue_test.h"

/* extension headers */ 
#include "includes/path_test.h" 
#include "includes/search_test.h" 
#include "includes/community_test.h" 

int main(int argc, char **argv) {

	/* run all tests here */ 
	printf("\n");

	/* queue methods */ 
	test_init_queue();
   	test_pop_queue();

	/* matrix utility methods */ 
	test_init_matrix(); 

	/* graph utility methods */ 
	test_adjacency_list();
	test_transpose_adj_list(); 
   	test_weighted_adjacency_list();

	/* searching methods */ 	
	test_bfs_one();
	test_bfs_two();
	test_dfs_one();

	/* pathfinding tests */ 
	test_bellman_ford();
   	test_random_walk();
	test_weighted_random_walk();

	/* centrality tests */ 
	test_degree_centrality(); 
	test_weighted_degree_centrality();	

	/* community detection tests */ 
	test_kosaraju(); 

	printf("\n"); 
	
}

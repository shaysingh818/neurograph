#include "includes/test_graph.h" 
#include "includes/test_path.h" 
#include "includes/test_search.h" 
#include "includes/test_community.h" 

int main(int argc, char **argv) {
	
	/* graph utility methods */ 
	test_graph();
   	test_weighted_graph();
	test_transpose_graph(); 

	/* conversion methods */ 
	test_to_matrix();
	test_to_directed_matrix();	
	test_to_weighted_matrix(); 
	test_to_directed_weighted_matrix();
   	test_to_list();
	test_to_weighted_list();
   	test_to_directed_list(); 	
	test_to_directed_weighted_list(); 

	/* searching */
	test_bfs_one();
	test_bfs_two();
	test_dfs_one();

	/* path finding */
	test_bellman_ford();
   	test_random_walk();
	test_weighted_random_walk();

	/* community detection */
	test_degree_centrality();
	test_weighted_degree_centrality();
	test_kosaraju();


}

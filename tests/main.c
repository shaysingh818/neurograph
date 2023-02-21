
/* main headers */ 
#include "includes/graph_test.h" 
#include "includes/matrix_test.h"
#include "includes/queue_test.h"
#include "includes/map_test.h"

/* extension headers */
#include "includes/csv_test.h" 
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

	/* test csv data extraction */
   	test_populate_headers(); 
	test_populate_headers_two(); 
	test_populate_headers_three(); 
	test_populate_headers_four(); 
   	test_populate_rows(); 
	
	/* test csv structure */ 
	test_invalid_file(); 	
	test_csv_structure();

	/* test hash map */ 
	test_ull(); 

	/* test graph conversion from csv */ 
	test_csv_to_graph(); 	
	test_csv_to_graph_two(); 
	test_csv_to_graph_three();

	/* test multi feature select */ 
	test_even_pair_feature_pass(); 
	test_even_pair_feature_fail(); 
	test_odd_pair_feature_pass(); 
	test_odd_pair_feature_fail(); 


	printf("\n"); 
	
}

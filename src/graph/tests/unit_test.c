#include "includes/test_graph.h" 
#include "includes/test_path.h" 
#include "includes/test_search.h" 
#include "includes/test_community.h" 

int main(int argc, char **argv) {
	
	/* conversion methods */ 
   	test_to_list();
	test_to_weighted_list();
   	test_to_directed_list(); 	
	test_to_directed_weighted_list(); 

	/* searching */
	test_bfs_one();
	test_bfs_two();
	test_dfs_one();

	/* shortest path */
	test_bellman_ford();
	test_dijkstra();
	test_dijkstra_two();
	test_dijkstra_vertice();  
	test_dijkstra_vertice_two();  
	test_shortest_path();

	/* random walk */
   	test_random_walk();
	test_weighted_random_walk();

	/* community detection */
	test_degree_centrality();
	test_weighted_degree_centrality();
	test_kosaraju();

	/* centrality */
	test_closeness_centrality();
	test_normalized_closeness_centrality();

}

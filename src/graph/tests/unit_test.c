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

	/* frame to graph methods */
	test_frame_to_unweighted_graph(); 
	test_frame_to_weighted_graph(); 
	test_unused_slots();

	/* graph markup language methods */
	test_get_max_vertex_count(); 
	test_get_nodes(); 
	test_get_nodes_from_file(); 
	test_serialize_adj_list_sorted_labels();
	test_serialize_adj_list(); 
	test_deserialize_adj_list();  

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
	test_dijkstra_mat();
	test_dijkstra_origin_vertex_mat(); 
	test_shortest_path_mat();

	/* random walk */
   	test_random_walk();
	test_weighted_random_walk();
	test_random_walk_mat(); 

	/* community detection */
	test_degree_centrality();
	test_weighted_degree_centrality();
	test_degree_centrality_mat();
	test_kosaraju();
	test_label_nodes(); 
	test_label_propagation();
	test_iterative_label_propagation(); 
	test_triangle_count();  


}

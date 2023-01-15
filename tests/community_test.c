#include "includes/community_test.h"


void test_degree_centrality() {

  	int vertices = 5; // num of vertices
    int edges = 8; // num of edges
    graph_t *g = init_graph(vertices, edges, false);

    /* create nodes for graph */
    node_t *a = create_node(0, 'A', 0); // create unweighted nodes
    node_t *b = create_node(1, 'B', 0);
    node_t *c = create_node(2, 'C', 0);
    node_t *d = create_node(3, 'D', 0);
    node_t *e = create_node(4, 'E', 0);

    /* add relationships */
    g->edges[0] = create_edge(a, b, -1);
    g->edges[1] = create_edge(a, c, 4);
    g->edges[2] = create_edge(b, c, 3);
    g->edges[3] = create_edge(b, d, 2);
    g->edges[4] = create_edge(b, e, 2);
    g->edges[5] = create_edge(d, b, 5);
    g->edges[6] = create_edge(d, b, 1);
    g->edges[7] = create_edge(e, d, -3);

	int result = degree_centrality(g, a);
	int equality_condition = result == 1;

	if(!equality_condition) {
		printf("%s::%s...  FAILED\n", __FILE__, __FUNCTION__); 
	} else {
		printf("%s::%s...  \e[0;32mPASSED\e[0m\n", __FILE__, __FUNCTION__); 
	}	
}



void test_weighted_degree_centrality() {
	
	/* test random walk */
    int vertices = 5; 

	/* create weighted adjacency list */ 
	graph_t *g = init_graph(vertices, vertices, false);
	add_node(g, 0, 'A', 1, 'B', 2);
	add_node(g, 0, 'A', 2, 'C', 1); 
	add_node(g, 0, 'A', 3, 'D', 1); 
	add_node(g, 1, 'B', 2, 'C', 2);
	add_node(g, 4, 'E', 2, 'C', 1);

	/* test weighted degree centrality */ 
	int result = weighted_degree_centrality(g);
	int equality_condition = result == 0; 
		
	if(!equality_condition) {
		printf("%s::%s...  FAILED\n", __FILE__, __FUNCTION__); 
	} else {
		printf("%s::%s...  \e[0;32mPASSED\e[0m\n", __FILE__, __FUNCTION__); 
	}	

}


void test_kosaraju() {

	/* test tranpose of adjacency list */
    int vertices = 8; 
	int equality_test = TRUE; 

	/* create adjacency list */ 
	graph_t *g = init_graph(vertices, vertices, true);

	/* first community */ 
	add_node(g, 0, 'A', 1, 'B', 0);
	add_node(g, 1, 'B', 2, 'C', 0);
	add_node(g, 2, 'C', 3, 'D', 0);
	add_node(g, 3, 'D', 0, 'A', 0);

	/* bridge */ 
	add_node(g, 2, 'C', 4, 'E', 0);

	/* second community */ 
	add_node(g, 4, 'E', 5, 'F', 0);
	add_node(g, 5, 'F', 6, 'G', 0);
	add_node(g, 6, 'G', 4, 'E', 0);
	add_node(g, 6, 'G', 7, 'H', 0);
	add_end_node(g, 7, 'H', 0);

	char test1[2] = {'A', 'B'}; 
	char test2[3] = {'C', 'D', 'E'}; 	
	char **result = kosaraju(g, 0);
	
	/* expected output from communities */
    char output[8][8] = {
        {'A', 'D', 'C', 'B'},
        {'E', 'G', 'F'},
        {'H'}
    };
	
	/* question: can there be more communities then there are vertices? */
	/* refine this method to have a specific structural return type for communities */ 
	for(int i = 0; i < g->v; i++) {
		for(int j = 0; j < g->v; j++) {
			if(result[i][j] != output[i][j]) {
				equality_test = FALSE; 
			}
		}
	}

	if(!equality_test) {
		printf("%s::%s...  FAILED\n", __FILE__, __FUNCTION__); 
	} else {
		printf("%s::%s...  \e[0;32mPASSED\e[0m\n", __FILE__, __FUNCTION__); 
	}	


}

#include "includes/test_community.h"


void test_degree_centrality() {

  	int vertices = 5; // num of vertices
    int edges = 8; // num of edges
    adj_list_t *g = init_graph(vertices, edges, false);

    /* create nodes for graph */
    node_t *a = create_node(0, "A", 0); // create unweighted nodes
    node_t *b = create_node(1, "B", 0);
    node_t *c = create_node(2, "C", 0);
    node_t *d = create_node(3, "D", 0);
    node_t *e = create_node(4, "E", 0);

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
	adj_list_t *g = init_graph(vertices, vertices, false);
	add_node(g, 0, "A", 1, "B", 2);
	add_node(g, 0, "A", 2, "C", 1); 
	add_node(g, 0, "A", 3, "D", 1); 
	add_node(g, 1, "B", 2, "C", 2);
	add_node(g, 4, "E", 2, "C", 1);

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
	adj_list_t *g = init_graph(vertices, vertices, true);

	/* first community */ 
	add_node(g, 0, "A", 1, "B", 0);
	add_node(g, 1, "B", 2, "C", 0);
	add_node(g, 2, "C", 3, "D", 0);
	add_node(g, 3, "D", 0, "A", 0);

	/* bridge */ 
	add_node(g, 2, "C", 4, "E", 0);

	/* second community */ 
	add_node(g, 4, "E", 5, "F", 0);
	add_node(g, 5, "F", 6, "G", 0);
	add_node(g, 6, "G", 4, "E", 0);
	add_node(g, 6, "G", 7, "H", 0);
	add_end_node(g, 7, "H", 0);

	char test1[2] = {'A', 'B'}; 
	char test2[3] = {'C', 'D', 'E'}; 	
	int **result = kosaraju(g, 0);
	
	/* expected output from communities */
    int output[8][8] = {
        {0, 3, 2, 1},
        {4, 6, 5},
        {7}
    };


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


void test_closeness_centrality() {

	int vertices = 7;
	int vertex = 4; 
	int equality_status = false; 
	float expected_result = 0.014706;  

	adj_list_t *g = init_graph(vertices, vertices, false);
    add_node(g, 0, "A", 1, "B", 2);
    add_node(g, 0, "A", 2, "C", 6);
    add_node(g, 1, "B", 3, "D", 5);
    add_node(g, 2, "C", 3, "D", 8);
    add_node(g, 3, "D", 4, "E", 10);
	add_node(g, 3, "D", 5, "F", 15);
	add_node(g, 4, "E", 5, "F", 6);
	add_node(g, 5, "F", 6, "G", 6);
	add_node(g, 4, "E", 6, "G", 2);

	float result = closeness_centrality(g, vertex); 

	if(fabs(result - expected_result) < 0.0001){
		equality_status = true;  
	}

	if(!equality_status) {
		printf("%s::%s...  FAILED\n", __FILE__, __FUNCTION__); 
	} else {
		printf("%s::%s...  \e[0;32mPASSED\e[0m\n", __FILE__, __FUNCTION__); 
	}	

}

void test_normalized_closeness_centrality() {

	int vertices = 7;
	int vertex = 4; 
	int equality_status = false;
	float expected_result = 0.088235;  

	adj_list_t *g = init_graph(vertices, vertices, false);
    add_node(g, 0, "A", 1, "B", 2);
    add_node(g, 0, "A", 2, "C", 6);
    add_node(g, 1, "B", 3, "D", 5);
    add_node(g, 2, "C", 3, "D", 8);
    add_node(g, 3, "D", 4, "E", 10);
	add_node(g, 3, "D", 5, "F", 15);
	add_node(g, 4, "E", 5, "F", 6);
	add_node(g, 5, "F", 6, "G", 6);
	add_node(g, 4, "E", 6, "G", 2);

	float result = normalized_closeness_centrality(g, vertex);

	if(fabs(result - expected_result) < 0.0001){
		equality_status = true;  
	}

	if(!equality_status) {
		printf("%s::%s...  FAILED\n", __FILE__, __FUNCTION__); 
	} else {
		printf("%s::%s...  \e[0;32mPASSED\e[0m\n", __FILE__, __FUNCTION__); 
	}	

}


void test_degree_centrality_mat() {

	int vertices = 7;
	int vertex = 2;
	int expected_results[7] = {2, 3, 3, 2, 0};  
	bool equality_status = true; 

	/* create adjacency matrix graph with size 5 */ 
	mat_graph_t *m = init_matrice_graph(5); 

    /* create unique nodes */
    entry_t *a = init_entry(0, "A"); 
    entry_t *b = init_entry(1, "B"); 
    entry_t *c = init_entry(2, "C"); 
    entry_t *d = init_entry(3, "D"); 

	/* connect a to everyone */ 
    insert(m, a, b, 0, false); 
    insert(m, a, c, 0, false); 
    insert(m, b, c, 0, false); 
    insert(m, b, d, 0, false); 
    insert(m, c, d, 0, false); 

	int *result = degree_centrality_mat(m);

	for(int i = 0; i < m->vertices; i++){
		if(result[i] != expected_results[i]){
			equality_status = false; 
		} 
	}

	if(!equality_status) {
		printf("%s::%s...  FAILED\n", __FILE__, __FUNCTION__); 
	} else {
		printf("%s::%s...  \e[0;32mPASSED\e[0m\n", __FILE__, __FUNCTION__); 
	}	

}


void test_label_nodes(){

	bool equality_status = true;  
	int vertices = 7; 
	mat_graph_t *m = init_matrice_graph(vertices);

    /* create unique nodes */
    entry_t *a = init_entry(0, "A"); 
    entry_t *b = init_entry(1, "B"); 
    entry_t *c = init_entry(2, "C"); 
    entry_t *d = init_entry(3, "D"); 
    entry_t *e = init_entry(4, "E"); 
    entry_t *f = init_entry(5, "F"); 
    entry_t *g = init_entry(6, "G"); 

	/* connect a to everyone */
    insert(m, a, a, 0, false); 
    insert(m, b, b, 0, false); 
    insert(m, a, d, 0, false); 
    insert(m, d, c, 0, false); 
    insert(m, d, e, 0, false); 
    insert(m, e, f, 0, false); 
    insert(m, f, g, 0, false); 
    insert(m, b, f, 0, false);

	int labels[2] = {0, 1}; // only works with these labels 
	mat_t *result = label_nodes(m, labels);

	/* expected result */
    double expected[7][7] = {
        {1.00, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00},
        {0.00, 1.00, 0.00, 0.00, 0.00, 0.00, 0.00},
        {0.00, 0.00, 0.00, 1.00, 0.00, 0.00, 0.00},
        {1.00, 0.00, 1.00, 0.00, 1.00, 0.00, 0.00},
        {0.00, 0.00, 0.00, 1.00, 0.00, 1.00, 0.00},
        {0.00, 1.00, 0.00, 0.00, 1.00, 0.00, 1.00},
        {0.00, 0.00, 0.00, 0.00, 0.00, 1.00, 0.00}
    };

	for(int i = 0; i < vertices; i++){
		for(int j = 0; j < vertices; j++){
			double rounded_value = round(result->arr[i][j]*100)/100; 
			if(expected[i][j] != rounded_value){
				equality_status = false; 
			}
		}
	}

	if(!equality_status) {
		printf("%s::%s...  FAILED\n", __FILE__, __FUNCTION__); 
	} else {
		printf("%s::%s...  \e[0;32mPASSED\e[0m\n", __FILE__, __FUNCTION__); 
	}	

}


void test_label_propagation() {

	/* create adjacency matrix graph with size 5 */
	bool equality_status = true;  
	int vertices = 7; 
	int expected_output[7] = {
		0, 1, 0, 0, -1, 1, 1
	}; 

	/* create adjacency list graph (test on smaller graph) */
	adj_list_t *g = init_graph(vertices, vertices, false);
    add_node(g, 0, "A", 3, "D", 2);
    add_node(g, 2, "C", 3, "D", 2);
    add_node(g, 3, "D", 4, "E", 2);
    add_node(g, 4, "E", 5, "F", 2);
    add_node(g, 5, "F", 6, "G", 2);
    add_node(g, 5, "F", 1, "B", 2);

	/* label nodes in graph */
	int *labels = malloc(g->v * sizeof(int)); 
	for(int i = 0; i < g->v; i++){
		labels[i] = -1; 
	}

	/* label the red nodes (red is 0, green is 1) */
	labels[0] = 0; 
	labels[1] = 1;

	int *predicted_labels = label_propagator(g, labels, 0);
	for(int i = 0; i < g->v; i++){
		if(predicted_labels[i] != expected_output[i]) {
			equality_status = false; 
		}
	}

	if(!equality_status) {
		printf("%s::%s...  FAILED\n", __FILE__, __FUNCTION__); 
	} else {
		printf("%s::%s...  \e[0;32mPASSED\e[0m\n", __FILE__, __FUNCTION__); 
	}	

}


void test_triangle_count() {

	int vertices = 6; 
	bool equality_status = true; 

	adj_list_t *g = init_graph(vertices, vertices, false);
    add_node(g, 0, "A", 1, "B", 2);
    add_node(g, 0, "A", 2, "C", 2);
    add_node(g, 1, "B", 2, "C", 2);
    add_node(g, 2, "C", 3, "D", 2);
    add_node(g, 1, "B", 3, "D", 2);
    add_node(g, 2, "C", 4, "E", 2);
    add_node(g, 2, "C", 5, "F", 2);

	int count = triangle_count(g, 4);

	if(count != 2){
		equality_status = false; 
	}

	if(!equality_status) {
		printf("%s::%s...  FAILED\n", __FILE__, __FUNCTION__); 
	} else {
		printf("%s::%s...  \e[0;32mPASSED\e[0m\n", __FILE__, __FUNCTION__); 
	}	

}

#include "includes/test_path.h"

void test_bellman_ford() {

  	int vertices = 5; // num of vertices
    int edges = 8; // num of edges
    graph_t *g = init_graph(vertices, edges, false);

    /* create nodes for graph */
    node_t *a = create_node(0, "A", 0);
    node_t *b = create_node(1, "B", 0);
    node_t *c = create_node(2, "C", 0);
    node_t *d = create_node(3, "D", 0);
    node_t *e = create_node(4, "E", 0);

    /* add relationships */
    g->list->edges[0] = create_edge(a, b, -1);
    g->list->edges[1] = create_edge(a, c, 4);
    g->list->edges[2] = create_edge(b, c, 3);
    g->list->edges[3] = create_edge(b, d, 2);
    g->list->edges[4] = create_edge(b, e, 2);
    g->list->edges[5] = create_edge(d, b, 5);
    g->list->edges[6] = create_edge(d, b, 1);
    g->list->edges[7] = create_edge(e, d, -3);

	int dist[g->vertices]; 
	int distances[5] = {0, -1, 2, -2, 1}; 
	int bellford_result = TRUE; 

    /* get result of bellman ford and print out vertices with nearest distance */
    int *result = bellman_ford_list(g, a, dist);
	for(int i = 0; i < g->vertices; i++) {
		if(result[i] != distances[i]) {
			bellford_result = FALSE; 
		}
	}

	/* validate results */ 
	if(!bellford_result) {
		printf("%s::%s...  FAILED\n", __FILE__, __FUNCTION__); 
	}
	printf("%s::%s...  \e[0;32mPASSED\e[0m\n", __FILE__, __FUNCTION__); 

}


void test_dijkstra(){

	int vertices = 7;
	int equality_status = true; 

	graph_t *g = init_graph(vertices, vertices, false);
    add_node(g->list, 0, "A", 1, "B", 2);
    add_node(g->list, 0, "A", 2, "C", 6);
    add_node(g->list, 1, "B", 3, "D", 5);
    add_node(g->list, 2, "C", 3, "D", 8);
    add_node(g->list, 3, "D", 4, "E", 10);
	add_node(g->list, 3, "D", 5, "F", 15);
	add_node(g->list, 4, "E", 5, "F", 6);
	add_node(g->list, 5, "F", 6, "G", 6);
	add_node(g->list, 4, "E", 6, "G", 2);

	/* find the shortest paths from 0 */
	int start_vertex = 0; 
	int *result = dijkstra_list(g, start_vertex);

	int output[7] = {0, 2, 6, 7, 17, 22, 19};  

	/* print vertices */
	for(int i = 0; i < g->vertices; i++) {
		assert(result[i] == output[i]); 
	}

	/* validate results */ 
	if(!equality_status) {
		printf("%s::%s...  FAILED\n", __FILE__, __FUNCTION__); 
	}
	printf("%s::%s...  \e[0;32mPASSED\e[0m\n", __FILE__, __FUNCTION__); 

}


void test_dijkstra_two(){

	int vertices = 7;
	int equality_status = true; 

	graph_t *g = init_graph(vertices, vertices, false);
    add_node(g->list, 0, "A", 1, "B", 5);
    add_node(g->list, 0, "A", 2, "C", 6);
    add_node(g->list, 1, "B", 2, "C", 15);
    add_node(g->list, 1, "B", 3, "D", 7);
    add_node(g->list, 1, "B", 4, "E", 8);
    add_node(g->list, 2, "C", 3, "D", 2);
    add_node(g->list, 2, "C", 5, "F", 4);
	add_node(g->list, 3, "D", 4, "E", 2);
	add_node(g->list, 3, "D", 5, "F", 9);
	add_node(g->list, 3, "D", 6, "G", 10);
	add_node(g->list, 4, "E", 6, "G", 3);

	/* find the shortest paths from 0 */
	int start_vertex = 0; 
	int *result = dijkstra_list(g, start_vertex);

	int output[7] = {0, 5, 6, 8, 10, 10, 13};  

	/* print vertices */
	for(int i = 0; i < g->vertices; i++) {
		if(result[i] != output[i]) {
			equality_status = false; 			
		}
	}

	/* validate results */ 
	if(!equality_status) {
		printf("%s::%s...  FAILED\n", __FILE__, __FUNCTION__); 
	}
	printf("%s::%s...  \e[0;32mPASSED\e[0m\n", __FILE__, __FUNCTION__); 

}


void test_dijkstra_vertice(){

	int vertices = 7;
	int equality_status = true; 

	graph_t *g = init_graph(vertices, vertices, false);
    add_node(g->list, 0, "A", 1, "B", 5);
    add_node(g->list, 0, "A", 2, "C", 6);
    add_node(g->list, 1, "B", 2, "C", 15);
    add_node(g->list, 1, "B", 3, "D", 7);
    add_node(g->list, 1, "B", 4, "E", 8);
    add_node(g->list, 2, "C", 3, "D", 2);
    add_node(g->list, 2, "C", 5, "F", 4);
	add_node(g->list, 3, "D", 4, "E", 2);
	add_node(g->list, 3, "D", 5, "F", 9);
	add_node(g->list, 3, "D", 6, "G", 10);
	add_node(g->list, 4, "E", 6, "G", 3);

	/* find the shortest paths from 0 */
	int start_vertex = 2; 
	int *result = dijkstra_list(g, start_vertex);

	int output[7] = {6, 9, 0, 2, 4, 4, 7}; 

	/* print vertices */
	for(int i = 0; i < g->vertices; i++) {
		if(result[i] != output[i]) {
			equality_status = false; 			
		}
	}

	/* validate results */ 
	if(!equality_status) {
		printf("%s::%s...  FAILED\n", __FILE__, __FUNCTION__); 
	}
	printf("%s::%s...  \e[0;32mPASSED\e[0m\n", __FILE__, __FUNCTION__); 

}


void test_dijkstra_vertice_two(){

	int vertices = 7;
	int equality_status = true; 

	graph_t *g = init_graph(vertices, vertices, false);
    add_node(g->list, 0, "A", 1, "B", 2);
    add_node(g->list, 0, "A", 2, "C", 6);
    add_node(g->list, 1, "B", 3, "D", 5);
    add_node(g->list, 2, "C", 3, "D", 8);
    add_node(g->list, 3, "D", 4, "E", 10);
	add_node(g->list, 3, "D", 5, "F", 15);
	add_node(g->list, 4, "E", 5, "F", 6);
	add_node(g->list, 5, "F", 6, "G", 6);
	add_node(g->list, 4, "E", 6, "G", 2);

	/* find the shortest paths from 0 */
	int start_vertex = 4; 
	int *result = dijkstra_list(g, start_vertex);

	int output[7] = {17, 15, 18, 10, 0, 6, 2}; 


	/* print vertices */
	for(int i = 0; i < g->vertices; i++) {
		if(result[i] != output[i]) {
			equality_status = false; 			
		}
	}

	/* validate results */ 
	if(!equality_status) {
		printf("%s::%s...  FAILED\n", __FILE__, __FUNCTION__); 
	}
	printf("%s::%s...  \e[0;32mPASSED\e[0m\n", __FILE__, __FUNCTION__); 

}


void test_shortest_path(){

	int vertices = 7;
	int equality_status = true; 

	graph_t *g = init_graph(vertices, vertices, false);
    add_node(g->list, 0, "A", 1, "B", 2);
    add_node(g->list, 0, "A", 2, "C", 6);
    add_node(g->list, 1, "B", 3, "D", 5);
    add_node(g->list, 2, "C", 3, "D", 8);
    add_node(g->list, 3, "D", 4, "E", 10);
	add_node(g->list, 3, "D", 5, "F", 15);
	add_node(g->list, 4, "E", 5, "F", 6);
	add_node(g->list, 5, "F", 6, "G", 6);
	add_node(g->list, 4, "E", 6, "G", 2);

	
	for(int j = 0; j < g->vertices; j++){

		/* set start vertex */
		int start_vertex = j; 
		int *result = dijkstra_list(g, start_vertex);

		/* get shortest path for each start vertex */
		for(int i = 0; i < g->vertices; i++){
			int temp_result = shortest_path_list(g, start_vertex, i);
			if(temp_result != result[i]) {
				equality_status = false; 
			} 
		}
	} 

	/* validate results */ 
	if(!equality_status) {
		printf("%s::%s...  FAILED\n", __FILE__, __FUNCTION__); 
	}
	printf("%s::%s...  \e[0;32mPASSED\e[0m\n", __FILE__, __FUNCTION__); 


}

void test_random_walk() {

	/* test random walk */
    int vertices = 5; // num of vertices

    graph_t *g = init_graph(vertices, vertices, false);
    add_node(g->list, 0, "A", 1, "B", 0);
    add_node(g->list, 0, "A", 2, "C", 0);
    add_node(g->list, 0, "A", 3, "D", 0);
    add_node(g->list, 1, "B", 2, "C", 0);
    add_node(g->list, 4, "E", 2, "C", 0);

	/* specify steps and path */ 
    int steps = 10;
    walk_t *result = random_walk_list(g, 0, steps);
	sleep(1); // random seed is based off time, wait one second for random numbers 
	walk_t *result2 = random_walk_list(g, 0, steps); 

	int equality_status = TRUE; 
    for(int i = 0; i < steps; i++) {
		if(result->path[i] != result2->path[i]) {
			equality_status = FALSE; 
		}
    }

	if(equality_status) {
		printf("%s::%s...  FAILED\n", __FILE__, __FUNCTION__); 
	} else {
		printf("%s::%s...  \e[0;32mPASSED\e[0m\n", __FILE__, __FUNCTION__); 
	}

	/* what happens if the steps aren't equal? */
    graph_t *g1 = init_graph(vertices, vertices, false);
    add_node(g1->list, 0, "A", 1, "B", 0);
    add_node(g1->list, 0, "A", 2, "C", 0);
    add_node(g1->list, 0, "A", 3, "D", 0);
    add_node(g1->list, 1, "B", 2, "C", 0);
    add_node(g1->list, 4, "E", 2, "C", 0);

    steps = 5;

    walk_t *result3 = random_walk_list(g1, 0, steps);
	sleep(1); // random seed is based off time, wait one second for random numbers 
	walk_t *result4 = random_walk_list(g1, 0, steps);

	equality_status = TRUE; 
    for(int i = 0; i < steps; i++) {
		if(result3->path[i] != result4->path[i]) {
			equality_status = FALSE; 
		}
    }

	if(equality_status) {
		printf("%s::%s...  FAILED\n", __FILE__, __FUNCTION__); 
	} else {
		printf("%s::%s::%s...  \e[0;32mPASSED\e[0m\n", __FILE__, __FUNCTION__, "step_equal"); 
	}


}


void test_weighted_random_walk() {


	/* test random walk */
    int vertices = 5; 

	/* create weighted adjacency list */ 
	graph_t *g = init_graph(vertices, vertices, false);
	add_node(g->list, 0, "A", 1, "B", 2);
	add_node(g->list, 0, "A", 2, "C", 1); 
	add_node(g->list, 0, "A", 3, "D", 1); 
	add_node(g->list, 1, "B", 2, "C", 2);
	add_node(g->list, 4, "E", 2, "C", 1);

	/* specific steps */ 
    int steps = 10;

	/* create walk structure to output results as tuple */ 
    walk_t *result = weighted_random_walk_list(g, 0, 10);

	/* iterate through walk results and check if sum matches path */ 
   	int test_sum = 0; 	
	for(int i = 0; i < result->steps; i++) {
	   	node_t *node = g->list->items[result->path[i]]->head; 	
		test_sum += node->weight; 
	}

	/* check if sum of paths is correct */ 
	int equality_condition = TRUE; 
	if(test_sum != result->weighted_sum) {
		equality_condition = FALSE; 
	}

	if(!equality_condition) {
		printf("%s::%s...  FAILED\n", __FILE__, __FUNCTION__); 
	} else {
		printf("%s::%s::%s...  \e[0;32mPASSED\e[0m\n", __FILE__, __FUNCTION__, "sum_path"); 
	}

	/* check if unique sums and paths are created for each random walk */ 
}


void test_random_walk_mat() {

	int equality_status = true; 

	/* create adjacency matrix graph with size 5 */ 
	graph_t *m = init_graph(5, 5, false); 

	/* connect a to everyone */ 
	add_node_mat(m->matrix, 0, "A", 1, "B", 0);  
	add_node_mat(m->matrix, 0, "A", 2, "C", 0);  
	add_node_mat(m->matrix, 1, "B", 2, "C", 0);  
	add_node_mat(m->matrix, 1, "B", 3, "D", 0);  
	add_node_mat(m->matrix, 2, "C", 3, "D", 0);  


	int start = 0, steps = 4; 
	walk_t *result = random_walk_mat(m, start, steps); 

	/* print result nodes*/
	int weight_sum = 0; 
	for(int i = 0; i < result->steps; i++) {
		int item = result->path[i]; 
		int weight = m->matrix->items[start*m->vertices+item]->weight;
		weight_sum += weight; 
		start = item; 
	}

	if(result->weighted_sum != weight_sum){
		equality_status = false; 
	}
	
	if(!equality_status) {
		printf("%s::%s...  FAILED\n", __FILE__, __FUNCTION__); 
	} else {
		printf("%s::%s::%s...  \e[0;32mPASSED\e[0m\n", __FILE__, __FUNCTION__, "sum_path"); 
	}

}


void test_dijkstra_mat() {

	bool equality_status = true; 

	/* create adjacency matrix graph with size 5 */ 
	graph_t *m = init_graph(7, 7, false); 

	/* connect a to everyone */ 
    add_node_mat(m->matrix, 0, "A", 1, "B", 2);
    add_node_mat(m->matrix, 0, "A", 2, "C", 6);
    add_node_mat(m->matrix, 1, "B", 3, "D", 5);
    add_node_mat(m->matrix, 2, "C", 3, "D", 8);
    add_node_mat(m->matrix, 3, "D", 4, "E", 10);
	add_node_mat(m->matrix, 3, "D", 5, "F", 15);
	add_node_mat(m->matrix, 4, "E", 5, "F", 6);
	add_node_mat(m->matrix, 5, "F", 6, "G", 6);
	add_node_mat(m->matrix, 4, "E", 6, "G", 2);

	int output[7] = {0, 2, 6, 7, 17, 22, 19};  

	int *dist = dijkstra_mat(m, 0);
	for(int i = 0; i < m->vertices; i++){
		if(dist[i] != output[i]){
			equality_status = false; 
		}
	} 

	if(!equality_status) {
		printf("%s::%s...  FAILED\n", __FILE__, __FUNCTION__); 
	} else {
		printf("%s::%s::%s...  \e[0;32mPASSED\e[0m\n", __FILE__, __FUNCTION__, "sum_path"); 
	}

}


void test_dijkstra_origin_vertex_mat() {

	int vertices = 7; 
	bool equality_status = true; 
	/* create adjacency matrix graph with size 5 */ 
	graph_t *m = init_graph(7, 7, false); 

	/* make connections */
    add_node_mat(m->matrix, 0, "A", 1, "B", 5);
    add_node_mat(m->matrix, 0, "A", 2, "C", 6);
    add_node_mat(m->matrix, 1, "B", 2, "C", 15);
    add_node_mat(m->matrix, 1, "B", 3, "D", 7);
    add_node_mat(m->matrix, 1, "B", 4, "E", 8);
	add_node_mat(m->matrix, 2, "C", 3, "D", 2);
	add_node_mat(m->matrix, 2, "C", 5, "F", 4);
	add_node_mat(m->matrix, 3, "D", 4, "E", 2);
	add_node_mat(m->matrix, 3, "D", 5, "F", 9);
	add_node_mat(m->matrix, 3, "D", 6, "G", 10);
	add_node_mat(m->matrix, 4, "E", 6, "G", 3);

	int output[7] = {6, 9, 0, 2, 4, 4, 7};

	int *dist = dijkstra_mat(m, 2);
	for(int i = 0; i < m->vertices; i++){
		if(dist[i] != output[i]){
			equality_status = false; 
		}
	}

	if(!equality_status) {
		printf("%s::%s...  FAILED\n", __FILE__, __FUNCTION__); 
	} else {
		printf("%s::%s::%s...  \e[0;32mPASSED\e[0m\n", __FILE__, __FUNCTION__, "sum_path"); 
	}

} 


void test_shortest_path_mat(){

	bool equality_status = true; 

	/* create adjacency matrix graph with size 5 */ 
	graph_t *m = init_graph(7, 7, false); 

	/* connect a to everyone */ 
    add_node_mat(m->matrix, 0, "A", 1, "B", 2);
    add_node_mat(m->matrix, 0, "A", 2, "C", 6);
    add_node_mat(m->matrix, 1, "B", 3, "D", 5);
    add_node_mat(m->matrix, 2, "C", 3, "D", 8);
    add_node_mat(m->matrix, 3, "D", 4, "E", 10);
	add_node_mat(m->matrix, 3, "D", 5, "F", 15);
	add_node_mat(m->matrix, 4, "E", 5, "F", 6);
	add_node_mat(m->matrix, 5, "F", 6, "G", 6);
	add_node_mat(m->matrix, 4, "E", 6, "G", 2);

	int output[7] = {0, 2, 6, 7, 17, 22, 19}; 

	for(int i = 0; i < m->vertices; i++){
		int dist = shortest_path_mat(m, 0, i);
		if(dist != output[i]){
			equality_status = false; 
		}
	} 

	if(!equality_status) {
		printf("%s::%s...  FAILED\n", __FILE__, __FUNCTION__); 
	} else {
		printf("%s::%s::%s...  \e[0;32mPASSED\e[0m\n", __FILE__, __FUNCTION__, "sum_path"); 
	}

}

#include "includes/graph_test.h" 

void test_adjacency_list() {

	/* test first example of bfs */ 
	adj_list_t *a = init_adj_list(5);
	add_edge(a, 0, 'A', 1, 'B');
	add_edge(a, 0, 'A', 2, 'C'); 
	add_edge(a, 0, 'A', 3, 'D'); 
	add_edge(a, 1, 'B', 2, 'C');
	add_edge(a, 4, 'E', 2, 'C');

	/* check that linked lists have the correct elements */ 
	int adj_list_test = TRUE; 
	char relationship_list[5][5] = {
		{'B', 'C', 'D'}, 
		{'A', 'C'},
		{'A', 'B', 'E'},
		{'A'},
		{'C'}
	}; 

	/* iterate an scan against relationship list */ 
	for(int i = 0; i < a->v; i++) {
		node_t *head = a->items[i].head; 
		int node_index = 0; 
		while(head) {
			if(head->label != relationship_list[i][node_index]) {
				adj_list_test = FALSE; 
			}
			head = head->next;
		   	node_index += 1; 
		}	
	}

	/* validate results */ 
	if(!adj_list_test) {
		printf("%s::%s... FAILED\n", __FILE__, __FUNCTION__); 
	}
	printf("%s::%s... \e[0;32mPASSED\e[0m\n", __FILE__, __FUNCTION__);

	/* what happens if we feed in an incorrect amount of vertices? */ 
}


void test_weighted_adjacency_list() {

	/* test first example of bfs */ 
	w_adj_list_t *a = init_w_adj_list(5);
	add_w_edge(a, 0, 'A', 1, 'B', 1);
	add_w_edge(a, 0, 'A', 2, 'C', 1); 
	add_w_edge(a, 0, 'A', 3, 'D', 1); 
	add_w_edge(a, 1, 'B', 2, 'C', 1);
	add_w_edge(a, 4, 'E', 2, 'C', 1);


	/* check that linked lists have the correct elements */ 
	int adj_list_test = TRUE; 
	char relationship_list[5][5] = {
		{'B', 'C', 'D'}, 
		{'A', 'C'},
		{'A', 'B', 'E'},
		{'A'},
		{'C'}
	};

	/* check that weights exist in adj list */ 

	/* iterate an scan against relationship list */ 
	for(int i = 0; i < a->v; i++) {
		w_node_t *head = a->items[i].head; 
		int node_index = 0; 
		while(head) {
			if(head->label != relationship_list[i][node_index]) {
				adj_list_test = FALSE; 
			}
			head = head->next;
		   	node_index += 1; 
		}	
	}

	/* validate results */ 
	if(!adj_list_test) {
		printf("%s::%s... FAILED\n", __FILE__, __FUNCTION__); 
	}
	printf("%s::%s... \e[0;32mPASSED\e[0m\n", __FILE__, __FUNCTION__);
}

void test_bfs_one() {

	/* test first example of bfs */ 
	adj_list_t *a = init_adj_list(5);
	add_edge(a, 0, 'A', 1, 'B');
	add_edge(a, 0, 'A', 2, 'C'); 
	add_edge(a, 0, 'A', 3, 'D'); 
	add_edge(a, 1, 'B', 2, 'C');
	add_edge(a, 4, 'E', 2, 'C');

	/* check queue state against it */ 
	int bfs_status = TRUE; 
	char order[5] = {'A', 'B', 'C', 'D', 'E'}; 
	node_t *head = a->items[1].head;
	queue_t *result = bfs(a, head); 

	/* iterate through queue and confirm order */ 
	for(int i = result->front_index; i <= result->rear_index; i++) {
		if(result->items[i]->label != order[i]) {
			bfs_status = FALSE; 
		}
	}

	/* validate results */ 
	if(!bfs_status) {
		printf("%s::%s... FAILED\n", __FILE__, __FUNCTION__); 
	} else {
		printf("%s::%s... \e[0;32mPASSED\e[0m\n", __FILE__, __FUNCTION__); 
	}

}


void test_bfs_two() {

	/* create labeled graph */ 
	adj_list_t *a = init_adj_list(5);
    add_edge(a, 0, 'S', 1, 'A');
    add_edge(a, 0, 'S', 2, 'B');
    add_edge(a, 0, 'S', 3, 'C');
    add_edge(a, 1, 'A', 4, 'D');
    add_edge(a, 2, 'B', 4, 'D');
    add_edge(a, 3, 'C', 4, 'D');

	/* get head node of graph */
	int bfs_status = TRUE; 
	char order[5] = {'S', 'A', 'B', 'C', 'D'}; 
	node_t *head = a->items[1].head;
	queue_t *result = bfs(a, head); 

	/* iterate through queue and confirm order */ 
	for(int i = result->front_index; i <= result->rear_index; i++) {
		if(result->items[i]->label != order[i]) {
			bfs_status = FALSE; 
		}
	}

	/* validate results */ 
	if(!bfs_status) {
		printf("%s::%s...  FAILED\n", __FILE__, __FUNCTION__); 
	}
	printf("%s::%s...  \e[0;32mPASSED\e[0m\n", __FILE__, __FUNCTION__); 

}

void test_dfs_one() {

	/* test first example of bfs */ 
	adj_list_t *a = init_adj_list(5); 
	add_edge(a, 0, 'A', 1, 'B'); 
	add_edge(a, 0, 'A', 2, 'C'); 
	add_edge(a, 0, 'A', 3, 'D'); 
	add_edge(a, 1, 'B', 2, 'C');
	add_edge(a, 4, 'E', 2, 'C');

	/* check queue state against it */ 
	int dfs_status = TRUE; 
	char order[5] = {'A', 'B', 'C', 'E', 'D'}; 
	queue_t *q = init_queue(a->v); 	

	/* get head node of graph */ 
	node_t *head = a->items[1].head;

	/* check result of bfs */ 
	int result = dfs(q, a, head); 

	/* iterate through queue and confirm order */ 
	for(int i = q->front_index; i <= q->rear_index; i++) {
		if(q->items[i]->label != order[i]) {
			dfs_status = FALSE; 
		}
	}

	/* validate results */ 
	if(!dfs_status) {
		printf("%s::%s...  FAILED\n", __FILE__, __FUNCTION__); 
	}
	printf("%s::%s...  \e[0;32mPASSED\e[0m\n", __FILE__, __FUNCTION__); 

}


void test_bellman_ford() {

  	int vertices = 5; // num of vertices
    int edges = 8; // num of edges
    graph_t *g = init_graph(vertices, edges);

    /* create nodes for graph */
    node_t *a = create_node(0, 'A');
    node_t *b = create_node(1, 'B');
    node_t *c = create_node(2, 'C');
    node_t *d = create_node(3, 'D');
    node_t *e = create_node(4, 'E');

    /* add relationships */
    g->edges[0] = create_edge(a, b, -1);
    g->edges[1] = create_edge(a, c, 4);
    g->edges[2] = create_edge(b, c, 3);
    g->edges[3] = create_edge(b, d, 2);
    g->edges[4] = create_edge(b, e, 2);
    g->edges[5] = create_edge(d, b, 5);
    g->edges[6] = create_edge(d, b, 1);
    g->edges[7] = create_edge(e, d, -3);

	int dist[g->v]; 
	int distances[5] = {0, -1, 2, -2, 1}; 
	int bellford_result = TRUE; 

    /* get result of bellman ford and print out vertices with nearest distance */
    int *result = bellman_ford(g, a, dist);
	for(int i = 0; i < g->v; i++) {
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


void test_random_walk() {

	/* test random walk */
    int vertices = 5; // num of vertices

    adj_list_t *a = init_adj_list(vertices);
    add_edge(a, 0, 'A', 1, 'B');
    add_edge(a, 0, 'A', 2, 'C');
    add_edge(a, 0, 'A', 3, 'D');
    add_edge(a, 1, 'B', 2, 'C');
    add_edge(a, 4, 'E', 2, 'C');

	/* specify steps and path */ 
    int steps = 10;
    int path[steps];
	int path2[steps]; 
    int *result = random_walk(a, 0, steps, path);
	sleep(1); // random seed is based off time, wait one second for random numbers 
	int *result2 = random_walk(a, 0, steps, path2); 

	int equality_status = TRUE; 
    for(int i = 0; i < steps; i++) {
		if(path[i] != path2[i]) {
			equality_status = FALSE; 
		}
    }

	if(equality_status) {
		printf("%s::%s...  FAILED\n", __FILE__, __FUNCTION__); 
	} else {
		printf("%s::%s...  \e[0;32mPASSED\e[0m\n", __FILE__, __FUNCTION__); 
	}

	/* what happens if the steps aren't equal? */
    adj_list_t *a1 = init_adj_list(vertices);
    add_edge(a1, 0, 'A', 1, 'B');
    add_edge(a1, 0, 'A', 2, 'C');
    add_edge(a1, 0, 'A', 3, 'D');
    add_edge(a1, 1, 'B', 2, 'C');
    add_edge(a1, 4, 'E', 2, 'C');

    steps = 5;
    int path3[steps];
	int path4[4];

    int *result3 = random_walk(a1, 0, steps, path3);
	sleep(1); // random seed is based off time, wait one second for random numbers 
	int *result4 = random_walk(a1, 0, steps, path4);

	equality_status = TRUE; 
    for(int i = 0; i < steps; i++) {
		if(path[i] != path2[i]) {
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
	w_adj_list_t *a = init_w_adj_list(5);
	add_w_edge(a, 0, 'A', 1, 'B', 2);
	add_w_edge(a, 0, 'A', 2, 'C', 1); 
	add_w_edge(a, 0, 'A', 3, 'D', 1); 
	add_w_edge(a, 1, 'B', 2, 'C', 2);
	add_w_edge(a, 4, 'E', 2, 'C', 1);

	/* specific steps */ 
    int steps = 10;
    int path[steps];
	int path2[steps]; 

	/* create walk structure to output results as tuple */ 
	walk_t *w = init_walk(steps);
    walk_t *result = weighted_random_walk(a, w, 0);

	/* iterate through walk results and check if sum matches path */ 
   	int test_sum = 0; 	
	for(int i = 0; i < result->steps; i++) {
	   	w_node_t *node = a->items[w->path[i]].head; 	
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


void test_degree_centrality() {

  	int vertices = 5; // num of vertices
    int edges = 8; // num of edges
    graph_t *g = init_graph(vertices, edges);

    /* create nodes for graph */
    node_t *a = create_node(0, 'A');
    node_t *b = create_node(1, 'B');
    node_t *c = create_node(2, 'C');
    node_t *d = create_node(3, 'D');
    node_t *e = create_node(4, 'E');

    /* add relationships */
    g->edges[0] = create_edge(a, b, -1);
    g->edges[1] = create_edge(a, c, 4);
    g->edges[2] = create_edge(b, c, 3);
    g->edges[3] = create_edge(b, d, 2);
    g->edges[4] = create_edge(b, e, 2);
    g->edges[5] = create_edge(d, b, 5);
    g->edges[6] = create_edge(d, b, 1);
    g->edges[7] = create_edge(e, d, -3);

}

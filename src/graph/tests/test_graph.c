#include "includes/test_graph.h" 

void test_graph() {

	/* test first example of bfs */ 
	graph_t *g = init_graph(5, 5, false);
	add_node(g, 0, "A", 1, "B", 0);
	add_node(g, 0, "A", 2, "C", 0); 
	add_node(g, 0, "A", 3, "D", 0); 
	add_node(g, 1, "B", 2, "C", 0);
	add_node(g, 4, "E", 2, "C", 0);

	/* check that linked lists have the correct elements */ 
	int adj_list_test = TRUE; 
	char *relationship_list[5][5] = {
		{"B", "C", "D"}, 
		{"A", "C"},
		{"A", "B", "E"},
		{"A"},
		{"C"}
	}; 

	/* iterate an scan against relationship list */ 
	for(int i = 0; i < g->v; i++) {
		node_t *head = g->items[i].head; 
		int node_index = 0; 
		while(head) {
			int condition = strcmp(head->label, relationship_list[i][node_index]); 
			if(condition != 0) {
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


void test_weighted_graph() {

	/* test first example of bfs */ 
	graph_t *g = init_graph(5, 5, false);
	add_node(g, 0, "A", 1, "B", 1);
	add_node(g, 0, "A", 2, "C", 1); 
	add_node(g, 0, "A", 3, "D", 1); 
	add_node(g, 1, "B", 2, "C", 1);
	add_node(g, 4, "E", 2, "C", 1);


	/* check that linked lists have the correct elements */ 
	int adj_list_test = TRUE; 
	char *relationship_list[5][5] = {
		{"B", "C", "D"}, 
		{"A", "C"},
		{"A", "B", "E"},
		{"A"},
		{"C"}
	}; 

	/* check that weights exist in adj list */ 

	/* iterate an scan against relationship list */ 
	for(int i = 0; i < g->v; i++) {
		node_t *head = g->items[i].head; 
		int node_index = 0; 
		while(head) {
			int condition = strcmp(head->label, relationship_list[i][node_index]); 
			if(condition != 0) {
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


void test_transpose_graph() {

	/* test tranpose of adjacency list */
    int vertices = 8; 
	int adj_list_test = TRUE; 

	/* create adjacency list */ 
	graph_t *g = init_graph(vertices, vertices, true);
	graph_t *result_list = init_graph(vertices, vertices, true); 

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
	add_node(g, 7, "H", 7, "H", 0);

	/* call the tranpose method */ 
	graph_t *result = transpose_items(g, result_list); 

	/* expected neighors output */
	char *relationship_list[8][8] = {
		{"D"}, 
		{"A"},
		{"B"},
		{"C"},
		{"C", "G"},
		{"E"}, 
		{"F"}, 
		{"G", "H"}, 
	};

	/* compare the results of input and output adj list */
	for(int i = 0; i < result->v; i++) {
		int node_index = 0; 
		node_t *head = result->items[i].head; 
		while(head) {

			/* check if values are equal */ 
			int condition = strcmp(head->label, relationship_list[i][node_index]); 
			if(condition != 0) {
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



void test_to_matrix() {

	/* test transpose of adjacency list */
    int vertices = 8; 
	int equality_status = TRUE;

	/* expected result after directed matrix conversion */
	int expected_output[8][8] = {
		{0,1,0,1,0,0,0,0},
		{1,0,1,0,0,0,0,0},
		{0,1,0,1,1,0,0,0},
		{1,0,1,0,0,0,0,0},
		{0,0,1,0,0,1,1,0},
		{0,0,0,0,1,0,1,0},
		{0,0,0,0,1,1,0,1},
		{0,0,0,0,0,0,1,1}
	};	

	/* create adjacency list */ 
	graph_t *g = init_graph(vertices, vertices, false);
	mat_t *result = init_mat(vertices, vertices); 

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
	add_node(g, 7, "H", 7, "H", 0);

	/* test to regular matrix conversion */ 
	mat_t *output = to_matrix(result, g);

	/* check output */ 
	for(int i = 0; i < vertices; i++) {
		for(int j = 0; j < vertices; j++) {
			if(output->arr[i][j] != expected_output[i][j]) {
				equality_status = FALSE; 
			}
		}
	}


	/* validate results */ 
	if(!equality_status) {
		printf("%s::%s... FAILED\n", __FILE__, __FUNCTION__); 
	}
	printf("%s::%s... \e[0;32mPASSED\e[0m\n", __FILE__, __FUNCTION__);

}


void test_to_directed_matrix() {

	
	/* test transpose of adjacency list */
    int vertices = 8; 
	int equality_status = TRUE;

	/* expected result after directed matrix conversion */
	int expected_output[8][8] = {
		{0,1,0,0,0,0,0,0},
		{0,0,1,0,0,0,0,0},
		{0,0,0,1,1,0,0,0},
		{1,0,0,0,0,0,0,0},
		{0,0,0,0,0,1,0,0},
		{0,0,0,0,0,0,1,0},
		{0,0,0,0,1,0,0,1},
		{0,0,0,0,0,0,0,1}
	};	

	/* create adjacency list */ 
	graph_t *g = init_graph(vertices, vertices, true);
	mat_t *result = init_mat(vertices, vertices); 

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
	add_node(g, 7, "H", 7, "H", 0);

	/* test directed matrix conversion */ 
	mat_t *output = to_directed_matrix(result, g);

	/* check output */ 
	for(int i = 0; i < vertices; i++) {
		for(int j = 0; j < vertices; j++) {
			if(output->arr[i][j] != expected_output[i][j]) {
				equality_status = FALSE; 
			}
		}
	}

	/* validate results */ 
	if(!equality_status) {
		printf("%s::%s... FAILED\n", __FILE__, __FUNCTION__); 
	}
	printf("%s::%s... \e[0;32mPASSED\e[0m\n", __FILE__, __FUNCTION__);
}


void test_to_weighted_matrix() {

	/* vertices and equality status */ 
	int vertices = 5;
	int equality_status = TRUE;

	/* expected result after directed matrix conversion */
	int expected_output[5][5] = {
		{0,1,2,3,0},
		{1,0,4,0,0},
		{2,4,0,0,5},
		{3,0,0,0,0},
		{0,0,5,0,0},
	};	

	/* create adj lists */ 
	graph_t *g = init_graph(vertices, vertices, false);
	mat_t *result = init_mat(vertices, vertices);

	/* build graph */ 
	add_node(g, 0, "A", 1, "B", 1);
	add_node(g, 0, "A", 2, "C", 2); 
	add_node(g, 0, "A", 3, "D", 3); 
	add_node(g, 1, "B", 2, "C", 4);
	add_node(g, 4, "E", 2, "C", 5);


	/* test directed matrix conversion */ 
	mat_t *output = to_weighted_matrix(result, g);

	/* check output */ 
	for(int i = 0; i < vertices; i++) {
		for(int j = 0; j < vertices; j++) {
			if(output->arr[i][j] != expected_output[i][j]) {
				equality_status = FALSE; 
			}
		}
	}


	/* validate results */ 
	if(!equality_status) {
		printf("%s::%s... FAILED\n", __FILE__, __FUNCTION__); 
	}
	printf("%s::%s... \e[0;32mPASSED\e[0m\n", __FILE__, __FUNCTION__);
}


void test_to_directed_weighted_matrix() {

	/* vertices and equality status */ 
	int vertices = 8; 
	int equality_status = TRUE;

	/* expected result after directed matrix conversion */
	int expected_output[8][8] = {
		{0,1,0,0,0,0,0,0},
		{0,0,2,0,0,0,0,0},
		{0,0,0,3,5,0,0,0},
		{4,0,0,0,0,0,0,0},
		{0,0,0,0,0,6,0,0},
		{0,0,0,0,0,0,7,0},
		{0,0,0,0,8,0,0,9},
		{0,0,0,0,0,0,0,10}
	};	

	/* test first example of weighted matrix */ 
	graph_t *g = init_graph(vertices, vertices, true);
	mat_t *result = init_mat(vertices, vertices);

	/* first community */ 
	add_node(g, 0, "A", 1, "B", 1);
	add_node(g, 1, "B", 2, "C", 2);
	add_node(g, 2, "C", 3, "D", 3);
	add_node(g, 3, "D", 0, "A", 4);

	/* bridge */ 
	add_node(g, 2, "C", 4, "E", 5);

	/* second community */ 
	add_node(g, 4, "E", 5, "F", 6);
	add_node(g, 5, "F", 6, "G", 7);
	add_node(g, 6, "G", 4, "E", 8);
	add_node(g, 6, "G", 7, "H", 9);
	add_node(g, 7, "H", 7, "H", 10);

	/* test directed matrix conversion */ 
	mat_t *output = to_directed_weighted_matrix(result, g);

	/* check output */ 
	for(int i = 0; i < vertices; i++) {
		for(int j = 0; j < vertices; j++) {
			if(output->arr[i][j] != expected_output[i][j]) {
				equality_status = FALSE; 
			}
		}
	}

	/* validate results */ 
	if(!equality_status) {
		printf("%s::%s... FAILED\n", __FILE__, __FUNCTION__); 
	}
	printf("%s::%s... \e[0;32mPASSED\e[0m\n", __FILE__, __FUNCTION__);


}


void test_to_list() {

	/* vertices and equality status */ 
	int vertices = 5; 
	int equality_status = TRUE;

	/* test first example of weighted matrix */ 
	graph_t *g = init_graph(vertices, vertices, true);
	mat_t *m = init_mat(5, 5); 

	/* build matrix */ 
	entry(m, 0, 1); 
	entry(m, 0, 2); 
	entry(m, 1, 2); 
	entry(m, 2, 0); 
	entry(m, 2, 3);

	/* test directed matrix conversion */ 
	graph_t *output = to_list(g, m);

	/* expected relationships from adjacency list */ 
	char *relationship_list[5][5] = {
		{"B", "C"}, 
		{"A", "C"},
		{"A", "B", "D"},
		{"C"}
	};

	/* iterate through list and match relationships */ 
	for(int i = 0; i < g->v; i++) {
		node_t *head = g->items[i].head; 
		int node_index = 0; 
		while(head) {
			int condition = strcmp(head->label, relationship_list[i][node_index]); 
			if(condition != 0) {
				equality_status = FALSE; 
			}

			head = head->next;
		   	node_index += 1; 
		}	
	}

	/* validate results */ 
	if(!equality_status) {
		printf("%s::%s... FAILED\n", __FILE__, __FUNCTION__); 
	}
	printf("%s::%s... \e[0;32mPASSED\e[0m\n", __FILE__, __FUNCTION__);
}


void test_to_weighted_list() {

	/* vertices and equality status */ 
	int vertices = 5; 
	int equality_status = TRUE;

	/* test first example of weighted matrix */ 
	graph_t *g = init_graph(vertices, vertices, false);
	mat_t *m = init_mat(vertices, vertices);

	/* build matrix */ 
	weighted_entry(m, 0, 1, 1); 
	weighted_entry(m, 0, 2, 2); 
	weighted_entry(m, 1, 2, 3); 
	weighted_entry(m, 2, 0, 4); 
	weighted_entry(m, 2, 3, 5);

	/* expected relationships from adjacency list */ 
	int relationship_list[5][6] = {
		{1, 4, 1, 4}, 
		{1,1,3,3},
		{4,3,4,3, 5,5},
		{5,5}
	};

	/* test directed matrix conversion */ 
	graph_t *output = to_weighted_list(g, m);

	/* iterate through list and match relationships */ 
	for(int i = 0; i < g->v; i++) {
		node_t *head = g->items[i].head; 
		int node_index = 0; 
		while(head) {
			if(head->weight != relationship_list[i][node_index]) {
				equality_status = FALSE;
			}


			head = head->next;
		   	node_index += 1; 
		}	
	}

	/* validate results */ 
	if(!equality_status) {
		printf("%s::%s... FAILED\n", __FILE__, __FUNCTION__); 
	}
	printf("%s::%s... \e[0;32mPASSED\e[0m\n", __FILE__, __FUNCTION__);


}


void test_to_directed_list() {

	/* vertices and equality status */ 
	int vertices = 8; 
	int equality_status = TRUE;

	/* test first example of weighted matrix */ 
	graph_t *g = init_graph(vertices, vertices, true);
	mat_t *m = init_mat(vertices, vertices);

	/* build matrix */ 
	directed_entry(m, 0, 1); 
	directed_entry(m, 0, 2); 
	directed_entry(m, 1, 2); 
	directed_entry(m, 2, 0); 
	directed_entry(m, 2, 3);

	/* expected relationships from adjacency list */ 
	char *relationship_list[5][6] = {
		{"B", "C"}, 
		{"C"},
		{"A","D"}
	};

	/* test directed matrix conversion */ 
	graph_t *output = to_weighted_list(g, m);

	/* iterate through list and match relationships */ 
	for(int i = 0; i < g->v; i++) {
		node_t *head = g->items[i].head; 
		int node_index = 0; 
		while(head) {
			int condition = strcmp(head->label, relationship_list[i][node_index]); 
			if(condition != 0) {
				equality_status = FALSE; 
			}
			head = head->next;
		   	node_index += 1; 
		}	
	}

	/* validate results */ 
	if(!equality_status) {
		printf("%s::%s... FAILED\n", __FILE__, __FUNCTION__); 
	}
	printf("%s::%s... \e[0;32mPASSED\e[0m\n", __FILE__, __FUNCTION__);

}


void test_to_directed_weighted_list() {

	/* vertices and equality status */ 
	int vertices = 8; 
	int equality_status = TRUE;

	/* test first example of weighted matrix */ 
	graph_t *g = init_graph(vertices, vertices, true);
	mat_t *m = init_mat(vertices, vertices);

	/* build matrix */ 
	directed_weighted_entry(m, 0, 1, 1); 
	directed_weighted_entry(m, 0, 2, 2); 
	directed_weighted_entry(m, 1, 2, 3); 
	directed_weighted_entry(m, 2, 0, 4); 
	directed_weighted_entry(m, 2, 3, 5);

	/* expected relationships from adjacency list */ 
	char *relationship_list[5][5] = {
		{"B", "C"}, 
		{"C"},
		{"A","D"}
	};

	/* test directed matrix conversion */ 
	graph_t *output = to_directed_weighted_list(g, m);

	/* iterate through list and match relationships */ 
	for(int i = 0; i < g->v; i++) {
		node_t *head = g->items[i].head; 
		int node_index = 0; 
		while(head) {
			int condition = strcmp(head->label, relationship_list[i][node_index]); 
			if(condition != 0) {
				equality_status = FALSE; 
			}
			head = head->next;
		   	node_index += 1; 
		}	
	}

	/* validate results */ 
	if(!equality_status) {
		printf("%s::%s... FAILED\n", __FILE__, __FUNCTION__); 
	}
	printf("%s::%s... \e[0;32mPASSED\e[0m\n", __FILE__, __FUNCTION__);

}

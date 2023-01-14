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


void test_transpose_adj_list() {

	/* test tranpose of adjacency list */
    int vertices = 8; 
	int adj_list_test = TRUE; 

	/* create adjacency list */ 
	adj_list_t *a = init_adj_list(vertices);
	adj_list_t *result_list = init_adj_list(vertices); 

	/* first community */ 
	add_directed_edge(a, 0, 'A', 1, 'B');
	add_directed_edge(a, 1, 'B', 2, 'C');
	add_directed_edge(a, 2, 'C', 3, 'D');
	add_directed_edge(a, 3, 'D', 0, 'A');

	/* bridge */ 
	add_directed_edge(a, 2, 'C', 4, 'E');

	/* second community */ 
	add_directed_edge(a, 4, 'E', 5, 'F');
	add_directed_edge(a, 5, 'F', 6, 'G');
	add_directed_edge(a, 6, 'G', 4, 'E');
	add_directed_edge(a, 6, 'G', 7, 'H');
	add_directed_edge(a, 7, 'H', 7, 'H');

	/* call the tranpose method */ 
	adj_list_t *result = transpose_adj(a, result_list); 

	/* expected neighors output */
	char relationship_list[8][8] = {
		{'D'}, 
		{'A'},
		{'B'},
		{'C'},
		{'C', 'G'},
		{'E'}, 
		{'F'}, 
		{'G', 'H'}, 
	};

	/* compare the results of input and output adj list */
	for(int i = 0; i < result->v; i++) {
		int node_index = 0; 
		node_t *head = result->items[i].head; 
		while(head) {

			/* check if values are equal */ 
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
	adj_list_t *a = init_adj_list(vertices);
	mat_t *result = init_mat(vertices, vertices); 

	/* first community */ 
	add_directed_edge(a, 0, 'A', 1, 'B');
	add_directed_edge(a, 1, 'B', 2, 'C');
	add_directed_edge(a, 2, 'C', 3, 'D');
	add_directed_edge(a, 3, 'D', 0, 'A');

	/* bridge */ 
	add_directed_edge(a, 2, 'C', 4, 'E');

	/* second community */ 
	add_directed_edge(a, 4, 'E', 5, 'F');
	add_directed_edge(a, 5, 'F', 6, 'G');
	add_directed_edge(a, 6, 'G', 4, 'E');
	add_directed_edge(a, 6, 'G', 7, 'H');
	add_directed_edge(a, 7, 'H', 7, 'H');

	/* test to regular matrix conversion */ 
	mat_t *output = to_matrix(result, a);

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
	adj_list_t *a = init_adj_list(vertices);
	mat_t *result = init_mat(vertices, vertices); 

	/* first community */ 
	add_directed_edge(a, 0, 'A', 1, 'B');
	add_directed_edge(a, 1, 'B', 2, 'C');
	add_directed_edge(a, 2, 'C', 3, 'D');
	add_directed_edge(a, 3, 'D', 0, 'A');

	/* bridge */ 
	add_directed_edge(a, 2, 'C', 4, 'E');

	/* second community */ 
	add_directed_edge(a, 4, 'E', 5, 'F');
	add_directed_edge(a, 5, 'F', 6, 'G');
	add_directed_edge(a, 6, 'G', 4, 'E');
	add_directed_edge(a, 6, 'G', 7, 'H');
	add_directed_edge(a, 7, 'H', 7, 'H');

	/* test directed matrix conversion */ 
	mat_t *output = to_directed_matrix(result, a);

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
	w_adj_list_t *a = init_w_adj_list(vertices);
	mat_t *result = init_mat(vertices, vertices);

	/* build graph */ 
	add_w_edge(a, 0, 'A', 1, 'B', 1);
	add_w_edge(a, 0, 'A', 2, 'C', 2); 
	add_w_edge(a, 0, 'A', 3, 'D', 3); 
	add_w_edge(a, 1, 'B', 2, 'C', 4);
	add_w_edge(a, 4, 'E', 2, 'C', 5);


	/* test directed matrix conversion */ 
	mat_t *output = to_weighted_matrix(result, a);

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
	w_adj_list_t *a = init_w_adj_list(8);
	mat_t *result = init_mat(vertices, vertices);

	/* first community */ 
	add_directed_weighted_edge(a, 0, 'A', 1, 'B', 1);
	add_directed_weighted_edge(a, 1, 'B', 2, 'C', 2);
	add_directed_weighted_edge(a, 2, 'C', 3, 'D', 3);
	add_directed_weighted_edge(a, 3, 'D', 0, 'A', 4);

	/* bridge */ 
	add_directed_weighted_edge(a, 2, 'C', 4, 'E', 5);

	/* second community */ 
	add_directed_weighted_edge(a, 4, 'E', 5, 'F', 6);
	add_directed_weighted_edge(a, 5, 'F', 6, 'G', 7);
	add_directed_weighted_edge(a, 6, 'G', 4, 'E', 8);
	add_directed_weighted_edge(a, 6, 'G', 7, 'H', 9);
	add_directed_weighted_edge(a, 7, 'H', 7, 'H', 10);

	/* test directed matrix conversion */ 
	mat_t *output = to_directed_weighted_matrix(result, a);

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
	adj_list_t *a = init_adj_list(vertices);
	mat_t *m = init_mat(5, 5); 

	/* build matrix */ 
	entry(m, 0, 1); 
	entry(m, 0, 2); 
	entry(m, 1, 2); 
	entry(m, 2, 0); 
	entry(m, 2, 3);

	/* test directed matrix conversion */ 
	adj_list_t *output = to_list(a, m);

	/* expected relationships from adjacency list */ 
	char relationship_list[5][5] = {
		{'B', 'C'}, 
		{'A', 'C'},
		{'A', 'B', 'D'},
		{'C'}
	};

	/* iterate through list and match relationships */ 
	for(int i = 0; i < a->v; i++) {
		node_t *head = a->items[i].head; 
		int node_index = 0; 
		while(head) {
			if(head->label != relationship_list[i][node_index]) {
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
	w_adj_list_t *a = init_w_adj_list(vertices);
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
	w_adj_list_t *output = to_weighted_list(a, m);


	/* iterate through list and match relationships */ 
	for(int i = 0; i < a->v; i++) {
		w_node_t *head = a->items[i].head; 
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
	w_adj_list_t *a = init_w_adj_list(8);
	mat_t *m = init_mat(vertices, vertices);

	/* build matrix */ 
	directed_entry(m, 0, 1); 
	directed_entry(m, 0, 2); 
	directed_entry(m, 1, 2); 
	directed_entry(m, 2, 0); 
	directed_entry(m, 2, 3);

	/* expected relationships from adjacency list */ 
	char relationship_list[5][6] = {
		{'B', 'C', 'C'}, 
		{'A', 'C'},
		{'A', 'B', 'A', 'D'},
		{'C'}
	};

	/* test directed matrix conversion */ 
	w_adj_list_t *output = to_weighted_list(a, m);

	/* iterate through list and match relationships */ 
	for(int i = 0; i < a->v; i++) {
		w_node_t *head = a->items[i].head; 
		int node_index = 0; 
		while(head) {
			if(head->label != relationship_list[i][node_index]) {
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
	w_adj_list_t *a = init_w_adj_list(8);
	mat_t *m = init_mat(vertices, vertices);

	/* build matrix */ 
	directed_weighted_entry(m, 0, 1, 1); 
	directed_weighted_entry(m, 0, 2, 2); 
	directed_weighted_entry(m, 1, 2, 3); 
	directed_weighted_entry(m, 2, 0, 4); 
	directed_weighted_entry(m, 2, 3, 5);

	/* expected relationships from adjacency list */ 
	char relationship_list[5][5] = {
		{'B', 'C'}, 
		{'C'},
		{'A','D'}
	};

	/* test directed matrix conversion */ 
	w_adj_list_t *output = to_directed_weighted_list(a, m);

	/* iterate through list and match relationships */ 
	for(int i = 0; i < a->v; i++) {
		w_node_t *head = a->items[i].head; 
		int node_index = 0; 
		while(head) {
			if(head->label != relationship_list[i][node_index]) {
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




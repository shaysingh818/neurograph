#include "includes/test_graph.h" 


void test_to_list() {

	/* vertices and equality status */ 
	int vertices = 5; 
	int equality_status = TRUE;

	/* test first example of weighted matrix */ 
	adj_list_t *g = init_adj_list(vertices, vertices, true);
	mat_graph_t *m = init_matrice_graph(vertices);

	/*  create entries */
	entry_t *a = init_entry(0, "A");  
	entry_t *b = init_entry(1, "B");  
	entry_t *c = init_entry(2, "C");  
	entry_t *d = init_entry(3, "D");  

	/* build matrix */ 
	insert(m, a, b, 0, false); 
	insert(m, a, c, 0, false); 
	insert(m, b, c, 0, false); 
	insert(m, c, a, 0, false); 
	insert(m, c, d, 0, false);

	/* test directed matrix conversion */ 
	adj_list_t *output = to_list(g, m, false);

	/* expected relationships from adjacency list */ 
	char *relationship_list[5][5] = {
		{"B", "C"}, 
		{"A", "C"},
		{"A", "B", "D"},
		{"C"}
	};

	/* iterate through list and match relationships */ 
	for(int i = 0; i < g->v; i++) {
		node_t *head = g->items[i]->head; 
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
	} else {
		printf("%s::%s... \e[0;32mPASSED\e[0m\n", __FILE__, __FUNCTION__);
	}
}


void test_to_weighted_list() {

	/* vertices and equality status */ 
	int vertices = 5; 
	int equality_status = TRUE;

	/* test first example of weighted matrix */ 
	adj_list_t *g = init_adj_list(vertices, vertices, false);
	mat_graph_t *m = init_matrice_graph(vertices);

	/*  create entries */
	entry_t *a = init_entry(0, "A");  
	entry_t *b = init_entry(1, "B");  
	entry_t *c = init_entry(2, "C");  
	entry_t *d = init_entry(3, "D");  

	/* build matrix */ 
	insert(m, a, b, 1, false); 
	insert(m, a, c, 2, false); 
	insert(m, b, c, 3, false); 
	insert(m, c, a, 4, false); 
	insert(m, c, d, 5, false);

	/* expected relationships from adjacency list */ 
	int relationship_list[5][6] = {
		{1, 4, 1, 4}, 
		{1,1,3,3},
		{4,3,4,3, 5,5},
		{5,5}
	};

	/* test directed matrix conversion */ 
	adj_list_t *output = to_list(g, m, false);

	/* iterate through list and match relationships */ 
	for(int i = 0; i < g->v; i++) {
		node_t *head = g->items[i]->head; 
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
	} else {
		printf("%s::%s... \e[0;32mPASSED\e[0m\n", __FILE__, __FUNCTION__);
	}


}


void test_to_directed_list() {

	/* vertices and equality status */ 
	int vertices = 8; 
	int equality_status = TRUE;

	/* test first example of weighted matrix */ 
	adj_list_t *g = init_adj_list(vertices, vertices, true);
	mat_graph_t *m = init_matrice_graph(vertices);

	entry_t *a = init_entry(0, "A"); 
	entry_t *b = init_entry(1, "B"); 
	entry_t *c = init_entry(2, "C"); 
	entry_t *d = init_entry(3, "D");

	/* build matrix */ 
	insert(m, a, b, 0, true); 
	insert(m, a, c, 0, true); 
	insert(m, b, c, 0, true); 
	insert(m, c, a, 0, true); 
	insert(m, c, d, 0, true);


	/* expected relationships from adjacency list */ 
	char *relationship_list[5][6] = {
		{"B", "C"}, 
		{"C"},
		{"A","D"}
	};

	/* test directed matrix conversion */ 
	adj_list_t *output = to_list(g, m, true);

	/* iterate through list and match relationships */ 
	for(int i = 0; i < g->v; i++) {
		node_t *head = g->items[i]->head; 
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
	} else {
		printf("%s::%s... \e[0;32mPASSED\e[0m\n", __FILE__, __FUNCTION__);
	}

}


void test_to_directed_weighted_list() {

	/* vertices and equality status */ 
	int vertices = 8; 
	int equality_status = TRUE;

	/* test first example of weighted matrix */ 
	adj_list_t *g = init_adj_list(vertices, vertices, true);
	mat_graph_t *m = init_matrice_graph(vertices);

	/*  create entries */
	entry_t *a = init_entry(0, "A");  
	entry_t *b = init_entry(1, "B");  
	entry_t *c = init_entry(2, "C");  
	entry_t *d = init_entry(3, "D");  

	/* build matrix */ 
	insert(m, a, b, 0, true); 
	insert(m, a, c, 0, true); 
	insert(m, b, c, 0, true); 
	insert(m, c, a, 0, true); 
	insert(m, c, d, 0, true);

	/* expected relationships from adjacency list */ 
	char *relationship_list[5][5] = {
		{"B", "C"}, 
		{"C"},
		{"A","D"}
	};

	/* test directed matrix conversion */ 
	adj_list_t *output = to_list(g, m, true);

	/* iterate through list and match relationships */ 
	for(int i = 0; i < g->v; i++) {
		node_t *head = g->items[i]->head; 
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
	} else {
		printf("%s::%s... \e[0;32mPASSED\e[0m\n", __FILE__, __FUNCTION__);
	}

}


void test_to_matrix() {

	/* test transpose of adjacency list */
    int vertices = 8; 
	int equality_status = TRUE;

	/* expected result after directed matrix conversion */
	int expected_output[8][8] = {
		{-1,1,-1,3,-1,-1,-1,-1},
		{0,-1,2,-1,-1,-1,-1,-1},
		{-1,1,-1,3,4,-1,-1,-1},
		{0,-1,2,-1,-1,-1,-1,-1},
		{-1,-1,2,-1,-1,5,6,-1},
		{-1,-1,-1,-1,4,-1,6,-1},
		{-1,-1,-1,-1,4,5,-1,7},
		{-1,-1,-1,-1,-1,-1,6,7}
	};	

	/* create adjacency list */ 
	adj_list_t *g = init_adj_list(vertices, vertices, false);
	mat_graph_t *result = init_matrice_graph(vertices); 

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
	mat_graph_t *output = to_matrix(result, g, false);
	int v = output->vertices;

	/* check output */ 
	for(int i = 0; i < vertices; i++) {
		for(int j = 0; j < vertices; j++) {
			if(output->matrix[i*v+j]->id != expected_output[i][j]) {
				equality_status = FALSE; 
			}
		}
	}


	/* validate results */ 
	if(!equality_status) {
		printf("%s::%s... FAILED\n", __FILE__, __FUNCTION__); 
	} else {
		printf("%s::%s... \e[0;32mPASSED\e[0m\n", __FILE__, __FUNCTION__);
	}

}


void test_to_directed_matrix() {

	
	/* test transpose of adjacency list */
    int vertices = 8; 
	int equality_status = TRUE;

	/* expected result after directed matrix conversion */
	int expected_output[8][8] = {
		{-1,1,-1,-1,-1,-1,-1,-1},
		{-1,-1,2,-1,-1,-1,-1,-1},
		{-1,-1,-1,3,4,-1,-1,-1},
		{0,-1,-1,-1,-1,-1,-1,-1},
		{-1,-1,-1,-1,-1,5,-1,-1},
		{-1,-1,-1,-1,-1,-1,6,-1},
		{-1,-1,-1,-1,4,-1,-1,7},
		{-1,-1,-1,-1,-1,-1,-1,7}
	};	

	/* create adjacency list */ 
	adj_list_t *g = init_adj_list(vertices, vertices, true);
	mat_graph_t *result = init_matrice_graph(vertices); 

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
	mat_graph_t *output = to_matrix(result, g, true);
	int v = output->vertices; 


	/* check output */ 
	for(int i = 0; i < vertices; i++) {
		for(int j = 0; j < vertices; j++) {
			if(output->matrix[i*v+j]->id != expected_output[i][j]) {
				equality_status = FALSE; 
			}
		}
	}

	/* validate results */ 
	if(!equality_status) {
		printf("%s::%s... FAILED\n", __FILE__, __FUNCTION__); 
	} else {
		printf("%s::%s... \e[0;32mPASSED\e[0m\n", __FILE__, __FUNCTION__);
	}
}


void test_to_weighted_matrix() {

	/* vertices and equality status */ 
	int vertices = 5;
	int equality_status = TRUE;

	/* expected result after directed matrix conversion */
	int expected_output[5][5] = {
		{-1,1,2,3,-1},
		{1,-1,4,-1,-1},
		{2,4,-1,-1,5},
		{3,-1,-1,-1,-1},
		{-1,-1,5,-1,-1},
	};	

	/* create adj lists */ 
	adj_list_t *g = init_adj_list(vertices, vertices, false);
	mat_graph_t *result = init_matrice_graph(vertices);


	/* build graph */ 
	add_node(g, 0, "A", 1, "B", 1);
	add_node(g, 0, "A", 2, "C", 2); 
	add_node(g, 0, "A", 3, "D", 3); 
	add_node(g, 1, "B", 2, "C", 4);
	add_node(g, 4, "E", 2, "C", 5);


	/* test directed matrix conversion */ 
	mat_graph_t *output = to_matrix(result, g, false);
	int v = output->vertices; 

	/* check output */ 
	for(int i = 0; i < vertices; i++) {
		for(int j = 0; j < vertices; j++) {
			if(output->weights[i*v+j] != expected_output[i][j]) {
				equality_status = FALSE; 
			}
		}
	}

	/* validate results */ 
	if(!equality_status) {
		printf("%s::%s... FAILED\n", __FILE__, __FUNCTION__); 
	} else {
		printf("%s::%s... \e[0;32mPASSED\e[0m\n", __FILE__, __FUNCTION__);
	}
}


void test_to_directed_weighted_matrix() {

	/* vertices and equality status */ 
	int vertices = 8; 
	int equality_status = TRUE;

	/* expected result after directed matrix conversion */
	int expected_output[8][8] = {
		{-1,1,-1,-1,-1,-1,-1,-1},
		{-1,-1,2,-1,-1,-1,-1,-1},
		{-1,-1,-1,3,5,-1,-1,-1},
		{4,-1,-1,-1,-1,-1,-1,-1},
		{-1,-1,-1,-1,-1,6,-1,-1},
		{-1,-1,-1,-1,-1,-1,7,-1},
		{-1,-1,-1,-1,8,-1,-1,9},
		{-1,-1,-1,-1,-1,-1,-1,10}
	};	

	/* test first example of weighted matrix */ 
	adj_list_t *g = init_adj_list(vertices, vertices, true);
	mat_graph_t *result = init_matrice_graph(vertices);

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
	mat_graph_t *output = to_matrix(result, g, true);
	int v = output->vertices; 


	/* check output */ 
	for(int i = 0; i < vertices; i++) {
		for(int j = 0; j < vertices; j++) {
			if(output->weights[i*v+j] != expected_output[i][j]) {
				equality_status = FALSE; 
			}
		}
	}

	/* validate results */ 
	if(!equality_status) {
		printf("%s::%s... FAILED\n", __FILE__, __FUNCTION__); 
	} else {
		printf("%s::%s... \e[0;32mPASSED\e[0m\n", __FILE__, __FUNCTION__);
	}


}

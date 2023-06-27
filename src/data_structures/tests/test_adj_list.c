#include "includes/test_adj_list.h" 

void test_graph() {

	/* test first example of bfs */ 
	adj_list_t *g = init_graph(5, 5, false);
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
		node_t *head = g->items[i]->head; 
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
	} else {
		printf("%s::%s... \e[0;32mPASSED\e[0m\n", __FILE__, __FUNCTION__);
	}

}


void test_weighted_graph() {

	/* test first example of bfs */ 
	adj_list_t *g = init_graph(5, 5, false);
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
		node_t *head = g->items[i]->head; 
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
	} else {
		printf("%s::%s... \e[0;32mPASSED\e[0m\n", __FILE__, __FUNCTION__);
	}
}


void test_transpose_graph() {

	/* test tranpose of adjacency list */
    int vertices = 8; 
	int adj_list_test = TRUE; 

	/* create adjacency list */ 
	adj_list_t *g = init_graph(vertices, vertices, true);
	adj_list_t *result_list = init_graph(vertices, vertices, true); 

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
	adj_list_t *result = transpose_items(g, result_list); 

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
		node_t *head = result->items[i]->head; 
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
	} else {
		printf("%s::%s... \e[0;32mPASSED\e[0m\n", __FILE__, __FUNCTION__);
	}
}


void test_get_node_by_id() {

	/* test tranpose of adjacency list */
    int vertices = 8; 
	bool equality_test = false; 

	/* create adjacency list */ 
	adj_list_t *g = init_graph(vertices, vertices, true);
	adj_list_t *result_list = init_graph(vertices, vertices, true); 

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


	node_t *result = get_node_by_id(g, 0); 

	int label_condition = strcmp(result->label, "A") == 0; 
	if(label_condition && result->id == 0){
		equality_test = true; 
	}


	/* validate results */ 
	if(!equality_test) {
		printf("%s::%s... FAILED\n", __FILE__, __FUNCTION__); 
	} else {
		printf("%s::%s... \e[0;32mPASSED\e[0m\n", __FILE__, __FUNCTION__);
	}

}


void test_resize_adj_list() {


	/* create adjacency list */
	bool equality_status = true; 
	int vertices = 100;  
	adj_list_t *g = init_graph(vertices, vertices, true);
	adj_list_t *result_list = init_graph(vertices, vertices, true); 

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


	if(g->v != 100) {
		equality_status = false; 
	} 
	resize_adj_list(g, 7); 

	if(g->v != 7) {
		equality_status = false; 
	} 


	/* validate results */ 
	if(!equality_status) {
		printf("%s::%s... FAILED\n", __FILE__, __FUNCTION__); 
	} else {
		printf("%s::%s... \e[0;32mPASSED\e[0m\n", __FILE__, __FUNCTION__);
	}

}

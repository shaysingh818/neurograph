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
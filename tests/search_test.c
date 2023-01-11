#include "includes/search_test.h"
#include "../src/includes/graph.h"

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

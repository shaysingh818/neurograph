#include "includes/test_search.h"

void test_bfs_one() {

	int vertices = 5; 	
	int bfs_status = TRUE; 

	char *path = "../../examples/gml/unit_tests/searching/bfs_one.gmul";
	graph_t *g = serialize_graph_list(path, 1024, false);

	/* check queue state against it */ 
	char *order[5] = {"A", "B", "C", "D", "E"}; 
	node_t *head = g->list->items[1]->head;
	queue_t *result = bfs(g, head); 

	/* iterate through queue and confirm order */ 
	for(int i = result->front_index; i <= result->rear_index; i++) {
		int condition = strcmp(result->items[i]->label, order[i]);
		assert(condition == 0); 
	}

	printf("%s::%s... \e[0;32mPASSED\e[0m\n", __FILE__, __FUNCTION__); 
}


void test_bfs_two() {

	int vertices = 5; 
	int bfs_status = TRUE; 

	/* create labeled graph */ 
	char *path = "../../examples/gml/unit_tests/searching/bfs_two.gmul";
	graph_t *g = serialize_graph_list(path, 1024, false);

	/* get head node of graph */
	char *order[5] = {"S", "A", "B", "C", "D"}; 
	node_t *head = g->list->items[1]->head;
	queue_t *result = bfs(g, head); 

	/* iterate through queue and confirm order */ 
	for(int i = result->front_index; i <= result->rear_index; i++) {
		int condition = strcmp(result->items[i]->label, order[i]);
		assert(condition == 0); 
	}

	/* validate results */ 
	if(!bfs_status) {
		printf("%s::%s...  FAILED\n", __FILE__, __FUNCTION__); 
	}
	printf("%s::%s...  \e[0;32mPASSED\e[0m\n", __FILE__, __FUNCTION__); 

}

void test_dfs_one() {

	int vertices = 5; 

	/* test first example of bfs */ 
	char *path = "../../examples/gml/unit_tests/searching/dfs_one.gmul";
	graph_t *g = serialize_graph_list(path, 1024, false);

	/* check queue state against it */ 
	char *order[5] = {"A", "B", "C", "E", "D"}; 
	queue_t *q = init_queue(g->vertices); 	

	/* get head node of graph */ 
	node_t *head = g->list->items[1]->head;

	/* check result of bfs */ 
	int result = dfs(q, g, head); 

	/* iterate through queue and confirm order */ 
	for(int i = q->front_index; i <= q->rear_index; i++) {
		int condition = strcmp(q->items[i]->label, order[i]);
		assert(condition == 0); 
	}

	printf("%s::%s...  \e[0;32mPASSED\e[0m\n", __FILE__, __FUNCTION__); 

}

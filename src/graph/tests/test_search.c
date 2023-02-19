#include "includes/test_search.h"
#include "../../includes/graph.h"

void test_bfs_one() {

	int vertices = 5; 	
	int bfs_status = TRUE; 

	/* test first example of bfs */ 
	graph_t *g = init_graph(vertices, vertices, false);
	add_node(g, 0, "A", 1, "B", 0);
	add_node(g, 0, "A", 2, "C", 0); 
	add_node(g, 0, "A", 3, "D", 0); 
	add_node(g, 1, "B", 2, "C", 0);
	add_node(g, 4, "E", 2, "C", 0);

	/* check queue state against it */ 
	char *order[5] = {"A", "B", "C", "D", "E"}; 
	node_t *head = g->items[1].head;
	queue_t *result = bfs(g, head); 

	/* iterate through queue and confirm order */ 
	for(int i = result->front_index; i <= result->rear_index; i++) {
		int condition = strcmp(result->items[i]->label, order[i]);
		if(condition != 0) {
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

	int vertices = 5; 
	int bfs_status = TRUE; 

	/* create labeled graph */ 
	graph_t *g = init_graph(vertices, vertices, false);
    add_node(g, 0, "S", 1, "A", 0);
    add_node(g, 0, "S", 2, "B", 0);
    add_node(g, 0, "S", 3, "C", 0);
    add_node(g, 1, "A", 4, "D", 0);
    add_node(g, 2, "B", 4, "D", 0);
    add_node(g, 3, "C", 4, "D", 0);

	/* get head node of graph */
	char *order[5] = {"S", "A", "B", "C", "D"}; 
	node_t *head = g->items[1].head;
	queue_t *result = bfs(g, head); 

	/* iterate through queue and confirm order */ 
	for(int i = result->front_index; i <= result->rear_index; i++) {
		int condition = strcmp(result->items[i]->label, order[i]);
		if(condition != 0) {
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

	int vertices = 5; 
	int dfs_status = TRUE; 

	/* test first example of bfs */ 
	graph_t *g = init_graph(vertices, vertices, false); 
	add_node(g, 0, "A", 1, "B", 0); 
	add_node(g, 0, "A", 2, "C", 0); 
	add_node(g, 0, "A", 3, "D", 0); 
	add_node(g, 1, "B", 2, "C", 0);
	add_node(g, 4, "E", 2, "C", 0);

	/* check queue state against it */ 
	char *order[5] = {"A", "B", "C", "E", "D"}; 
	queue_t *q = init_queue(g->v); 	

	/* get head node of graph */ 
	node_t *head = g->items[1].head;

	/* check result of bfs */ 
	int result = dfs(q, g, head); 

	/* iterate through queue and confirm order */ 
	for(int i = q->front_index; i <= q->rear_index; i++) {
		int condition = strcmp(q->items[i]->label, order[i]);
		if(condition != 0) {
			dfs_status = FALSE;
		}
	}

	/* validate results */ 
	if(!dfs_status) {
		printf("%s::%s...  FAILED\n", __FILE__, __FUNCTION__); 
	}
	printf("%s::%s...  \e[0;32mPASSED\e[0m\n", __FILE__, __FUNCTION__); 

}

#include "includes/comp.h"


adjacency_list_t *init_comp_graph() {
    adjacency_list_t *graph = (adjacency_list_t*)malloc(sizeof(adjacency_list_t));
    graph->items = malloc(INITIAL_NODE_SIZE * sizeof(node_obj_list_t*));
    graph->curr_node_count = INITIAL_NODE_SIZE;

	/* allocate variable lists */
	for(int i = 0; i < graph->curr_node_count; i++){
		graph->items[i] = malloc(sizeof(node_obj_list_t));
		graph->items[i]->head = NULL; 
	}

    return graph; 
}

int add_cgraph_node(adjacency_list_t *g, int src_id, int dest_id) {

	if(src_id >= g->curr_node_count || dest_id >= g->curr_node_count) {
		printf("Not enough vertices in graph\n");
		printf("Current amount of vertices: %d\n", g->curr_node_count);
		exit(0); 
	}


	node_t *check = NULL;
	node_t *new_node = init_variable(dest_id, (void*)3);

	printf("Here\n"); 

	/* check if head is null */ 
	if(g->items[src_id]->head == NULL) {
		new_node->next = g->items[src_id]->head; 
		g->items[src_id]->head = new_node;
	} else {
		check = g->items[src_id]->head; 
		while(check->next != NULL){
			check = check->next; 
		}
		check->next = new_node; 
	}


	return TRUE; 
}



void print_comp_graph(adjacency_list_t *g) {
	for(int i = 0; i < g->curr_node_count; i++){
		node_t *head = g->items[i]->head;
		printf("%d ", i);
		while(head) {
			printf("-> (%d)", head->id); 
			head  = head->next; 
		}
		printf("\n"); 
	}
}
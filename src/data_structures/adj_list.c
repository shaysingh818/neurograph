#include "includes/adj_list.h"


adj_list_t *init_graph(int v, int e, bool directed) {

	adj_list_t *list;
	list = (adj_list_t*)malloc(sizeof(adj_list_t)); 
	list->edges = malloc(e * sizeof(edge_t));
   	list->visited = malloc(v * sizeof(int)); 	
	list->items = (node_list_t*)malloc(v * sizeof(node_list_t)); 
	list->directed = directed;
   	list->err = false; 	
	list->v = v;
    list->e = e; 

	/* allocate edges slot */
   	for(int i = 0; i < e; i++){
		list->edges[i] = malloc(sizeof(edge_t)); 
	}	

	/* allocate adjacency list */ 
	for(int n = 0; n < v; n++){
		list->items[n].head = NULL; 
	}
		
	/* add all nodes as unvisited */ 
	for(int n = 0; n < v; n++){
		list->visited[n] = 0; 
	}


	return list; 
}


node_t *get_node_by_id(adj_list_t *g, int search_id){
	for(int i = 0; i < g->v; i++){
		node_t *head = g->items[i].head; 
		while(head) {
			if(head->id == search_id){
				return head; 
			}
			head = head->next; 			
		}
	}
}


adj_list_t *transpose_items(adj_list_t *g, adj_list_t *r) {

	for(int i = 0; i < g->v; i++) {
		node_t *head = g->items[i].head; 
		while(head) {
			
			node_t *src = get_node_by_id(g, head->id); 
			node_t *dst = get_node_by_id(g, i); 

			/* switch direction of graph */ 
			add_node(r, head->id, src->label, i, dst->label, head->weight); 
			head = head->next; 
		}
	}
	return r; 
}


int add_node(
	adj_list_t *g, int src_id, char *src_label, 
	int dest_id, char *dest_label, int weight) {


	node_t *check = NULL; 
	node_t *new_node = create_node(dest_id, dest_label, weight);

	/* check if head is null */ 
	if(g->items[src_id].head == NULL) {
		new_node->next = g->items[src_id].head; 
		g->items[src_id].head = new_node; 
	} else {
		check = g->items[src_id].head; 
		while(check->next != NULL){
			check = check->next; 
		}
		check->next = new_node; 
	}


	if(g->directed == false) {

		/* check if head is NULL again */ 
		new_node = create_node(src_id, src_label, weight); 
		if(g->items[dest_id].head == NULL) {
			new_node->next = g->items[dest_id].head; 
			g->items[dest_id].head = new_node; 
		} else {
			check = g->items[dest_id].head; 
			while(check->next != NULL) {
				check = check->next; 
			}
			check->next = new_node; 
		} 

	}

	return TRUE; 
}


int add_end_node(adj_list_t *g, int src_id, char *src_label, int weight) {
	
	/* only add to selected src node */ 
	node_t *check = NULL; 
	node_t *new_node = create_node(src_id, src_label, weight); 

	/* check if head is null */ 
	if(g->items[src_id].head == NULL) {
		new_node->next = g->items[src_id].head; 
		g->items[src_id].head = new_node; 
	} else {
		check = g->items[src_id].head; 
		while(check->next != NULL){
			check = check->next; 
		}
		check->next = new_node; 
	}

	return TRUE; 
}


void print_graph(adj_list_t *g) {
	for(int i = 0; i < g->v; i++){
		node_t *head = g->items[i].head;
		printf("%d ", i); 
		while(head) {
			printf("-> (%d, %s)", head->id, head->label); 
			if(head->weight >= 0) {
				printf(" [%d] ", head->weight); 
			}
			head  = head->next; 
		}
		printf("\n"); 
	}
}
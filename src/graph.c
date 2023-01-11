#include "includes/graph.h"
#include "includes/queue.h"


graph_t *init_graph(int v, int e) {

	graph_t *g;
	g = (graph_t*)malloc(sizeof(graph_t)); 
	g->edges = malloc(e * sizeof(edge_t));
   	g->visited = malloc(v * sizeof(int)); 	
	g->v = v;
	g->e = e; 

	/* allocate edges slot */
   	for(int i = 0; i < e; i++){
		g->edges[i] = malloc(sizeof(edge_t)); 
	}	
		
	/* add all nodes as unvisited */ 
	for(int n = 0; n < v; n++){
		g->visited[n] = 0; 
	}

	return g; 
}


adj_list_t *init_adj_list(int v) {

	adj_list_t *a;
	a = (adj_list_t*)malloc(sizeof(adj_list_t)); 
	a->items = (node_list_t*)malloc(v * sizeof(node_list_t));
   	a->visited = malloc(v * sizeof(int));
	a->v = v;

	/* allocate adjacency list as empty */ 
	for(int i = 0; i < v; i++) {
		a->items[i].head = NULL; 	
	}

	/* add all nodes as unvisited */ 
	for(int n = 0; n < v; n++){
		a->visited[n] = 0; 
	}

	return a; 

}


w_adj_list_t *init_w_adj_list(int v) {

	w_adj_list_t *a;
	a = (w_adj_list_t*)malloc(sizeof(w_adj_list_t)); 
	a->items = (w_node_list_t*)malloc(v * sizeof(w_node_list_t));
   	a->visited = malloc(v * sizeof(int));
	a->v = v;

	/* allocate adjacency list as empty */ 
	for(int i = 0; i < v; i++) {
		a->items[i].head = NULL; 	
	}

	/* add all nodes as unvisited */ 
	for(int n = 0; n < v; n++){
		a->visited[n] = 0; 
	}

	return a; 
}


walk_t *init_walk(int steps) {
	walk_t *w;
	w = (walk_t*)malloc(sizeof(walk_t));
   	w->path = malloc(steps * sizeof(int));
   	w->steps = steps; 	
	w->cycles = 0; 
	w->weighted_sum = 0; 
	return w; 
}


adj_list_t *transpose_adj(adj_list_t *a, adj_list_t *r) {

	char label_list[8] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H'}; 	
	for(int i = 0; i < a->v; i++) {
		node_t *head = a->items[i].head; 
		while(head) {
			
			/* grab corresponding labels */ 
			char src_label = label_list[head->id]; 
			char dest_label = label_list[i]; 

			/* switch direction of graph */ 
			add_directed_edge(r, head->id, src_label, i, dest_label); 
			head = head->next; 
		}
	}

	return r; 
}


void print_adj_list(adj_list_t *a) {
	for(int i = 0; i < a->v; i++){
		node_t *head = a->items[i].head;
		printf("%d ", i); 
		while(head) {
			printf("-> (%d, %c)", head->id, head->label); 
			head  = head->next; 
		}
		printf("\n"); 
	}
}


void print_w_adj_list(w_adj_list_t *a) {
	for(int i = 0; i < a->v; i++){
		w_node_t *head = a->items[i].head;
		printf("%d ", i); 
		while(head) {
			printf("-> (%d, %c) [%d]", head->id, head->label, head->weight); 
			head  = head->next; 
		}
		printf("\n"); 
	}
}


int add_edge(
	adj_list_t *a, 
	int src_id, char src_label, 
	int dest_id, char dest_label) {

	node_t *check = NULL; 
	node_t *new_node = create_node(dest_id, dest_label); 

	/* check if head is null */ 
	if(a->items[src_id].head == NULL) {
		new_node->next = a->items[src_id].head; 
		a->items[src_id].head = new_node; 
	} else {
		check = a->items[src_id].head; 
		while(check->next != NULL){
			check = check->next; 
		}
		check->next = new_node; 
	}

	/* check if head is NULL again */ 
	new_node = create_node(src_id, src_label); 
	if(a->items[dest_id].head == NULL) {
		new_node->next = a->items[dest_id].head; 
		a->items[dest_id].head = new_node; 
	} else {
		check = a->items[dest_id].head; 
		while(check->next != NULL) {
			check = check->next; 
		}
		check->next = new_node; 
	} 

	return TRUE; 

}


int add_directed_edge(
	adj_list_t * a, 
	int src_id, char src_label, 
	int dest_id, char dest_label) {


	/* only add to selected src node */ 
	node_t *check = NULL; 
	node_t *new_node = create_node(dest_id, dest_label); 

	/* check if head is null */ 
	if(a->items[src_id].head == NULL) {
		new_node->next = a->items[src_id].head; 
		a->items[src_id].head = new_node; 
	} else {
		check = a->items[src_id].head; 
		while(check->next != NULL){
			check = check->next; 
		}
		check->next = new_node; 
	}

	return TRUE; 
}

int add_end_node(adj_list_t *a, int src_id, char src_label) {
	
	/* only add to selected src node */ 
	node_t *check = NULL; 
	node_t *new_node = create_node(src_id, src_label); 

	/* check if head is null */ 
	if(a->items[src_id].head == NULL) {
		new_node->next = a->items[src_id].head; 
		a->items[src_id].head = new_node; 
	} else {
		check = a->items[src_id].head; 
		while(check->next != NULL){
			check = check->next; 
		}
		check->next = new_node; 
	}

	return TRUE; 
}


int add_w_edge(
	w_adj_list_t *a, 
	int src, char src_label, 
	int dest, char dest_label, 
	int weight) {

	/* create destination node */ 
	w_node_t *check = NULL; 
	w_node_t *new_node = create_weighted_node(
		dest, weight, dest_label
	);

	/* check if head is null */ 
	if(a->items[src].head == NULL) {
		new_node->next = a->items[src].head; 
		a->items[src].head = new_node; 
	} else {
		check = a->items[src].head; 
		while(check->next != NULL){
			check = check->next; 
		}
		check->next = new_node; 
	}

	/* create src node */ 
	new_node = create_weighted_node(
		src, weight, src_label
	);

	/* check if head is NULL again */ 
	if(a->items[dest].head == NULL) {
		new_node->next = a->items[dest].head; 
		a->items[dest].head = new_node; 
	} else {
		check = a->items[dest].head; 
		while(check->next != NULL) {
			check = check->next; 
		}
		check->next = new_node; 
	} 

	return TRUE; 

}
#include "includes/graph.h"
#include "../queue/includes/queue.h"



graph_t *init_graph(int v, int e, bool directed) {

	graph_t *g;
	g = (graph_t*)malloc(sizeof(graph_t)); 
	g->edges = malloc(e * sizeof(edge_t));
   	g->visited = malloc(v * sizeof(int)); 	
	g->items = (node_list_t*)malloc(v * sizeof(node_list_t)); 
	g->directed = directed;
   	g->err = false; 	
	g->v = v;
	g->e = e; 

	/* allocate edges slot */
   	for(int i = 0; i < e; i++){
		g->edges[i] = malloc(sizeof(edge_t)); 
	}	

	/* allocate adjacency list */ 
	for(int n = 0; n < v; n++){
		g->items[n].head = NULL; 
	}
		
	/* add all nodes as unvisited */ 
	for(int n = 0; n < v; n++){
		g->visited[n] = 0; 
	}

	return g; 
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


graph_t *transpose_items(graph_t *g, graph_t *r) {

	char *label_list[8] = {"A", "B", "C", "D", "E", "F", "G", "H"}; 	
	for(int i = 0; i < g->v; i++) {
		node_t *head = g->items[i].head; 
		while(head) {
			
			/* grab corresponding labels */ 
			char *src_label = label_list[head->id]; 
			char *dest_label = label_list[i]; 

			/* switch direction of graph */ 
			add_node(r, head->id, src_label, i, dest_label, head->weight); 
			head = head->next; 
		}
	}
	return r; 
}


mat_t *to_matrix(mat_t *m, graph_t *g, bool directed) {
	
	/* iterate through list and populate matrix */
	for(int i = 0; i < g->v; i++) {

		node_t *head = g->items[i].head;
		node_t *src_node = get_node_by_id(g, i); 

		while(head) {

			entry_t *src = init_entry(src_node->id, src_node->label); 
			entry_t *dst = init_entry(head->id, head->label); 

			if(directed) {
				insert(m, src, dst, head->weight, true); 
			} else {
				insert(m, src, dst, head->weight, false); 
			}

			head  = head->next;
		}
	}
	return m; 
}


graph_t *to_list(graph_t *g, mat_t *m, bool directed) {

	/* unique labels for each node */ 	
	char *label_list[8] = {"A", "B", "C", "D", "E", "F", "G", "H"}; 

	for(int i = 0; i < m->vertices; i++) {
		for(int j = 0; j < m->vertices; j++) {
			if(m->matrix[i*m->vertices+j]->label != NULL) {
				int weight_value = m->weights[i*m->vertices+j]; 
				add_node(g, i, label_list[i], j, label_list[j], weight_value);
			}
		}
	}

	return g; 
}


int add_node(
	graph_t *g, int src_id, char *src_label, 
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


int add_end_node(graph_t *g, int src_id, char *src_label, int weight) {
	
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


node_t *get_node_by_id(graph_t *g, int search_id){
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


void print_graph(graph_t *g) {
	for(int i = 0; i < g->v; i++){
		node_t *head = g->items[i].head;
		printf("%d ", i); 
		while(head) {
			printf("-> (%d, %s)", head->id, head->label); 
			if(head->weight > 0) {
				printf(" [%d] ", head->weight); 
			}
			head  = head->next; 
		}
		printf("\n"); 
	}
}

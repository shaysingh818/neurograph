#include "includes/search.h"

queue_t *bfs(graph_t *g, node_t *root) {	

	/* create array to return list of nodes visited */ 
	int *nodes = malloc(g->vertices * sizeof(int));
	int current_index = 0; 

	/* create queue */ 
	queue_t *q = init_queue(g->vertices);
   	queue_t *visit = init_queue(g->vertices); 	
   	g->visited[root->id] = 1; 

	item_t *item = init_item(root->id, root->label, 0, root); 
	push(q, item); 	

	while(!is_empty(q)) {

		/* get current item in queue */ 
		int current_vertex = front(q);
		node_t *temp = g->list->items[current_vertex]->head; 

		/* pop element from queue and add to visited */ 
		push(visit, q->items[q->front_index]); 
		pop(q);	

		/* add non visited adjacent nodes to queue */ 	
		while(temp) {
			int adj_vertex = temp->id; 
			if(g->visited[adj_vertex] == 0){

				g->visited[adj_vertex] = 1; 
				item_t *temp_item = init_item(temp->id,temp->label, 0, temp);
				push(q, temp_item); 
			}
			temp  = temp->next; 
		}
	}	

	return visit; 
}


int dfs(queue_t *q, graph_t *g, node_t *root) {

	node_t *adj_list = g->list->items[root->id]->head; 
	node_t *temp = adj_list;
   	g->visited[root->id] = 1;

	item_t *item = init_item(root->id, root->label, 0, root); 
	push(q, item); 

	while(temp != NULL) {
		int connected_vertex = temp->id; 
		if(g->visited[connected_vertex] == 0){
			dfs(q, g, temp); 
		}
		temp = temp->next; 
	}

	return TRUE; 
}


int k_dfs(queue_t *q, graph_t *g, node_t *root) {

	/* grab the ID of the head node */ 
	node_t *temp = g->list->items[root->id]->head; 
   	g->visited[root->id] = 1;

	item_t *item = init_item(root->id, root->label, 0, root); 
	push(q, item); 

	while(temp != NULL) {
		int connected_vertex = temp->id; 
		if(g->visited[connected_vertex] == 0){
			k_dfs(q, g, temp); 
		}
		temp = temp->next; 
	}

	return TRUE; 
}

#include "includes/path.h"


int *bellman_ford_list(graph_t *g, node_t *root, int *dist) {

	/* grab src node, vertices and edges */ 
	int v = g->vertices; 
	int e = g->edges; 
	int src = root->id; 

	/* init distances from source to all other vertices */ 
	for(int i = 0; i < v; i++) {
		dist[i] = INT_MAX; 
	}
	dist[src] = 0; 

	/* relax all edges */ 
	for(int i = 1; i <= v - 1; i++){
		for(int j = 0; j < e; j++){
			int u = g->list->edges[j]->src->id;
			int v = g->list->edges[j]->dest->id; 
			int weight = g->list->edges[j]->weight;
			if(dist[u] != INT_MAX && dist[u] + weight < dist[v]) {
				dist[v] = dist[u] + weight; 
			}
		}
	}

	/* check for negative weight cycles */ 
	for(int i = 0; i < e; i++){
		int u = g->list->edges[i]->src->id;
		int v = g->list->edges[i]->dest->id; 
		int weight = g->list->edges[i]->weight;
		if(dist[u] != INT_MAX && dist[u] + weight < dist[v]) {
			printf("Graph contains negative weight cycle\n");
		   	return FALSE; 	
		}
	}

	return dist; 
}




int *dijkstra_list(graph_t *g, int start_vertex) {
	
	/* start and current node */ 
	node_t *start = g->list->items[start_vertex]->head;
	int *dist = malloc(g->vertices * sizeof(int));
	int *prev = malloc(g->vertices * sizeof(int)); 
	int *s = malloc(g->vertices * sizeof(int)); 

	/* create queue using int values */ 
	queue_t *q = init_queue(g->vertices); 

	for(int i = 0; i < g->vertices; i++) {
	   	if(i != start_vertex) {
			dist[i] = INT_MAX; 
			prev[i] = INT_MIN; 	
		}
	}

	/* push start vertex to front of queue */
	item_t *start_item = init_item(start_vertex, start->label, 0, start); 
	push(q, start_item); 
	dist[start_vertex] = 0; 

	while(!is_empty(q)) {

		/* get minimum distance */
		int u = q->items[q->front_index]->integer; 
		pop(q);  

		node_t *head = g->list->items[u]->head; 
		while(head) {

			if(dist[head->id] > dist[u] + head->weight) {
				dist[head->id] = dist[u] + head->weight;
				prev[head->id] = u; 
				item_t *temp = init_item(head->id, head->label, 0, head); 
				push(q, temp); 
			}
			head = head->next; 
		}
	}

	return dist; 
}	


int shortest_path_list(graph_t *g, int start_vertex, int end_vertex) {

	/* start and current node */ 
	node_t *start = g->list->items[start_vertex]->head;
	int *dist = malloc(g->vertices * sizeof(int));
	int *prev = malloc(g->vertices * sizeof(int)); 
	int *s = malloc(g->vertices * sizeof(int)); 

	/* create queue using int values */ 
	queue_t *q = init_queue(g->vertices); 

	for(int i = 0; i < g->vertices; i++) {
	   	if(i != start_vertex) {
			dist[i] = INT_MAX; 
			prev[i] = INT_MIN; 	
		}
	}

	/* push start vertex to front of queue */
	item_t *start_item = init_item(start_vertex, start->label, 0, start); 
	push(q, start_item); 
	dist[start_vertex] = 0; 

	while(!is_empty(q)) {

		/* get minimum distance */
		int u = q->items[q->front_index]->integer; 
		pop(q);  

		node_t *head = g->list->items[u]->head; 
		while(head) {

			int x = dist[u] + head->weight; 
			if(dist[head->id] > dist[u] + head->weight) {
				/* otherwise keep looking */
				dist[head->id] = dist[u] + head->weight;
				prev[head->id] = u; 
				item_t *temp = init_item(head->id, head->label, 0, head); 
				push(q, temp); 
			}

			head = head->next; 
		}

	}

	if(dist[end_vertex] != INT_MAX){
		return dist[end_vertex]; 
	}
	/* in this case, there is no shortest path  */
	return 0; 
} 


walk_t *random_walk_list(graph_t *g, int start_vertex, int steps) {

	/* variables */ 	
	int v = g->vertices;
   	time_t t; 	

	/* create walk structure */
	walk_t *walk = init_walk(steps); 	 

	/* start with the src node */
	node_t *start = g->list->items[start_vertex]->head;

	/* init random seed */ 
	srand((unsigned) time(&t));

	/* walk through graph for n steps */ 
	for(int n = 0; n < steps; n++) {
	
		/* keep track of neighbors */ 
		int neighbors[v];
		int counter = 0;

		/* get starting nodes neighbors */ 
		while(start) {
			neighbors[counter] = start->id; 
			start  = start->next; 
			counter += 1; 
		}

		/* select random neighbor that hasn't been visited */ 
		int rand_index = rand() % counter; 
		int selected_neighbor = neighbors[rand_index]; 

		/* set as new starting node and add visited node to path */ 
		start = g->list->items[selected_neighbor]->head;
		walk->path[n] = selected_neighbor; 
	}	
	
	return walk; 
}


walk_t *weighted_random_walk_list(graph_t *g, walk_t *w, int start_vertex) {
		
	/* variables */ 	
	int v = g->vertices;
   	time_t t; 

	/* start with the src node */
	node_t *start = g->list->items[start_vertex]->head;

	/* init random seed */ 
	srand((unsigned) time(&t));

	/* walk through graph for n steps */ 
	for(int n = 0; n < w->steps; n++) {
	
		/* keep track of neighbors */ 
		int neighbors[v];
		int counter = 0;

		/* get starting nodes neighbors */ 
		while(start) {
			neighbors[counter] = start->id;
			start  = start->next; 
			counter += 1; 
		}

		/* select random neighbor that hasn't been visited */ 
		int rand_index = rand() % counter; 
		int selected_neighbor = neighbors[rand_index]; 

		/* set as new starting node and add visited node to path */ 
		start = g->list->items[selected_neighbor]->head;
		w->weighted_sum += start->weight;
		w->path[n] = selected_neighbor; 
	}	

	return w; 	
}


walk_t *random_walk_mat(graph_t *m, int start_vertex, int steps) {

	/* init random seed */
   	time_t t; 	
	srand((unsigned) time(&t));
	int start = start_vertex;

	/* create walk structure */
	walk_t *walk = init_walk(steps); 	 

	for(int n = 0; n < steps; n++){

		int counter = 0;
		int neighbors[m->vertices];

		for(int j = 0; j < m->vertices; j++) {
			int id = m->matrix->matrix[start*m->vertices+j]->id; 
			if(id >= 0) {
				neighbors[counter] = id; 
				counter += 1; 
			}
		}

		int rand_index = rand() % counter; 
		int selected_neighbor = neighbors[rand_index]; 
		int weight = m->matrix->weights[start*m->vertices+selected_neighbor];

		start = selected_neighbor;
		walk->weighted_sum += weight; 
		walk->path[n] = selected_neighbor; 
	}

	return walk; 
}


int *dijkstra_mat(graph_t *m, int start_vertex) {

	int *dist = malloc(m->vertices * sizeof(int));
	int *prev = malloc(m->vertices * sizeof(int)); 
	queue_t *q = init_queue(m->vertices); 

	for(int i = 0; i < m->vertices; i++) {
		if(i != start_vertex) {
			dist[i] = INT_MAX; 
			prev[i] = INT_MIN; 
		}
	}

	/* push start vertex to front of queue */
	entry_t *start = search_entry_by_id(m->matrix, start_vertex);
	item_t *start_item = init_item(start->id, start->label, 0, NULL); 
	push(q, start_item); 	
	dist[start_vertex] = 0; 

	while(!is_empty(q)) {

		/* get minimum distance */
		int u = q->items[q->front_index]->integer;
		pop(q); 

		/* get neighbors */
		for(int n = 0; n < m->vertices; n++){

			int id = m->matrix->matrix[start_vertex*m->vertices+n]->id; 
			int weight = m->matrix->weights[start_vertex*m->vertices+n]; 
			char *label = m->matrix->matrix[start_vertex*m->vertices+n]->label; 

			if(id >= 0) {
				if(dist[id] > dist[u] + weight) {
					dist[id] = dist[u] + weight;
					prev[id] = u; 
					item_t *temp = init_item(id, label, 0, NULL); 
					push(q, temp);
				}
				start_vertex = u; 
			}
		}
	}

	return dist;  	
}



int shortest_path_mat(graph_t *m, int start_vertex, int end_vertex) {

	/* 
		This method should be refactored. It does the same
		logic as the Dijkstra code. Only difference is 
		parameters and what it returns. 
	*/

	int *dist = malloc(m->vertices * sizeof(int));
	int *prev = malloc(m->vertices * sizeof(int)); 
	queue_t *q = init_queue(m->vertices); 

	for(int i = 0; i < m->vertices; i++) {
		if(i != start_vertex) {
			dist[i] = INT_MAX; 
			prev[i] = INT_MIN; 
		}
	}

	/* push start vertex to front of queue */
	entry_t *start = search_entry_by_id(m->matrix, start_vertex);
	item_t *start_item = init_item(start->id, start->label, 0, NULL); 
	push(q, start_item); 	
	dist[start_vertex] = 0;


	while(!is_empty(q)) {

		/* get minimum distance */
		int u = q->items[q->front_index]->integer;
		pop(q); 

		/* get neighbors */
		for(int n = 0; n < m->vertices; n++){

			int id = m->matrix->matrix[start_vertex*m->vertices+n]->id; 
			int weight = m->matrix->weights[start_vertex*m->vertices+n]; 
			char *label = m->matrix->matrix[start_vertex*m->vertices+n]->label; 

			if(id >= 0) {
				if(dist[id] > dist[u] + weight) {
					dist[id] = dist[u] + weight;
					prev[id] = u; 
					item_t *temp = init_item(id, label, 0, NULL); 
					push(q, temp);
				}
				start_vertex = u; 
			}
		}
	}

	if(dist[end_vertex] != INT_MAX){
		return dist[end_vertex]; 
	}

	return 0; 
} 

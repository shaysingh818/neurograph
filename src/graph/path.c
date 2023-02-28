#include "includes/path.h"


int *bellman_ford(graph_t *g, node_t *root, int *dist) {

	/* grab src node, vertices and edges */ 
	int v = g->v; 
	int e = g->e; 
	int src = root->id; 

	/* init distances from source to all other vertices */ 
	for(int i = 0; i < v; i++) {
		dist[i] = INT_MAX; 
	}
	dist[src] = 0; 

	/* relax all edges */ 
	for(int i = 1; i <= v - 1; i++){
		for(int j = 0; j < e; j++){
			int u = g->edges[j]->src->id;
			int v = g->edges[j]->dest->id; 
			int weight = g->edges[j]->weight;
			if(dist[u] != INT_MAX && dist[u] + weight < dist[v]) {
				dist[v] = dist[u] + weight; 
			}
		}
	}

	/* check for negative weight cycles */ 
	for(int i = 0; i < e; i++){
		int u = g->edges[i]->src->id;
		int v = g->edges[i]->dest->id; 
		int weight = g->edges[i]->weight;
		if(dist[u] != INT_MAX && dist[u] + weight < dist[v]) {
			printf("Graph contains negative weight cycle\n");
		   	return FALSE; 	
		}
	}

	return dist; 
}




int *dijkstra(graph_t *g, int start_vertex) {
	
	/* start and current node */ 
	node_t *start = g->items[start_vertex].head;
	int *dist = malloc(g->v * sizeof(int));
	int *prev = malloc(g->v * sizeof(int)); 
	int *s = malloc(g->v * sizeof(int)); 

	/* create queue using int values */ 
	queue_t *q = init_queue(g->v); 

	for(int i = 0; i < g->v; i++) {
	   	if(i != start_vertex) {
			dist[i] = INT_MAX; 
			prev[i] = NULL; 	
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

		node_t *head = g->items[u].head; 
		while(head) {

			int x = dist[u] + head->weight; 
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


int *random_walk(graph_t *g, int start_vertex, int steps, int *path) {

	/* variables */ 	
	int v = g->v;
   	time_t t; 	

	/* start with the src node */
	node_t *start = g->items[start_vertex].head;

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
		start = g->items[selected_neighbor].head;
		path[n] = selected_neighbor; 
	}	
	
	return path; 
}


walk_t *weighted_random_walk(graph_t *g, walk_t *w, int start_vertex) {
		
	/* variables */ 	
	int v = g->v;
   	time_t t; 	

	/* start with the src node */
	node_t *start = g->items[start_vertex].head;

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
		start = g->items[selected_neighbor].head;
		w->weighted_sum += start->weight;
		w->path[n] = selected_neighbor; 
	}	

	return w; 	
}

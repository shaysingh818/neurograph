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



queue_t *bfs(adj_list_t *a, node_t *root) {	

	/* create array to return list of nodes visited */ 
	int *nodes = malloc(a->v * sizeof(int));
	int current_index = 0; 

	/* create queue */ 
	queue_t *q = init_queue(a->v);
   	queue_t *visit = init_queue(a->v); 	
   	a->visited[root->id] = 1; 
	push(q, root); 	

	while(!is_empty(q)) {

		/* get current item in queue */ 
		int current_vertex = front(q);
		node_t *temp = a->items[current_vertex].head; 

		/* pop element from queue and add to visited */ 
		push(visit, q->items[q->front_index]); 
		pop(q);	

		/* add non visited adjacent nodes to queue */ 	
		while(temp) {
			int adj_vertex = temp->id; 
			if(a->visited[adj_vertex] == 0){
				a->visited[adj_vertex] = 1; 
				push(q, temp); 
			}
			temp  = temp->next; 
		}
	}	

	return visit; 
}


int dfs(queue_t *q, adj_list_t *a, node_t *root) {

	node_t *adj_list = a->items[root->id].head; 
	node_t *temp = adj_list;
   	a->visited[root->id] = 1;
	push(q, root); 

	while(temp != NULL) {
		int connected_vertex = temp->id; 
		if(a->visited[connected_vertex] == 0){
			dfs(q, a, temp); 
		}
		temp = temp->next; 
	}

	return TRUE; 
}



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


int *random_walk(adj_list_t *a, int start_vertex, int steps, int *path) {

	/* variables */ 	
	int v = a->v;
   	time_t t; 	

	/* start with the src node */
	node_t *start = a->items[start_vertex].head;

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
		start = a->items[selected_neighbor].head;
		path[n] = selected_neighbor; 
	}	
	
	return path; 
}


walk_t *weighted_random_walk(w_adj_list_t *a, walk_t *w, int start_vertex) {
		
	/* variables */ 	
	int v = a->v;
   	time_t t; 	

	/* start with the src node */
	w_node_t *start = a->items[start_vertex].head;

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
		start = a->items[selected_neighbor].head;
		w->weighted_sum += start->weight;
		w->path[n] = selected_neighbor; 
	}	

	return w; 	
}


int degree_centrality(graph_t *g, node_t *root) {

	/* online implementations are vague */ 
	/* for now use best attempt to get the most popular node */ 

	int v = g->v;
	int e = g->e; 
	int max_count = 0;
   	int max_vertex = 0; 	

	/* go through all vertices */ 
	for(int i = 0; i < v; i++){
		int current_edge_count = 0; 
		for(int j = 0; j < e; j++){
			int u = g->edges[j]->src->id; 
			int v = g->edges[j]->dest->id; 
			int weight = g->edges[j]->weight;
		   	if(u == i) {
				current_edge_count += 1; 
			}	
		}

		/* check for edge with the most connections */ 
		if(current_edge_count > max_count) {
			max_count = current_edge_count; 
			max_vertex = i; 
		}

	}

	return max_vertex; 
}



int weighted_degree_centrality(w_adj_list_t *a) {

	/* variables */ 	
	int v = a->v;
	int max_score = 0; 
	int max_vertex = 0; 

	/* traverse adjacency list */ 
	for(int i = 0; i < a->v; i++){

		/* variables to keep track of most popular node */ 
		int weighted_sum = 0;
	   	int connection_count = 0; 

		/* get current head node */ 	
		w_node_t *head = a->items[i].head;

		while(head) {
			weighted_sum += head->weight; 
			connection_count += 1; 
			head  = head->next; 
		}

		/* score highest connected nodes */ 
		int score = connection_count + weighted_sum;

		/* get max score */ 
		if(score > max_score) {
			max_score = score; 
			max_vertex = i; 
		}
	}

	return max_vertex;
}


int scc_fill_order(queue_t *q, adj_list_t *a, node_t *root) {

	/* grab the ID of the head node */ 
	node_t *adj_list = a->items[root->id].head; 
	node_t *temp = adj_list;
   	a->visited[root->id] = 1;

	while(temp != NULL) {
		int connected_vertex = temp->id; 
		if(a->visited[connected_vertex] == 0){
			scc_fill_order(q, a, temp); 
		}
		temp = temp->next; 
	}

	push(q, temp); 
	return TRUE; 
}


int scc(adj_list_t *a, int start_vertex) {

	/* variables */ 	
	int v = a->v;

	return TRUE; 
}


#include "includes/community.h"


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



int weighted_degree_centrality(graph_t *g) {

	/* variables */ 	
	int v = g->v;
	int max_score = 0; 
	int max_vertex = 0; 

	/* traverse adjacency list */ 
	for(int i = 0; i < g->v; i++){

		/* variables to keep track of most popular node */ 
		int weighted_sum = 0;
	   	int connection_count = 0; 

		/* get current head node */ 	
		node_t *head = g->items[i].head;

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


int **kosaraju(graph_t *g, int start_vertex) {

	/* variables */ 	
	int v = g->v;
	queue_t *q = init_queue(g->v);
	queue_t *q1 = init_queue(g->v);
	graph_t *r = init_graph(g->v, g->v, true);
   	int num_components = 0; 	

	/* perform DFS on first instance of graph */ 
	node_t *head = g->items[3].head;
	int result = dfs(q, g, head); 

	/* transposed graph */
	graph_t *transpose = transpose_items(g, r); 

	/* perform DFS on transposed graph */
	node_t *t_head = g->items[6].head;
	item_t *queue_item = init_item(head->id, head->label, 0, head); 
	push(q1, queue_item); //push head node before
	int transpose_result = dfs(q1, transpose, t_head); 

	/* mark all as unvisited */ 
	for(int i = 0; i < g->v; i++){
		transpose->visited[i] = 0; 
	}

	/* allocate space for final results */ 
	int **communities = malloc(sizeof(int*)*g->v);  
	for(int i = 0; i < g->v; i++) {
		communities[i] = malloc(sizeof(int)*g->v); 
	}

	/* pop stack and find components */ 
   	while(!is_empty(q)) {
		item_t *item = q->items[q->front_index]; 
		pop(q);
	   	if(!transpose->visited[item->node->id]) {
			queue_t *q2 = init_queue(g->v);
			int transpose_result = k_dfs(q2, transpose, item->node);

			/* get results from queue */ 
			for(int i = q2->front_index; i <= q2->rear_index; i++) {
				communities[num_components][i] = q2->items[i]->node->id;
			}
			num_components += 1; 
		}	
	}
	
	return communities; 
}


int closeness_centrality(graph_t *g, node_t *root){

	/* sum of all distances to other nodes */ 
	/* based on calculating shortest paths between all pairs of nodes */ 

	/* traverse adjacency list */ 
	for(int i = 0; i < g->v; i++){

		/* get distance of current node and all other nodes */
		int dist = 0; 

	}

	return 0; 

	

	
} 


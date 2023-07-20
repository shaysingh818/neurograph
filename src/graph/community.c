
#include "includes/community.h"


int degree_centrality_list(graph_t *g, node_t *root) {

	/* online implementations are vague */ 
	/* for now use best attempt to get the most popular node */ 

	int v = g->vertices;
	int e = g->edges; 
	int max_count = 0;
   	int max_vertex = 0; 	

	/* go through all vertices */ 
	for(int i = 0; i < v; i++){
		int current_edge_count = 0; 
		for(int j = 0; j < e; j++){
			int u = g->list->edges[j]->src->id; 
			int v = g->list->edges[j]->dest->id; 
			int weight = g->list->edges[j]->weight;
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



int weighted_degree_centrality_list(graph_t *g) {

	/* variables */ 	
	int v = g->vertices;
	int max_score = 0; 
	int max_vertex = 0; 

	/* traverse adjacency list */ 
	for(int i = 0; i < g->vertices; i++){

		/* variables to keep track of most popular node */ 
		int weighted_sum = 0;
	   	int connection_count = 0; 

		/* get current head node */ 	
		node_t *head = g->list->items[i]->head;

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


float closeness_centrality_list(graph_t *g, int vertex){

	int sum = 0; 
	/* traverse adjacency list */ 
	for(int i = 0; i < g->vertices; i++){
		int dist = shortest_path_list(g, vertex, i);
		sum += dist;  
	}

	return (float)1 / (float)sum; 
	
}

float normalized_closeness_centrality_list(graph_t *g, int vertex){

	int sum = 0; 
	/* traverse adjacency list */ 
	for(int i = 0; i < g->vertices; i++){
		int dist = shortest_path_list(g, vertex, i);
		sum += dist;  
	}

	int n = g->vertices - 1; 
	return (float)n / (float)sum; 
}  


int **kosaraju_list(graph_t *g, int start_vertex) {

	/* variables */ 	
	int v = g->vertices;
	queue_t *q = init_queue(g->vertices);
	queue_t *q1 = init_queue(g->vertices);
	graph_t *r = init_graph(g->vertices, g->vertices, true);
   	int num_components = 0; 	

	/* perform DFS on first instance of graph */ 
	node_t *head = g->list->items[3]->head;
	int result = dfs(q, g, head); 

	/* transposed graph */
	graph_t *transposed = init_graph(g->vertices, g->vertices, true);  
	transposed->list = transpose_items(g->list, r->list); 

	/* perform DFS on transposed graph */
	node_t *t_head = g->list->items[6]->head;
	item_t *queue_item = init_item(head->id, head->label, 0, head); 
	push(q1, queue_item); //push head node before
	int transpose_result = dfs(q1, transposed, t_head); 

	/* mark all as unvisited */ 
	for(int i = 0; i < g->vertices; i++){
		transposed->visited[i] = 0; 
	}

	/* allocate space for final results */ 
	int **communities = malloc(sizeof(int*)*g->vertices);  
	for(int i = 0; i < g->vertices; i++) {
		communities[i] = malloc(sizeof(int)*g->vertices); 
	}

	/* pop stack and find components */ 
   	while(!is_empty(q)) {
		item_t *item = q->items[q->front_index]; 
		pop(q);
	   	if(!transposed->visited[item->node->id]) {
			queue_t *q2 = init_queue(g->vertices);
			int transpose_result = k_dfs(q2, transposed, item->node);

			/* get results from queue */ 
			for(int i = q2->front_index; i <= q2->rear_index; i++) {
				communities[num_components][i] = q2->items[i]->node->id;
			}
			num_components += 1; 
		}	
	}
	
	return communities; 
}


int *label_propagator_list(graph_t *g, int *labels, int start_vertex) {

	node_t *start_node = g->list->items[start_vertex]->head; 
	bool labeled = false; 
	int path[10]; 

	/* create array to return list of nodes visited */ 
	queue_t *q = init_queue(g->vertices);
	int result = dfs(q, g, start_node); 
	int curr_label = -1; 

	/* allocate predicted labels for results */
	int *predicted_labels = malloc(g->vertices * sizeof(int)); 
	for(int i = 0; i < g->vertices; i++){
		predicted_labels[i] = -1; 
	}

	/* get items from queue and calculate probabilities */
	for(int i = q->front_index; i <= q->rear_index; i++) {

		node_t *value = g->list->items[q->items[i]->integer]->head;
		int neighbor_counter = 0; 

		while(value) {

			if(labels[value->id] >= 0) {
				curr_label = labels[value->id]; 
			}
			value = value->next;
			neighbor_counter += 1;  
		}

		double delta = 1.00/neighbor_counter;
		if(delta == 0.50) {
			curr_label = -1; 
		}

		int node_index = q->items[i]->integer; 
		predicted_labels[node_index] = curr_label; 		
	}


	return predicted_labels; 
} 


int triangle_count_list(graph_t *g, int vertex) {


	/* perform a depth first search three times */
	queue_t *q = init_queue(g->vertices);
	node_t *start_node = g->list->items[vertex]->head;
	set_t *s = init_set(true);  
	int result = dfs(q, g, start_node);
	int triangle_count = 0; 


	/* iterate through search results */
	for(int i = q->front_index; i <= q->rear_index; i++) {

		int index = q->items[i]->integer; 
		node_t *temp = g->list->items[index]->head; 
		while(temp){	
			node_t *temp2 = g->list->items[temp->id]->head;
			while(temp2) {
				node_t *temp3 = g->list->items[temp2->id]->head;
				while(temp3){
					if(temp3->id == index){
						insert_sorted(s, temp->id, NULL, 0); 
						insert_sorted(s, temp2->id, NULL, 0); 
						insert_sorted(s, temp3->id, NULL, 0);
					}
					temp3 = temp3->next; 
				}
				temp2 = temp2->next;
			}
			temp = temp->next;
		}
	}


	/* store set results in queue */
    s->queue = init_queue(s->count); 
    get_items_sorted(s->root, s->queue);
	int node_count = s->queue->item_count; 
	if(node_count % 2 == 0){
		triangle_count = node_count / 2; 
	} else if (node_count % 3 == 0 || node_count == 3){
		triangle_count = node_count / 3;
	}


	return triangle_count; 
} 


int *degree_centrality_mat(graph_t *g) {

	/* allocate array for result of nodes */
	int *results = malloc(g->vertices * sizeof(int)); 

	for(int i = 0; i < g->vertices; i++){
		int count = 0; 
		for(int j = 0; j < g->vertices; j++){
			int id = g->matrix->matrix[i*g->vertices+j]->id;
			if(id >= 0) {
				count += 1; 
			} 
		}
		results[i] = count; 
	}
	return results; 
}

mat_t *label_nodes_mat(graph_t *m, int *labels) {

	mat_t *A = init_vec(m->vertices, m->vertices, false);
	size_t n = sizeof(labels) / sizeof(labels[0]);

	for(int i = 0; i < m->vertices; i++){
		for(int j = 0; j < m->vertices; j++){

			if(m->matrix->matrix[i*m->vertices+j]->label != NULL){
				if(i == labels[i] && i == j){
					A->arr[i][j] = 1;
				}

				if(i != labels[i]){
					A->arr[i][j] = 1; 
				}	
			}
		}
	}
	return A; 
}

mat_t *label_propogation(mat_t *A, int iterations) {

	int node_count = 2; 
	int labeled_nodes[2] = {0, 1};

	/* get propbabilites */
	double prob;

	/* probabilistic transition matrix */
	mat_t *d = init_vec(A->rows, A->cols, false); 

	/* get adjacency and degree matrix   */
	for(int i = 0; i < A->rows; i++){

		int neighbor_count = 0; 
		for(int j = 0; j < A->rows; j++){
			if(A->arr[i][j] > 0){	
				neighbor_count += 1;  
			}
		}
		d->arr[i][i] = neighbor_count; 
	}

	/* get the determinant of degree matrix */
	double  determinant = 1.00; 
	for(int i = 0; i < d->rows; i++){
		determinant *= d->arr[i][i];
	}

	mat_t *d_1 = scalar_multiply(d, determinant);
	mat_t *result = multiply(A, d_1);
	mat_t *m_power = power(result, iterations); 

	return m_power; 
}
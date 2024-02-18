#include "includes/graph.h"
#include <data_structures/queue/includes/queue.h>



graph_t *init_graph(int v, int e, bool directed) {
	graph_t *g = (graph_t*)malloc(sizeof(graph_t)); 
	g->edges = e; 
	g->vertices = v;
	g->directed = directed; 
	g->visited = malloc(v * sizeof(int));  
	g->list = init_adj_list(g->vertices, g->edges, g->directed); 
	g->matrix = init_adj_mat(g->vertices, g->edges, g->directed); 
	g->labels = malloc(v * sizeof(int)); 
	for (int i = 0; i < v; i++){ g->labels[i] = -1; }
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

void remove_unused_slots(graph_t *g) {
	int last_used_indice = 0;  
	for(int i = g->vertices; i > 0; i--){
		if(g->list->used[i] == 1){
			last_used_indice = i;
			break;
		}
	}
	int remainder = g->vertices - last_used_indice; 
	int new_size = g->vertices - remainder; 
	resize_adj_list(g->list, new_size+1);
	g->vertices = new_size+1; 
} 


void print_walk(walk_t *w){
	printf("Steps: %d\n", w->steps); 
	printf("Cycles: %d\n", w->cycles);
	printf("Weighted sum: %d\n", w->weighted_sum); 
	printf("Path:  "); 
	for(int i = 0; i < w->steps; i++){
		printf("-> %d", w->path[i]); 
	}
}


void label_node(graph_t *g, int index, int label) {
	if(index > g->vertices){
		printf("Index is out of bounds with graph size\n"); 
		exit(1); 
	}
	g->labels[index] = label; 	
} 


adj_mat_t *to_matrix(adj_mat_t *m, adj_list_t *g, bool directed) {
	
	/* iterate through list and populate matrix */
	for(int i = 0; i < g->v; i++) {

		node_t *head = g->items[i]->head;
		node_t *src_node = get_node_by_id(g, i); 
		int row = src_node->id; 
		int col = head->id; 

		while(head) {

			node_t *src = create_node(
				src_node->id, 
				src_node->node_type->node->label, 
				src_node->node_type->node->weight
			);

			node_t *dst = create_node(
				head->id, 
				head->node_type->node->label, 
				head->node_type->node->weight
			); 

			add_node_mat(
				m, src->id, src->node_type->node->label, 
				dst->id, dst->node_type->node->label, 
				head->node_type->node->weight
			); 
			head  = head->next;
		}
	}
	return m; 
}


adj_list_t *to_list(adj_list_t *g, adj_mat_t *m, bool directed) {

	for(int i = 0; i < m->v; i++) {
		for(int j = 0; j < m->v; j++) {
			if(m->items[i*m->v+j]->id > -1) {
				int weight_value = m->items[i*m->v+j]->node_type->node->weight;
				node_t *src = search_node_by_id_mat(m, i); 
				node_t *dst = search_node_by_id_mat(m, j); 
				add_node(
					g, src->id, 
					src->node_type->node->label, 
					dst->id, dst->node_type->node->label, 
					weight_value
				);
			}
		}
	}

	return g; 
}


void print_graph_list(graph_t *g) {
	for(int i = 0; i < g->vertices; i++){
		node_t *head = g->list->items[i]->head;
		printf("%d ", i); 
		while(head) {
			printf("-> (%d, %s)", head->id, head->node_type->node->label); 
			if(head->node_type->node->weight >= 0) {
				printf(" [%d] ", head->node_type->node->weight); 
			}
			head  = head->next; 
		}
		printf("\n"); 
	}
}


graph_t *frame_to_unweighted_graph(frame_t *frame, array_t *cols, bool directed) {

	/* create graph to be returned */ 
	int vertex_count = frame->row_limit * cols->item_count;	
	graph_t *g = init_graph(vertex_count, vertex_count, directed);
	ordered_set_t *set = init_array_set(vertex_count); 


	/* validate that graph is unweighted */
	if(cols->item_count % 2 != 0) {
		if(FRAME_DEBUG) {
			printf("Unweighted graph should be in pairs of 2\n"); 
		}
		g->list->err = true; 
		return g; 
	}


	for(int i = 0; i < cols->item_count; i+=2){

		/* extract values */
		row_value_t **src_header_values = lookup_table_key(
			frame->frame, 
			cols->items[i]->node_type->node->label
		);

		row_value_t **dst_header_values = lookup_table_key(
			frame->frame, 
			cols->items[i+1]->node_type->node->label
		);

		for(int j = 0; j < frame->row_limit; j++){

			char *src = src_header_values[j]->value; 
			char *dst = dst_header_values[j]->value;

			insert_ordered(set, j, src, 0); 
			insert_ordered(set, j, dst, 0); 

			int src_id = get_value_key(set, src); 
			int dst_id = get_value_key(set, dst);

			add_node(g->list, src_id, src, dst_id, dst, 0); 	
		} 
	}

	return g; 
}


graph_t *frame_to_weighted_graph(frame_t *frame, array_t *cols, bool directed) {

	/* create graph */
	int vertex_count = frame->row_limit * cols->item_count;	
	graph_t *g = init_graph(vertex_count, vertex_count, directed);
	ordered_set_t *set = init_array_set(vertex_count); 

	/* validate that graph is unweighted */ 
	if(cols->item_count % 3 != 0) {
		if(FRAME_DEBUG) {
			printf("Weighted graph should be in pairs of 3\n"); 
		}
		g->list->err = true; 
		return g; 
	}

    for(int i = 0; i < cols->item_count; i+=3){
	
		/* extract values */
		row_value_t **src_header_values = lookup_table_key(
			frame->frame, 
			cols->items[i]->node_type->node->label
		);

		row_value_t **dst_header_values = lookup_table_key(
			frame->frame, 
			cols->items[i+1]->node_type->node->label
		); 

		row_value_t **weight_header_values = lookup_table_key(
			frame->frame, 
			cols->items[i+2]->node_type->node->label
		);

		for(int j = 0; j < frame->row_limit; j++) {

			char *src = src_header_values[j]->value; 
			char *dst = dst_header_values[j]->value;
			char *weight = weight_header_values[j]->value;

			/* convert weight to integer */ 
			int weight_to_int = atoi(weight);

			insert_ordered(set, j, src, 0); 
			insert_ordered(set, j, dst, 0); 

			int src_id = get_value_key(set, src); 
			int dst_id = get_value_key(set, dst);

			add_node(g->list, src_id, src, dst_id, dst, weight_to_int); 	
		}
	}

	/* removed unused slots */
	remove_unused_slots(g); 
	return g; 
}

int get_max_vertex_count(char *filename, int file_size) {

	FILE* fp = fopen(filename, "r");
   	int row_count = 0, max_vertex = 0;
    char* buffer = malloc(file_size * sizeof(char));

	while(fgets(buffer, file_size, fp)) {

		/* null terminate the buffer */ 
		int len = strlen(buffer); 
		if(buffer[len-1] == '\n') {
			buffer[len-1] = 0; 
		}

		/* extract tokens from regular expression */
		tokens_t *row_values = match_single(buffer, RE_GML_NODE); 
		int size = row_values->result_size;

		char *id_string = row_values->tokens[0]; 
		int id_to_int = atoi(id_string); 
		char *label = row_values->tokens[1];

		if(id_to_int > max_vertex) {
			max_vertex = id_to_int; 
		}

		/* Check if all neighbors info is there */
		if((size-2) % 3 != 0){
			printf("Line [%d]: Error with node neighbors config\n", row_count);
		}

		/* get neighbors */
		for(int i = 2; i < size; i+=3){
			int id = atoi(row_values->tokens[i]); 
			char *label = row_values->tokens[i+1];
			int weight = atoi(row_values->tokens[i+2]);	

			if(id > max_vertex){
				max_vertex = id; 
			}

		} 
		row_count += 1;
	}

	return max_vertex; 
}


ordered_set_t *get_graph_nodes(graph_t *g) {
	ordered_set_t *set = init_array_set(g->vertices); 
	for(int i = 0; i < g->list->v; i++){
		node_t *head = g->list->items[i]->head;
		insert_ordered(set, head->id, head->node_type->node->label, 0); 
		while(head) {
			insert_ordered(set, head->id, head->node_type->node->label, 0); 
			head  = head->next;
		}
	}
	return set; 
} 


set_t *get_graph_nodes_from_file(char *filename, int file_size) {

	/* variables */
	FILE* fp = fopen(filename, "r");
   	int row_count = 0, insert_count = 0;
    char *head_label; 
    char* buffer = malloc(file_size * sizeof(char));
    node_t *head;
    set_t *node_set =  init_set(true); 


	while(fgets(buffer, file_size, fp)) {

		/* null terminate the buffer */ 
		int len = strlen(buffer); 
		if(buffer[len-1] == '\n') {
			buffer[len-1] = 0; 
		}

		/* extract tokens from regular expression */
		tokens_t *row_values = match_single(buffer, RE_GML); 
		int size = row_values->result_size;

        /* extract node */
		tokens_t *r_quotes = match_single(row_values->tokens[0], REMOVE_QUOTES); 
        char *node = r_quotes->tokens[0];
        insert_sorted(node_set, insert_count, node, 0); 
		insert_count += 1; 

        // /* extract neighbors */
        for(int i = 1; i < size; i++){
		    r_quotes = match_single(row_values->tokens[i], REMOVE_QUOTES); 
            char *neighbor = r_quotes->tokens[0];
            insert_sorted(node_set, insert_count, neighbor, 0);
			insert_count += 1; 
        }

		row_count += 1;
	}    
    return node_set;
}


graph_t *serialize_graph_list_sorted_label(char *filename, int file_size) {

	/* variables */
	FILE* fp = fopen(filename, "r");
   	int row_count = 0;
    char *head_label; 
    char* buffer = malloc(file_size * sizeof(char));
    set_t *nodes = get_graph_nodes_from_file(filename, file_size); 
    graph_t *g = init_graph(nodes->count-1, nodes->count-1, false);


	while(fgets(buffer, file_size, fp)) {

		/* null terminate the buffer */ 
		int len = strlen(buffer); 
		if(buffer[len-1] == '\n') {
			buffer[len-1] = 0; 
		}

		/* extract tokens from regular expression */
		tokens_t *row_values = match_single(buffer, RE_GML); 
		int size = row_values->result_size;

        /* extract node */
		tokens_t *r_quotes = match_single(row_values->tokens[0], REMOVE_QUOTES); 
        char *node = r_quotes->tokens[0];

        /* add all nodes in graph to set */
        for(int i = 1; i < size; i++){

		    r_quotes = match_single(row_values->tokens[i], REMOVE_QUOTES); 
            char *neighbor = r_quotes->tokens[0];

            char *dst = neighbor;
            char *src = node;

            int dst_id = get_item_sorted(nodes, dst); 
            int src_id = get_item_sorted(nodes, src); 

            add_node(g->list, src_id, src, dst_id, dst, 0);

        }
		row_count += 1;
	}

	/* remove unused slots from graph */
	remove_unused_slots(g); 

    return g;
}


graph_t *serialize_graph_list(char *filename, int file_size, bool directed){

	FILE* fp = fopen(filename, "r");
   	int row_count = 0;
    char* buffer = malloc(file_size * sizeof(char));

	/* get max vertex count for graph instance size */
	int vertex_count = get_max_vertex_count(filename, file_size); 
    graph_t *g = init_graph(vertex_count+1, vertex_count+1, directed);

	while(fgets(buffer, file_size, fp)) {

		/* null terminate the buffer */ 
		int len = strlen(buffer); 
		if(buffer[len-1] == '\n') {
			buffer[len-1] = 0; 
		}

		/* extract tokens from regular expression */
		tokens_t *row_values = match_single(buffer, RE_GML_NODE); 
		int size = row_values->result_size;


		char *id_string = row_values->tokens[0]; 
		int src_id = atoi(id_string);
		char *src = row_values->tokens[1];

		/* Check if all neighbors info is there */
		if((size-2) % 3 != 0){
			printf("Line [%d]: Error with node neighbors config\n", row_count);
		}

		/* get neighbors */
		for(int i = 2; i < size; i+=3){
			int dst_id = atoi(row_values->tokens[i]);
			char *dst = row_values->tokens[i+1];
			int weight = atoi(row_values->tokens[i+2]);
			remove_character(dst, '"');
			remove_character(src, '"'); 
			add_node(g->list, src_id, src, dst_id, dst, weight);
		} 
		row_count += 1;
	}

	return g; 
}


void deserialize_graph_list(graph_t *g, char *filename) {

	FILE* fp; 
	fp = fopen(filename, "w");  
	if(access(filename, F_OK) == -1) {
   		strcpy(filename, "");
		printf("File does not exist\n");
	}

	for(int i = 0; i < g->list->v; i++){
		node_t *result = get_node_by_id(g->list, i);
		int id = result->id; 
		char *label = result->node_type->node->label;
		remove_character(label, '"');


		fprintf(fp, "[%d,\"%s\"]: ", id, label);  
		node_t *head = g->list->items[i]->head;
		fprintf(fp, "("); 
		while(head) {
			if (head->next == NULL){
				remove_character(head->node_type->node->label, '"'); 
				fprintf(
					fp, "[%d,\"%s\",%d]", 
					head->id, head->node_type->node->label, 
					head->node_type->node->weight
				);
			} else {
				remove_character(head->node_type->node->label, '"'); 
				fprintf(
					fp, "[%d,\"%s\",%d],", 
					head->id, head->node_type->node->label, 
					head->node_type->node->weight
				);
			}
			head  = head->next;
		}
		fprintf(fp, ")\n");
	}
	fclose(fp);
} 

graph_t *serialize_mat_graph(char *filename, int file_size) {
    printf("Serialize Mat\n");
}

void deserialize_mat_graph(graph_t *mat) {
    printf("De Serialize Mat\n");
} 

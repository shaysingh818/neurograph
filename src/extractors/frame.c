#include "includes/frame.h"
#include "includes/re.h"


void extract_frame_headers(frame_t *frame) {
	
    FILE *fp = fopen(frame->filename, "r"); 
	int headers_size;

	frame->row_count = 0; 
	frame->header_count = 0; 

	/* iterate through file */
	while(fgets(frame->file_buffer, frame->buffer_size, fp)) {

		/* null terminate the buffer */ 
		int len = strlen(frame->file_buffer); 
		if(frame->file_buffer[len-1] == '\n') {
			frame->file_buffer[len-1] = 0; 
		}

		/* extract headers and allocate rows */
		if(frame->row_count == 0) {

			/* extract tokens from regular expression */
			tokens_t *row_values = match_single(frame->file_buffer, RE_CSV); 
			headers_size = row_values->result_size; 
			frame->header_count = headers_size;  

			/* allocate headers based on results */
			frame->headers = malloc(headers_size * sizeof(header_t*));
			for(int i = 0; i < headers_size; i++){
				frame->headers[i] = malloc(sizeof(header_t)); 
				frame->headers[i]->index = i; 
				frame->headers[i]->name_size = strlen(row_values->tokens[i]) + 1;
				frame->headers[i]->name = malloc(frame->headers[i]->name_size * sizeof(char));  
				strcpy(frame->headers[i]->name, row_values->tokens[i]); 
			}
			free(row_values); 
		}
		frame->row_count += 1; 
	}

	/* allocate values for each header based on row size */
	for(int i = 0; i < headers_size; i++){
		frame->headers[i]->values_amount = frame->row_count; 
		frame->headers[i]->values = malloc(frame->row_count * sizeof(value_t*)); 
		for(int j = 0; j < frame->row_count; j++){
			frame->headers[i]->values[j] = malloc(sizeof(value_t)); 
		}
	}
	
}


void init_frame_rows(frame_t *frame) {

	/* variables */
	FILE* fp = fopen(frame->filename, "r");
   	int row_count = 0;

	while(fgets(frame->file_buffer, frame->buffer_size, fp)) {

		/* null terminate the buffer */ 
		int len = strlen(frame->file_buffer); 
		if(frame->file_buffer[len-1] == '\n') {
			frame->file_buffer[len-1] = 0; 
		}

		// /* extract tokens from regular expression */
		tokens_t *row_values = match_single(frame->file_buffer, RE_CSV); 
		int size = row_values->result_size;

		/* print out values */
		for(int i = 0; i < row_values->result_size; i++){
			//printf("Header: %d  Row: %d Value: %s\n", i, row_count, row_values->tokens[i]);
			size_t token_size = strlen(row_values->tokens[i])+1;
			frame->headers[i]->values[row_count]->value = malloc(token_size * sizeof(char)); 
			strcpy(frame->headers[i]->values[row_count]->value, row_values->tokens[i]);
			frame->headers[i]->values[row_count]->value_size = strlen(row_values->tokens[i])+1;
			frame->headers[i]->values[row_count]->index = row_count;
		}
		row_count += 1;
	}
} 


frame_t *init_frame(char *filename, int buffer_size){

	/* add to structure properties */ 
	size_t name_size = strlen(filename) + 1; 
	frame_t *frame; 
	frame = malloc(sizeof(frame_t));
   	frame->filename = (char*)malloc(name_size * sizeof(char)); 
	frame->buffer_size = buffer_size;
	frame->file_buffer = malloc(buffer_size * sizeof(char));
	frame->status = true;  
	
   	strcpy(frame->filename, filename);

	/* check if file exists */
	if(access(filename, F_OK) == -1) {
   		strcpy(frame->filename, "");
		printf("File does not exist\n");
		frame->status = false; 
	   	return frame; 	
	}

	/* initalize data in frame */
	extract_frame_headers(frame); 
	init_frame_rows(frame); 

    return frame; 
}


void f_cols(frame_t *frame) {
	printf("FILEPATH: %s\n", frame->filename); 
    printf("Loaded: %d rows\n\n", frame->row_count);
	printf("FEATURES: %d\n", frame->header_count); 
	printf("============================\n");  
	for(int i = 0; i < frame->header_count; i++){
		printf(
			"[%d] -> %s\n",
			frame->headers[i]->index, frame->headers[i]->name
		);		
	}	
}


adj_list_t *frame_to_unweighted_graph(frame_t *frame, int *cols, int size, bool directed) {

	/* create graph to be returned */ 
	int vertex_count = frame->row_count * size;	
	adj_list_t *g = init_graph(vertex_count, vertex_count, directed);


	/* validate that graph is unweighted */
	if(size % 2 != 0) {
		if(FRAME_DEBUG) {
			printf("Unweighted graph should be in pairs of 2\n"); 
		}
		g->err = true; 
		return g; 
	}

	char *head_label = frame->headers[cols[0]]->values[0]->value;
	int head_id = frame->headers[cols[0]]->values[0]->index;  
	node_t *head = create_node(head_id, head_label, 0); 

	for(int i = 0; i < size; i+=2){

		/* extract values */
		value_t **src_header_values = frame->headers[cols[i]]->values;
		value_t **dst_header_values = frame->headers[cols[i+1]]->values;

		for(int j = 1; j < frame->row_count; j++){

			char *src = src_header_values[j]->value; 
			char *dst = dst_header_values[j]->value;

			node_t *src_node = create_node(j, src, 0);
			node_t *dst_node = create_node(j, dst, 0);

			/* add src and dst to ull (unique linked list) */ 
			unique_append_ll(&head, src_node); 
			unique_append_ll(&head, dst_node);

			/* get the id for the head and src */
			int src_id = get_id_ll(head, src); 
			int dst_id = get_id_ll(head, dst);  

			add_node(g, src_id, src, dst_id, dst, 0); 	
		} 
	}

	return g; 
}


adj_list_t *frame_to_weighted_graph(frame_t *frame, int *cols, int size, bool directed) {

	/* create graph */
	int vertex_count = frame->row_count * size;	
	adj_list_t *g = init_graph(vertex_count, vertex_count, directed);

	/* validate that graph is unweighted */ 
	if(size % 3 != 0) {
		if(FRAME_DEBUG) {
			printf("Weighted graph should be in pairs of 3\n"); 
		}
		g->err = true; 
		return g; 
	}

	char *head_label = frame->headers[cols[0]]->values[0]->value;
	int head_id = frame->headers[cols[0]]->values[0]->index;  
	node_t *head = create_node(head_id, head_label, 0); 

    for(int i = 0; i < size; i+=3){
	
		/* extract values */
		value_t **src_header_values = frame->headers[cols[i]]->values;
		value_t **dst_header_values = frame->headers[cols[i+1]]->values;
		value_t **weight_header_values = frame->headers[cols[i+2]]->values;

		for(int j = 1; j < frame->row_count; j++) {

			char *src = src_header_values[j]->value; 
			char *dst = dst_header_values[j]->value;
			char *weight = weight_header_values[j]->value;

			/* convert weight to integer */ 
			int weight_to_int = atoi(weight);

			node_t *src_node = create_node(j, src, weight_to_int);
			node_t *dst_node = create_node(j, dst, weight_to_int);

			/* add src and dst to ull (unique linked list) */ 
			unique_append_ll(&head, src_node); 
			unique_append_ll(&head, dst_node);

			/* get the id for the head and src */
			int src_id = get_id_ll(head, src); 
			int dst_id = get_id_ll(head, dst);  

			add_node(g, src_id, src, dst_id, dst, weight_to_int); 	
		}
	}

	/* clear unused empty slots */
	int last_used_indice = 0;  
	for(int i = g->v; i > 0; i--){
		node_t *head = g->items[i].head;
		if(head && i != g->v){
			last_used_indice = i; 
			break; 
		}
	}

	int remainder = g->v - last_used_indice; 
	int new_size = g->v - remainder; 
	resize_adj_list(g, new_size+1); 

	return g; 
} 
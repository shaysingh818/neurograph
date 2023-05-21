#include "includes/csv.h"
#include "../data_structures/includes/map.h"

int populate_headers(csv_t *csv) {

	/* variables */ 
	FILE* fp = fopen(csv->filename, "r");
	char buffer[csv->buffer_size];
	int header_count = 0; 
   	int row_count = 0;

	/* add header structs to csv */ 
	csv->cols = malloc(FEATURE_SIZE * sizeof(col_t*)); 
	for(int i = 0; i < FEATURE_SIZE; i++) {
		csv->cols[i] = malloc(sizeof(col_t)); 
	}

	/* read file contents */ 
	while(fgets(buffer, csv->buffer_size, fp)) {

		/* limit amount of rows we load for feature */
		if(row_count > 0) {
			break; 
		}

		/* null terminate the buffer */ 
		int len = strlen(buffer); 
		if(buffer[len-1] == '\n') {
			buffer[len-1] = 0; 
		}

		/* extract comma separated values */ 
		char *value = strtok(buffer, ",");
		size_t value_length = strlen(value) + 1;

		/* add value to first column */ 
		csv->cols[header_count]->name = (char*)malloc(value_length * sizeof(char));
		strcpy(csv->cols[header_count]->name, value); 
		csv->cols[header_count]->row_index = header_count; 
		csv->cols[header_count]->name_length = value_length;
		header_count += 1; 


		while(value) {

			/* grab header value unless we reach the end */
			value = strtok(NULL, ",");
			if(value == NULL) {
				break; 
			}

			/* copy value to column */
			value_length = strlen(value) + 1;
			csv->cols[header_count]->name = (char*)malloc(value_length * sizeof(char));
			strcpy(csv->cols[header_count]->name, value); 
			csv->cols[header_count]->row_index = header_count; 
			csv->cols[header_count]->name_length = value_length;
			csv->col_count = header_count; 
			header_count += 1;


			if(header_count >= FEATURE_SIZE) {

				/* size of array to reallocate */ 
				int realloc_size = (header_count + FEATURE_SIZE) + 1; 

				/* reallocate remaining feature structures */ 
				csv->cols = realloc(csv->cols, realloc_size * sizeof(col_t*));
				for(int i = header_count; i < realloc_size; i++) {
					csv->cols[i] = malloc(sizeof(col_t)); 
				}
			}			
		}

		row_count += 1; 
	}
	return TRUE; 
}



int populate_rows(csv_t *csv) {

	/* variables */ 
	FILE* fp = fopen(csv->filename, "r");
	char buffer[csv->buffer_size];
   	int row_count = 0;

	/* allocate line data */ 
	csv->rows = malloc(csv->row_limit * sizeof(row_t*)); 
	for(int i = 0; i < csv->row_limit; i++) {
		csv->rows[i] = malloc(sizeof(row_t)); 
	}



	while(fgets(buffer, csv->buffer_size, fp)) {

		/* limit amount of rows we load for feature */
		if(row_count == csv->row_limit) {
			break; 
		}

		/* null terminate the buffer */ 
		int len = strlen(buffer); 
		if(buffer[len-1] == '\n') {
			buffer[len-1] = 0; 
		}

		/* variables for line data */
		int line_size = 0;
	   	int header_count = 0; 	
	  	char **line = malloc(csv->col_count * sizeof *line); 	
		char *value = strtok(buffer, ",");
		size_t value_length = strlen(value) + 1;

		/* copy first line value and allocate space */ 
		line[header_count] = malloc(value_length * sizeof(char)); 
		strcpy(line[header_count], value);
		line_size += value_length; 
	   	header_count += 1; 	

		while(value) {

			/* grab header value unless we reach the end */
			value = strtok(NULL, ",");
			if(value == NULL) {
				break; 
			}

			/* copy value in line array */ 
			value_length = strlen(value) + 1;
			line[header_count] = malloc(value_length * sizeof *line[header_count]); 
			strcpy(line[header_count], value);
			line_size += value_length;

			/* terminate files with bad input */
			if(header_count > csv->col_count){
				csv->status = false; 
				printf("Header and col count are not the same\n"); 
				return FALSE;  
			}
	   		header_count += 1; 	
		}

		/* add to line */
		csv->rows[row_count]->line = line; 
		csv->rows[row_count]->line_size = line_size;
		csv->rows[row_count]->value_count = csv->col_count;
		row_count += 1; 
	}
	return TRUE; 
}


csv_t *csv_init(char *filename, int buf_size, int set_limit) {

	/* add to structure properties */ 
	size_t name_size = strlen(filename) + 1; 
	csv_t *csv; 
	csv = malloc(sizeof(csv_t));
   	csv->filename = (char*)malloc(name_size * sizeof(char)); 
   	strcpy(csv->filename, filename);
	csv->buffer_size = buf_size;
	csv->row_limit = set_limit; 

	/* check if file exists */
	if(access(filename, F_OK) == -1) {
   		strcpy(csv->filename, "");
		printf("File does not exist\n");
		csv->status = FALSE; 
	   	return csv; 	
	}


	/* populate headers */ 
	int headers = populate_headers(csv); 
	if(!headers) {
		csv->status = false; 
		printf("HERE\n");
		return csv; 
	}

	/* populate rows */ 
	int rows = populate_rows(csv); 
	if(!rows) {
		return csv; 
	}

	/* set to true */ 
	csv->status = TRUE; 
	return csv; 
}


void print_cols(csv_t *csv) {
	for(int i = 0; i < csv->col_count; i++) {
		printf("[%d] -> %s\n", i, csv->cols[i]->name); 
	}
}


void print_rows(csv_t *csv) {
	for(int i = 0; i < csv->row_limit; i++) {
		for(int j = 0; j < csv->rows[i]->value_count; j++) {
			printf("%s, ", csv->rows[i]->line[j]); 
		}
		printf("\n"); 
	}
}


void csv_info(csv_t *csv) {
	printf("FILE NAME: %s\n", csv->filename); 
	printf("COLS: %d\n", csv->col_count); 
	printf("ROW COUNT: %d\n", csv->row_limit); 
	printf("BUFFER_SIZE: %d\n", csv->buffer_size); 
}


adj_list_t *csv_to_unweighted_graph(csv_t *csv, int *cols, int size, bool directed) {

	/* create graph to be returned */ 
	int vertex_count = csv->row_limit * size;	
	adj_list_t *g = init_graph(vertex_count, vertex_count, directed);
	
	/* validate that graph is unweighted */
	if(size % 2 != 0) {
		if(DEBUG) {
			printf("Unweighted graph should be in pairs of 2\n"); 
		}
		g->err = true; 
		return g; 
	}

	/* use queue here instead */
	u_ll_t *head = create_ull(csv->rows[0]->line[cols[0]]);
	int head_id = get_id(head, head->value);
   
	/* link it to itself for now */ 
	add_end_node(g, head_id, head->value, 0);

	for(int i = 0; i < size; i += 2) {
		for(int j = 1; j < csv->row_limit; j++) {

			char *src = csv->rows[j]->line[cols[i]];
			char *dst = csv->rows[j]->line[cols[i+1]];

			/* add src and dst to ull (unique linked list) */ 
			append(&head, src); 
			append(&head, dst);

			/* get unique src and dest id */
			int src_id = get_id(head, src); 
			int dst_id = get_id(head, dst);
	
			add_node(g, src_id, src, dst_id, dst, 0); 	
		}		
	}

	return g; 
}



adj_list_t *csv_to_weighted_graph(csv_t *csv, int *cols, int size, bool directed) {

	/* create graph */
	int vertex_count = csv->row_limit * size;	
	adj_list_t *g = init_graph(vertex_count, vertex_count, directed);

	/* validate that graph is unweighted */ 
	if(size % 3 != 0) {
		if(DEBUG) {
			printf("Weighted graph should be in pairs of 3\n"); 
		}
		g->err = true; 
		return g; 
	}

	/* create unique linked list for storing node values */  
	u_ll_t *head = create_ull(csv->rows[0]->line[cols[0]]);
	int head_id = get_id(head, head->value);

    for(int i = 0; i < size; i+=3){
		for(int j = 1; j < csv->row_limit; j++) {
			
			/* get src, dst and weight for graph */ 
			char *src = csv->rows[j]->line[cols[i]];
			char *dst = csv->rows[j]->line[cols[i+1]];
			char *weight = csv->rows[j]->line[cols[i+2]];

			/* convert weight to integer */ 
			int weight_to_int = atoi(weight);

			/* need to catch error for converting from char* to int */ 

			/* add nodes to unique linked list */ 
			append(&head, src); 
			append(&head, dst);

			/* get unique id for src and dst */ 
			int src_id = get_id(head, src); 
			int dst_id = get_id(head, dst);
		   	add_node(g, src_id, src, dst_id, dst, weight_to_int); 	
		}
	} 

	print_u_ll_t(head); 

	return g; 
}


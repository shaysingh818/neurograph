#include "includes/frame.h"


frame_t *create_frame(char *filename, int buffer_size, int row_limit, char *delimiter){

	/* add to structure properties */ 
	size_t name_size = strlen(filename) + 1; 
	frame_t *frame; 
	frame = malloc(sizeof(frame_t));
   	frame->filename = (char*)malloc(name_size * sizeof(char)); 
	frame->buffer_size = buffer_size;
	frame->file_buffer = malloc(buffer_size * sizeof(char));
	frame->status = true;
	frame->row_limit = row_limit; 
	frame->frame = hash_table(
		1, 0.5, 
		compare_char, 
		free_char,
		NULL, 
		additive_hash
	); 
	
   	strcpy(frame->filename, filename);

	/* set file delim */
	if(delimiter == NULL) {
		frame->delimiter = malloc(strlen(",") * sizeof(char)); 
		strcpy(frame->delimiter, ","); 
	} else {
		frame->delimiter = malloc(strlen(delimiter)+1 * sizeof(char)); 
		strcpy(frame->delimiter, delimiter); 
	}

	/* check if file exists */
	if(access(filename, F_OK) == -1) {
   		strcpy(frame->filename, "");
		printf("File does not exist\n");
		frame->status = false; 
	   	return frame; 	
	}

	return frame; 
}


frame_t *dataframe(char *filepath, int buffer_size, int row_limit, char *delimiter) {

	/* create frame structure and it's attributes */
	frame_t *frame = create_frame(filepath, buffer_size, row_limit, delimiter); 
	if(!frame->status){
		printf("Error creating dataframe: %s\n", filepath);
	}

	/* extract the headers from the frame */
	extract_headers(frame); 
	if(!frame->status){
		printf("Error extracting dataframe headers: %s\n", filepath);
	}

	/* extract frame values into hash map */
	init_rows(frame); 
	if(!frame->status){
		printf("Error extracting dataframe rows: %s\n", filepath);
	}

    return frame; 

}


row_value_t *init_row_value(int index, char *value) {

	row_value_t *r = (row_value_t*)malloc(sizeof(row_value_t)); 
	r->index = index;
    r->value_size = strlen(value)+1; // Keep track of nodes being created 
	r->value = NULL; 

	/* copy in string value if not NULL  */
	if(value != NULL) {
		size_t value_length = strlen(value) + 1;
		r->value = (char*)malloc(value_length * sizeof(char));
		strcpy(r->value, value);
	} 
	return r; 
}


mat_t *frame_to_matrix(frame_t *frame, array_t *cols) {

	mat_t *mat_result = init_matrix(frame->row_limit, cols->item_count); 
	for(int i = 0; i < cols->item_count; i++){

		row_value_t **values = lookup_table_key(frame->frame, cols->items[i]->label); 
		int failure = lookup_table_key(frame->frame, cols->items[i]->label); 
		if(failure == 0){
			printf("Key error: %s\n", cols->items[i]->label); 
			exit(0); 
		}

		for(int j = 0; j < frame->row_limit; j++){			
			char *value = values[j]->value, *err;
			double mat_value; 
			mat_value = strtod(value, &err);
			if(value == err){
				printf(
					"Cant convert %s column to numeric representation\n",
					cols->items[i]->label
				);
				frame->status = false;  
			}
			mat_result->arr[j][i] = mat_value; 
		}
	}

	return mat_result;  
} 


void extract_headers(frame_t *frame) {
	
    FILE *fp = fopen(frame->filename, "r"); 
	int headers_size;
	frame->curr_row = 0; 
	frame->header_count = 0; 

	/* iterate through file */
	while(fgets(frame->file_buffer, frame->buffer_size, fp)) {

		if(frame->curr_row == frame->row_limit){
			break;
		}

		/* null terminate the buffer */ 
		end_line_terminate(frame->file_buffer); 

		/* extract headers and allocate rows */
		if(frame->curr_row == 0) {

			/* extract tokens from regular expression */
    		array_t *semi_results = match_delimeter_file(frame->file_buffer, frame->delimiter);
			headers_size = semi_results->item_count;

			/* remove special carriage characters from EOF */
			char *value = semi_results->items[headers_size-1]->label; 
    		remove_character(value, '\r'); 

            frame->headers= semi_results; 
			frame->header_count = headers_size; 
		}
		frame->curr_row += 1; 
	}
}


void init_rows(frame_t *frame) {

	FILE* fp = fopen(frame->filename, "r");

	for(int i = 0; i < frame->header_count; i++){

		char *key = frame->headers->items[i]->label;

		/* allocate row values array for column */
		row_value_t **values = malloc(frame->row_limit * sizeof(row_value_t*));
		for(int n = 0; n < frame->row_limit; n++){
			values[n] = malloc(sizeof(row_value_t)); 
		}

		fseek(fp, 0, SEEK_SET);

		frame->curr_row = 0; 
		int row_counter = 0;  
		while(fgets(frame->file_buffer, frame->buffer_size, fp)) {

			array_t *row_vals = match_delimeter_file(frame->file_buffer, frame->delimiter);
			int size = row_vals->item_count;


			if(size != frame->header_count) {
				frame->status = false; 
			}

			if(frame->curr_row == frame->row_limit){
				break; 
			}

			char *value = row_vals->items[i]->label;  
			if(i == size-1){
				end_line_terminate(value); 
			}

			if(row_counter > 0){
				row_value_t *val = init_row_value(frame->curr_row, value);
				values[frame->curr_row] = val; 
				frame->curr_row += 1;   
			}


			row_counter += 1;
		}

		add_table_map(frame->frame, key, values); 
	}

	/* if our row limit is greater than the amount of rows in the file */
	if(frame->curr_row < frame->row_limit) {
		frame->row_limit = frame->curr_row;  
	} 
}


void print_cols(frame_t *frame) {
	printf("Filepath: %s\n", frame->filename); 
    printf("Rows Loaded: %d\n", frame->row_limit);
	printf("Feature Count: %d\n", frame->header_count);
    printf("\n"); 
    print_array(frame->headers);  
}


void print_rows(frame_t *frame) {
    row_value_t ***col_values = malloc(frame->headers->item_count * sizeof(row_value_t**)); 
    for(int i = 0; i < frame->headers->item_count; i++){
        row_value_t **values = lookup_table_key(frame->frame, frame->headers->items[i]->label);
        col_values[i] = values;  
    }


    for(int j = 0; j < frame->row_limit; j++){        
        for(int i = 0; i < frame->headers->item_count; i++){

			/* cut off column value if it's greater than the length of the header */
			char *value = strdup(col_values[i][j]->value);
			if(strlen(value) > strlen(frame->headers->items[i]->label)){
				value[strlen(frame->headers->items[i]->label)] = '\0'; 
			}

            printf("%20s", value);
        }
        printf("\n"); 
    }
}


void drop_cols(frame_t *frame, array_t *cols) {
	for(int i = 0; i < cols->item_count; i++){
		remove_char(frame->headers, cols->items[i]->label); 
		delete_table_key(frame->frame, cols->items[i]->label);
	}
} 
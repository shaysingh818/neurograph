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
		frame->headers[i]->values = malloc(frame->row_count * sizeof(row_value_t*)); 
		for(int j = 0; j < frame->row_count; j++){
			frame->headers[i]->values[j] = malloc(sizeof(row_value_t)); 
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


void init_frame_map(frame_t *frame) {

	/* variables */
	FILE* fp = fopen(frame->filename, "r");

	for(int i = 0; i < frame->header_count; i++){

		char *key = frame->headers[i]->name;
		int row_count = 0;

		/* allocate row values array for column */
		row_value_t **values = malloc(frame->row_count * sizeof(row_value_t*));
		for(int n = 0; n < frame->row_count; n++){
			values[n] = malloc(sizeof(row_value_t)); 
		}

		/* rewind to beginning of file */
		fseek(fp, 0, SEEK_SET);

		while(fgets(frame->file_buffer, frame->buffer_size, fp)) {

			tokens_t *row_values = match_single(frame->file_buffer, RE_CSV); 
			int size = row_values->result_size;

			size_t token_size = strlen(row_values->tokens[i])+1;
			values[row_count]->value = malloc(token_size * sizeof(char)); 
			strcpy(values[row_count]->value, row_values->tokens[i]);
			row_count += 1;
		}
		add_map(frame->map, key, values);
	}

	fclose(fp);
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
	frame->map = init_table(1, compare_char, NULL, NULL, additive_hash);
	
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


int count_lines(char *filename, int file_size) {

	/* variables */
	FILE* fp = fopen(filename, "r");
	char *file_buffer = malloc(file_size * sizeof(char));
	int row_count = 0; 

	while(fgets(file_buffer, file_size, fp)) {
		row_count += 1;
	}

	fclose(fp);
	return row_count; 
} 
#include "includes/csv.h"


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

	/* read file contents */ 
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
	  	char **line = malloc(csv->col_count * sizeof(char*)); 	
	   	int header_count = 0; 	
		char *value = strtok(buffer, ",");
		size_t value_length = strlen(value) + 1;

		/* copy first line value and allocate space */ 
		line[header_count] = (char*)malloc(value_length * sizeof(char)); 
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
			line[header_count] = (char*)malloc(value_length * sizeof(char)); 
			strcpy(line[header_count], value);
			line_size += value_length;
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
	csv_t *csv = (csv_t*)malloc(sizeof(csv_t));
   	csv->filename = (char*)malloc(name_size * sizeof(char)); 
   	strcpy(csv->filename, filename);
	csv->buffer_size = buf_size;
	csv->row_limit = set_limit; 

	/* check if file exists */ 


	/* populate headers */ 
	int headers = populate_headers(csv); 
	if(headers) {
		printf("[+] Loaded headers..\n"); 
	}

	/* populate rows */ 
	int rows = populate_rows(csv); 
	if(rows) {
		printf("[+] Loaded rows..\n"); 
	}

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




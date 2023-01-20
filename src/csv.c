#include "includes/csv.h"

feature_list_t *init_feature_list(
	char *file_name, 
	int feature_count, feature_t **features) {

	feature_list_t *f = (feature_list_t*)malloc(sizeof(feature_list_t));
	size_t filename_length = strlen(file_name) + 1;
   	f->file_name = (char*)malloc(filename_length * sizeof(char)); 	
	f->feature_count = feature_count;
   	f->features = features; 	
	
	/* copy in string value */ 
	strcpy(f->file_name, file_name); 

	return f; 
}


feature_list_t *csv_feature_extraction(char *set_filename) {
	
	/* dynamic header extraction */ 
	int row = 0; 
	FILE* fp; 
	char *token;
	char buffer[FILE_BUFFER_SIZE];
	feature_list_t *feature_list; 

	/* allocate initial space of one feature */ 
	feature_t **features = malloc(FEATURE_SIZE * sizeof(feature_t*)); 
	for(int i = 0; i < FEATURE_SIZE; i++) {
		features[i] = malloc(sizeof(feature_t)); 
	}

	/* allocate space for filename */ 
	size_t filename_length = strlen(set_filename) + 1; 
	char *filename = (char*)malloc(filename_length * sizeof(char));
   	strcpy(filename, set_filename);
	fp = fopen(filename, "r"); 	
	
	while(fgets(buffer, FILE_BUFFER_SIZE, fp)) {

		/* only grab headers */ 
		if(row > 0) {
			break; 
		}

		/* null terminate the buffer */ 
		int len = strlen(buffer); 
		if(buffer[len-1] == '\n') {
			buffer[len-1] = 0; 
		}

	   	int header_count = 0; 	
		char *value = strtok(buffer, ",");
		size_t value_length = strlen(value) + 1;

		while(value) {

			/* grab header value unless we reach the end */
			value = strtok(NULL, ",");
			if(value == NULL) {
				break; 
			}

			/* grab length of current value and insert */ 
			value_length = strlen(value) + 1;
			features[header_count]->name = (char*)malloc(value_length * sizeof(char)); 
			strcpy(features[header_count]->name, value); 
			features[header_count]->row_index = header_count; 
			features[header_count]->name_length = value_length;
			header_count += 1;

			if(header_count >= FEATURE_SIZE) {

				/* size of array to reallocate */ 
				int realloc_size = (header_count + FEATURE_SIZE) + 1; 

				/* reallocate remaining feature structures */ 
				features = realloc( features, realloc_size * sizeof(feature_t*));
				for(int i = header_count; i < realloc_size; i++) {
					features[i] = malloc(sizeof(feature_t)); 
				}
			}
		}
		
		/* create final list of features */ 
		feature_list = init_feature_list(filename, header_count, features); 
		row += 1; 
	}
	return feature_list; 
}


void print_feature(feature_t *f) {
	printf("===========================\n"); 
	printf("NAME: %s\n", f->name);
	printf("ROW INDEX: %d\n", f->row_index); 
	printf("NAME LENGTH: %ld\n", f->name_length); 
}

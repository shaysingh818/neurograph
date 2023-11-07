#include "includes/utils.h"


void end_line_terminate(char *buffer) {
	int len = strlen(buffer); 
	if(buffer[len-1] == '\n') {
		buffer[len-1] = '\0'; 
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
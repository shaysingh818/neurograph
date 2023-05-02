#include "includes/csv.h" 


int main(int argc, char **argv) {

	// test for memory leaks here
	int indices[2] = {1, 3}; 
	int equality_status = TRUE; 

	csv_t *file = csv_init("../../examples/data/movies.csv", FILE_BUFFER_SIZE, 4);
	if(!file->status) {
		printf("Invalid file"); 
		exit(0); 
	}

	free(file); 

}
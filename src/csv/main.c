#include "includes/csv.h" 


int main(int argc, char **argv) {

	// test for memory leaks here
	int indices[2] = {1, 3}; 
	int equality_status = TRUE; 
	csv_t *file = csv_init("../../examples/data/test.csv", FILE_BUFFER_SIZE, 4);
	if(!file->status) {
		printf("Invalid file"); 
		exit(0); 
	}

	csv_info(file);
   	print_cols(file);

	// see if the graph part works
	adj_list_t *g = csv_to_unweighted_graph(file, indices, 2, false);
   	if(!g->err) {
		equality_status = FALSE; 
	}

	print_graph(g); 	

}


#include "includes/test_graph_extraction.h"

int main(int argc, char **argv) {

	test_save_load_graph_config(); 
	test_save_load_movies_graph();
	test_save_load_public_transport_graph(); 
	test_save_load_online_retail_graph(); 

	return 0; 
}

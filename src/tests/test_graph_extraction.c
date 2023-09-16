#include "includes/test_graph_extraction.h"
#include <assert.h>

void test_save_load_graph_config() {

	/* test load graph config  */ 
  	int vertices = 5; // num of vertices

	graph_t *g = init_graph(vertices, vertices, false); 
	add_node(g->list, 0, "A", 1, "B", 0); 
	add_node(g->list, 0, "A", 2, "C", 0); 
	add_node(g->list, 0, "A", 3, "D", 0); 
	add_node(g->list, 1, "B", 2, "C", 0);
	add_node(g->list, 4, "E", 2, "C", 0);

	/* serialize and de serialize */ 
	char *path = "../../examples/gml/integration/local.gmul";
	deserialize_graph_list(g, path);
	graph_t *serialized = serialize_graph_list(path, 2048, true); 

	assert(serialized->list->v == g->list->v); 	
	printf("%s::%s... \e[0;32mPASSED\e[0m\n", __FILE__, __FUNCTION__);
}


void test_save_load_movies_graph() {

	int indices[2] = {1,5}; 
	char *input_path = "../../examples/data/movies.csv";
	char *output_path = "../../examples/gml/integration/movies.gmul";

	frame_t *frame = init_frame(input_path, 1024, 100); 
	assert(frame->status); 

	graph_t *result = frame_to_unweighted_graph(
		frame, indices, 2, false
	);

	/* de serialize */ 
	remove_unused_slots(result); 
	deserialize_graph_list(result, output_path);


	graph_t *g = serialize_graph_list(output_path, 2048, true);
	assert(g->list->v == 154); 
	printf("%s::%s... \e[0;32mPASSED\e[0m\n", __FILE__, __FUNCTION__);
}


void test_save_load_public_transport_graph() {

	int indices[2] = {3, 7}; 
	char *input_path = "../../examples/data/public_transport.csv";
	char *output_path = "../../examples/gml/integration/public_transport.gmul";

	frame_t *frame = init_frame(input_path, 1024, 500); 
	assert(frame->status);

	graph_t *result = frame_to_unweighted_graph(
		frame, indices, 2, false
	);

	remove_unused_slots(result); 
	deserialize_graph_list(result, output_path);

	graph_t *g = serialize_graph_list(output_path, 2048, true);
   	assert(g->list->v == 711); 	

	printf("%s::%s... \e[0;32mPASSED\e[0m\n", __FILE__, __FUNCTION__);
}


void test_save_load_online_retail_graph() {

	int indices[2] = {6, 0}; 
	char *input_path = "../../examples/data/online_retail.csv";
	char *output_path = "../../examples/gml/integration/online_retail.gmul";

	frame_t *frame = init_frame(input_path, 1024, 500); 
	assert(frame->status);

	graph_t *result = frame_to_unweighted_graph(
		frame, indices, 2, false
	);

	remove_unused_slots(result); 
	deserialize_graph_list(result, output_path);
	graph_t *g = serialize_graph_list(output_path, 2048, true);
   	assert(g->list->v == 76); 

	printf("%s::%s... \e[0;32mPASSED\e[0m\n", __FILE__, __FUNCTION__);
}





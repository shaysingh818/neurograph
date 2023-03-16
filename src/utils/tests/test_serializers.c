#include "includes/test_serializers.h"

void test_adj_list_serializer() {


	int vertices = 5; 
	adj_list_t *g = init_graph(vertices, vertices, false); 
	add_node(g, 0, "A", 1, "B", 0); 
	add_node(g, 0, "A", 2, "C", 0); 
	add_node(g, 0, "A", 3, "D", 0); 
	add_node(g, 1, "B", 2, "C", 0);
	add_node(g, 4, "E", 2, "C", 0);

	adj_list_serialize_t *a = adj_list_serializer(g); 

	for(int i = 0; i < a->vertice_count; i++){
		printf("Vertice: %d\n", i); 
		for(int j = 0; j < a->vertice_count; j++){
			printf("-> %s", a->items[i]->items[j]);
		}
		printf("\n"); 
	}
	

	
}

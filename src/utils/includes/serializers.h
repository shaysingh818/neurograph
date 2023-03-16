
#include "../../graph/includes/graph.h"

/*  Serializer structs */

struct NodeListSerializer {
	int count; 
	char **items; 
}; 

typedef struct NodeListSerializer node_list_serialize_t; 

struct AdjListSerializer {
	int vertice_count; 
	node_list_serialize_t **items; 	
}; 

typedef struct AdjListSerializer adj_list_serialize_t; 


struct MatrixSerializer {
	int vertice_count; 
	entry_t **items; 	
}; 

typedef struct MatrixSerializer matrix_serialize_t; 


/* create a serializer */
adj_list_serialize_t *adj_list_serializer(adj_list_t *g); 
matrix_serialize_t *matrix_serializer(mat_t *m); 

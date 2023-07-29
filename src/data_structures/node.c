#include "includes/node.h"


node_t *create_node(int id, char *label, int weight) {
	node_t *n;
	n = (node_t*)malloc(sizeof(node_t)); 
	n->id = id;
	n->counter = 1; // Keep track of nodes being created 
	n->weight = weight;
	n->label = NULL;  
	n->next = NULL;
	n->right = NULL; 
	n->left = NULL;  

	/* copy in string value if not NULL  */
	if(label != NULL) {
		size_t label_length = strlen(label) + 1;
		n->label = (char*)malloc(label_length * sizeof(char));
		strcpy(n->label, label); 
	} 
	return n; 
}

void print_node(node_t *node) {
	printf("ID: %d, LABEL: %s ", node->id, node->label);
	if(node->weight > 0) {
		printf("WEIGHT: %d ", node->weight); 
	}
	printf("\n"); 
}


edge_t *create_edge(node_t *n1, node_t *n2, int weight) {
    edge_t *e;
    e = (edge_t*)malloc(sizeof(edge_t));
    e->src = n1;
    e->dest = n2;
    e->weight = weight;
    return e;
}

void print_edge(edge_t *e) {
	printf("(%d -> %d) WEIGHT: %d\n", e->src->id, e->dest->id, e->weight); 
}
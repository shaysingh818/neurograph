#include "includes/node.h"


node_t *create_node(int id, char *label, int weight) {

	node_value_t *n = malloc(sizeof(node_value_t)); 
	n->counter = 1; // Keep track of nodes being created 
	n->weight = weight;
	n->label = NULL;  

	/* copy in string value if not NULL  */
	if(label != NULL) {
		size_t label_length = strlen(label) + 1;
		n->label = (char*)malloc(label_length * sizeof(char));
		strcpy(n->label, label);
	}

    node_t *node = malloc(sizeof(node_t));
    node->node_type = malloc(sizeof(node_type_t)); 
    node->node_type->node = n; 
    node->id = id; 
    node->next = NULL;
	node->right = NULL; 
	node->left = NULL; 
	return node; 
}


node_t *copy_node(node_t *node_value) {

	node_value_t *n = malloc(sizeof(node_value_t)); 
	n->counter = 0; // Keep track of nodes being created 
	n->weight = node_value->node_type->node->weight;
	size_t label_length = strlen(node_value->node_type->node->label) + 1;
	n->label = (char*)malloc(label_length * sizeof(char));
	strcpy(n->label, node_value->node_type->node->label);

    node_t *node = malloc(sizeof(node_t));
    node->node_type = malloc(sizeof(node_type_t)); 
    node->node_type->node = n; 
    node->id = node_value->id; 
    node->next = NULL;
	node->right = NULL; 
	node->left = NULL; 
	return node; 
}


void print_node(node_t *node) {
	printf("ID: %d, LABEL: %s ", node->id, node->node_type->node->label);
	if(node->node_type->node->weight > 0) {
		printf("WEIGHT: %d ", node->node_type->node->weight); 
	}
	printf("\n"); 
}


edge_t *create_edge(node_t *n1, node_t *n2, int weight) {
    edge_t *e;
    e = malloc(sizeof(edge_t));
    e->src = n1;
    e->dst = n2;
    e->weight = weight;
    return e;
}

void print_edge(edge_t *e) {
	printf("(%d -> %d) WEIGHT: %d\n", e->src->id, e->dst->id, e->weight); 
}
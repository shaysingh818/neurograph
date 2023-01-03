#include "includes/node.h"


node_t *create_node(int id, char label) {
	node_t *n;
	n = (node_t*)malloc(sizeof(node_t)); 
	n->id = id;  
	n->label = label; 
	n->next = NULL; 
	return n; 
}

void print_node(node_t *node) {
	printf("ID: %d, LABEL: %c\n", node->id, node->label); 
}


w_node_t *create_weighted_node(int id, int weight, char label) {
	w_node_t *n;
	n = (w_node_t*)malloc(sizeof(w_node_t)); 
	n->id = id;  
	n->label = label; 
	n->weight = weight; 
	n->next = NULL; 
	return n; 
}


void print_weighted_node(w_node_t *node) {
	printf("(%d, %c) WEIGHT: %d\n", node->id, node->label, node->weight); 
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

#include "includes/node.h"

node_t *init_variable(int id, void *value) {
    variable_t *variable = (variable_t*)malloc(sizeof(variable_t));
    variable->value = value;
    variable->label = NULL; 

  
    node_t *node = (node_t*)malloc(sizeof(node_t));
    node->node_type = (node_type_t*)malloc(sizeof(node_type_t)); 
    node->node_type->variable = variable; 
    node->id = id; 
    node->next = NULL; 
    return node; 
}


node_t *init_node_value(int id, char *label, int weight) {

	node_value_t *n = (node_value_t*)malloc(sizeof(node_value_t)); 
	n->counter = 1; // Keep track of nodes being created 
	n->weight = weight;
	n->label = NULL;  
	n->right = NULL; 
	n->left = NULL; 

    node_t *node = (node_t*)malloc(sizeof(node_t));
    node->node_type = (node_type_t*)malloc(sizeof(node_type_t)); 
    node->node_type->node = n; 
    node->id = id;
    node->next = NULL;  
    return node; 
}
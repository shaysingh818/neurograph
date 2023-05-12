#include "node.h"
#include <stdbool.h> 

void push_ll(node_t **head, node_t *new_node);
void insert_after_ll(node_t *prev_node, node_t *new_node); 
void append_ll(node_t **head, node_t *new_node); 
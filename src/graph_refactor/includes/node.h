#ifndef NODE_GEN_H
#define NODE_GEN_H

#include "node_types.h"


union NodeType {
    node_value_t *node; 
    variable_t *variable;
}; 

typedef union NodeType node_type_t; 


struct Node {
    int id;
    node_type_t *node_type;
    struct Node *next; 
};

typedef struct Node node_t; 


struct Edge {
    node_t *src;
    node_t *dst; 
    int weight; 
};

typedef struct Edge edge_t; 


/* Generic linked list of nodes */ 
struct NodeObjectList {
	node_t *head; 
}; 

typedef struct NodeObjectList node_obj_list_t;

/* node creation methods */
node_t *init_variable(int id, void *value);
node_t *init_node_value(int id, char *label, int weight);

#endif
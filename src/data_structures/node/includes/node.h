#ifndef NODE_H
#define NODE_H

#include <stdlib.h> 
#include <stdio.h> 
#include <string.h>
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
	struct Node* left; 
	struct Node* right;  
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


/* node  value methods */ 
node_t *create_node(int id, char *label, int weight); 
node_t *copy_node(node_t *node);
void print_node(node_t *node); 

/* edge methods */ 
edge_t* create_edge(node_t *n1, node_t *n2, int weight);
void print_edge(edge_t *e); 


#endif
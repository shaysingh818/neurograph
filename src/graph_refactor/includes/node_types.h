#ifndef NODE_TYPES_H
#define NODE_TYPES_H

#include <stdlib.h> 
#include <stdio.h> 
#include <string.h>

/* variable node type */
struct Variable {
	char *label;
	void *value;  
	void *(*forward)(void *val); 
	void *(*backward)(void *val);
};

typedef struct Variable variable_t;


/* Generic node */ 
struct NodeValue {
	int weight, counter; 
	char *label;
	struct NodeValue* left; 
	struct NodeValue* right;  
}; 

typedef struct NodeValue node_value_t;


#endif
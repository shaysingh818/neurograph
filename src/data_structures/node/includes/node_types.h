#ifndef NODE_TYPES_H
#define NODE_TYPES_H

#include <stdlib.h> 
#include <stdio.h> 
#include <string.h>

/* destructor and constructor funcs for value node*/
typedef void (*value_destructor)(void*);
typedef void (*value_constructor)(void*);

/* variable node type */
struct Variable {
	char *label;
	void *output;
	void *upstream_value;   
	void *(*forward)(void *val); 
	void *(*backward)(void *val);
	value_destructor value_destructor; 
	value_constructor value_constructor;	
};

typedef struct Variable variable_t;

/* Generic node */ 
struct NodeValue {
	int weight;
	int counter; 
	char *label;
}; 

typedef struct NodeValue node_value_t;


#endif
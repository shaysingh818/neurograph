#ifndef NODE_H
#define NODE_H

#include <stdlib.h> 
#include <stdio.h> 
#include <string.h>

/* Generic node */ 
struct Node {
	int id; 
	int weight; 
	char *label;
	struct Node* next; 
}; 

typedef struct Node node_t;

/* Generic linked list of nodes */ 
struct NodeList {
	node_t *head; 
}; 

typedef struct NodeList node_list_t; 


/* edge that stores relationship between two nodes */
struct Edge {
    node_t *src, *dest;
    int weight;
};

typedef struct Edge edge_t;


/* generic node methods */ 
node_t *create_node(int id, char *label, int weight); 
void print_node(node_t *node); 

/* edge methods */ 
edge_t* create_edge(node_t *n1, node_t *n2, int weight);
void print_edge(edge_t *e); 

#endif
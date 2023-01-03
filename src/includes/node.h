#ifndef NODE_H
#define NODE_H

#include <stdlib.h> 
#include <stdio.h> 

/* Unweighted node */
struct Node {
	int id;
	char label;
	struct Node* next; 
}; 

typedef struct Node node_t;

/* structure for storing a linked list of unweighted nodes */ 
struct NodeList {
	node_t *head; 
}; 

typedef struct NodeList node_list_t; 


/* Node structure with a weight value */ 
struct WeightedNode {
	int id; 
	int weight;
	char label;
   	struct WeightedNode* next; 	
}; 

typedef struct WeightedNode w_node_t; 


/* structure for storing a linked list of weighted nodes */ 
struct WeightedNodeList {
	w_node_t *head; 
}; 

typedef struct WeightedNodeList w_node_list_t; 


/* edge that stores relationship between two nodes */
struct Edge {
    node_t *src, *dest;
    int weight;
};

typedef struct Edge edge_t;


/* unweighted node methods */
node_t *create_node(int id, char label); 
void print_node(node_t *node);

/* weighted node methods */ 
w_node_t *create_weighted_node(int id, int weight, char label); 
void print_weighted_node(w_node_t *node); 

/* edge methods */ 
edge_t* create_edge(node_t *n1, node_t *n2, int weight);
void print_edge(edge_t *e); 

#endif



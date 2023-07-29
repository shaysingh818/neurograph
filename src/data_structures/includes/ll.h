#include "node.h"
#include <stdbool.h> 


struct UniqueLinkedList {
	char *value; 
	int index; 
	struct UniqueLinkedList *next; 
}; 

typedef struct UniqueLinkedList u_ll_t; 


struct MapList {
	int key; 
	struct MapList *next; 
}; 

typedef struct MapList ll_t; 


void push_ll(node_t **head, node_t *new_node);
void insert_after_ll(node_t *prev_node, node_t *new_node); 
void append_ll(node_t **head, node_t *new_node); 
int get_id_ll(node_t *head, char *key);
bool unique_append_ll(node_t **head, node_t *new_node);


/* unique linked list  methods */
u_ll_t *create_ull(char *set_key); 
int append(u_ll_t **head, char *set_key);
int pop_node(u_ll_t *head); 
int contains_value(u_ll_t *head, char *key);
int get_id(u_ll_t *head, char *key); 

void print_u_ll_t(u_ll_t *head); 
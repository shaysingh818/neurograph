#include "includes/ll.h"


void push_ll(node_t **head, node_t *new_node) {
    new_node->next = *(head); 
    *(head) = new_node; 
}

void insert_after_ll(node_t *prev_node, node_t *new_node) {

    if(prev_node == NULL){
        printf("Previous node cannot be NULL\n"); 
        return; 
    }

    new_node->next = prev_node->next; 
    prev_node->next = new_node; 
}

void append_ll(node_t **head, node_t *new_node) {

    node_t *last = *(head); 
    new_node->next = NULL; 

    if(*(head) == NULL) {
        *(head) = new_node; 
        return; 
    }

    while(last->next != NULL) {
        last = last->next; 
    }

    last->next = new_node; 
    return; 

}

int get_id_ll(node_t *head, char *key) {
	while(head != NULL) {
		int condition = strcmp(head->label, key) == 0; 
		if(condition) {
			return head->id; 
		}
		head = head->next; 
	}
	return false; 
}


bool unique_append_ll(node_t **head, node_t *new_node) {

    /* keep track of last node */
	node_t *last = *head;

	/* traverse till last node (This method will scale terribly) */
   	int counter = 0; 	
	while(last->next != NULL) {

		/* check if existing key is in list */ 
		int condition = strcmp(last->label, new_node->label) == 0; 
		if(condition) {
			return false; 
		}

		last = last->next; 
		counter += 1; 
	}

	/* adjust indices */ 
	new_node->id = counter + 1; 
	last->id = counter; 
	last->next = new_node;	

	if(*head == NULL) {
		*head = new_node; 
		return true; 
	}

	return true; 
}
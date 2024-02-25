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
		int condition = strcmp(head->node_type->node->label, key) == 0; 
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
		int condition = strcmp(last->node_type->node->label, new_node->node_type->node->label) == 0; 
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


u_ll_t *create_ull(char *set_key) {

	size_t key_size = strlen(set_key) + 1; 

	u_ll_t *new_node = (u_ll_t*)malloc(sizeof(u_ll_t));
	new_node->value = (char*)malloc(key_size * sizeof(char)); 
	strcpy(new_node->value, set_key);
	new_node->index = 0;
   	new_node->next = NULL;
	return new_node; 
}


int append(u_ll_t **head, char *set_key) {

	size_t key_size = strlen(set_key) + 1; 
	
	u_ll_t *last = *head;
	u_ll_t *new_node = (u_ll_t*)malloc(sizeof(u_ll_t)); 
	new_node->value = (char*)malloc(key_size * sizeof(char)); 
	strcpy(new_node->value, set_key);
   	new_node->next = NULL;

	/* traverse till last node (This method will scale terribly) */
   	int counter = 0; 	
	while(last->next != NULL) {

		/* check if existing key is in list */ 
		int condition = strcmp(last->value, set_key) == 0; 
		if(condition) {
			return false; 
		}

		last = last->next; 
		counter += 1; 
	}

	/* adjust indices */ 
	new_node->index = counter + 1; 
	last->index = counter; 
	last->next = new_node;	

	if(*head == NULL) {
		*head = new_node; 
		return true; 
	}

	return true; 
}


int get_id(u_ll_t *head, char *key) {
	while(head != NULL) {
		int condition = strcmp(head->value, key) == 0; 
		if(condition) {
			return head->index; 
		}
		head = head->next; 
	}
	return false; 
}


void print_u_ll_t(u_ll_t *head) {
	while(head != NULL) {
		printf("[%d] -> %s\n", head->index, head->value); 
		head = head->next; 
	}
}

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

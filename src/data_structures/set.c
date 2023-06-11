#include "includes/set.h"


set_t *init_set(bool set_order) {
	set_t *s = (set_t*)malloc(sizeof(set_t));
	s->root = NULL; 
    s->count = 0; 
    s->ordered = set_order; 
    s->queue = NULL; 
	return s; 
}

void set_insert(set_t *s, int data){
    if(s->root == NULL){
        s->root = push_set(s->root, data);
        s->count += 1;  
    } else {
        s->root = push_set(s->root, data); 
        s->count += 1; 
    }
}

void print_set(set_t *s) {
    s->queue = init_queue(s->count); 
    get_items(s->root, s->queue); 
	for(int i = s->queue->front_index; i <= s->queue->rear_index; i++) {
        printf("-> %d", s->queue->items[i]->integer); 
    }
} 

node_t *push_set(node_t *root, int data) {

    if(root == NULL){
        node_t *new_node = create_node(data, "", 0);
        return new_node;  
    }

    /* sort by left and right */
    if(root->id < data){
        root->right = push_set(root->right, data);
    } else if(root->id > data){
        root->left = push_set(root->left, data);
    }

    return root; 
}


void get_items(node_t *root, queue_t *q) {
    if(root == NULL){
        return; 
    }
    get_items(root->left, q);
    item_t *item = init_item(
        root->id, 
        root->label, 
        root->id,
        root
    ); 
    push(q, item); 
    get_items(root->right, q); 
} 
#include "includes/set.h"


set_t *init_set(bool set_order) {
	set_t *s = (set_t*)malloc(sizeof(set_t));
	s->root = NULL; 
    s->count = 0; 
    s->ordered = set_order; 
    s->queue = NULL; 
	return s; 
}


bool insert_ordered(set_t *s, int id, char *string_value, int weight) {

    /* keep track of last node */
    node_t *new_node = create_node(id, string_value, weight);
    node_t **head = &s->root; 

	if(*head == NULL) {
		*head = new_node; 
		return true; 
	}
	node_t *last = *head;
    node_t *prev = NULL;

	/* traverse till last node (This method will scale terribly) */
	while(last != NULL) {

        if(last->label != NULL){
		    /* check if existing key is in list */ 
		    int condition = strcmp(last->label, new_node->label); 
		    if(condition == 0) {
			    return false; 
		    } else if (condition > 0){
                prev->next = new_node;
                new_node->next = last;   
            }
        } else {
            if(last->id == new_node->id) {
                return false; 
            }
        }


        prev = last; 
		last = last->next; 
	}

	/* adjust indices */ 
	prev->next = new_node; 
	new_node->next = NULL;	
    s->count += 1; 
	return true; 

}

int get_value_ordered(set_t *s, char *key) {

    node_t **head = &s->root;
    node_t *last = *head;  

    if(last->label == NULL){
        printf("Set does not store character values\n"); 
        return false; 
    }

    int count = 0; 
    while(last != NULL){
        if(strcmp(last->label, key) == 0){
            return count; 
        }
        last = last->next;
        count += 1;  
    } 

    return 0; 
} 


void print_items_ordered(set_t *s){
    s->count = 0; 
    while(s->root != NULL) {
        if(s->root->label == NULL){
            printf("[%d] -> %d\n", s->count, s->root->id); 
        } else {
            printf("[%d] -> %s\n", s->count, s->root->label); 
        }
        s->root = s->root->next; 
        s->count += 1; 
    }
}


void get_items_ordered(set_t *s, queue_t *q) {

    node_t **head = &s->root;
    node_t *last = *head;  

    // if(last->label == NULL){
    //     printf("Set does not store character values\n");
    //     return;  
    // }

    int count = 0; 
    while(last != NULL){
        item_t *item = init_item(
            last->id, 
            last->label, 
            last->id,
            last
        ); 
        push(q, item);
        last = last->next;
    } 
} 


bool insert_sorted(set_t *s, int id, char *string_value, int weight) {
    node_t *new_node = create_node(id, string_value, weight);
    if(s->root == NULL){
        s->root = insert_set_value_sorted(s->root, new_node);
        s->count += 1;  
    } else {
        s->root = insert_set_value_sorted(s->root, new_node); 
        s->count += 1; 
    }
    return true;
}


node_t *insert_set_value_sorted(node_t *root, node_t *item) {

    /* check if root is null */
    if(root == NULL) {
        return item;
    } 

    /* if string value is present, sort lexographic, otherwise do numeric*/
    if(item->label != NULL){
        if(strcmp(root->label, item->label) > 0){
            root->right = insert_set_value_sorted(root->right, item);         
        } else if(strcmp(root->label, item->label) < 0) {
            root->left = insert_set_value_sorted(root->left, item); 
        }

    } else {
        if(root->id < item->id){
            root->right = insert_set_value_sorted(root->right, item);
        } else if(root->id > item->id){
            root->left = insert_set_value_sorted(root->left, item);
        }

    }

    return root; 
} 


int get_item_sorted(set_t *s, char *key) {
    queue_t *q = init_queue(s->count);
    get_items_sorted(s->root, q);
	for(int i = q->front_index; i <= q->rear_index; i++) {
        if(strcmp(q->items[i]->string, key) == 0){
            return i;
        }
    }
    return 0; 
} 


void get_items_sorted(node_t *root, queue_t *q) {
    if(root == NULL){
        return; 
    }
    get_items_sorted(root->left, q);
    item_t *item = init_item(
        root->id, 
        root->label, 
        root->id,
        root
    ); 
    push(q, item); 
    get_items_sorted(root->right, q); 
} 


void print_set_sorted(set_t *s) {
    s->queue = init_queue(s->count); 
    get_items_sorted(s->root, s->queue); 
	for(int i = s->queue->front_index; i <= s->queue->rear_index; i++) {
        printf("%s\n", s->queue->items[i]->string); 
    }
} 

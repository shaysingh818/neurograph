#include "includes/set.h"


ordered_set_t *init_array_set(int capacity) {

	ordered_set_t *s = (ordered_set_t*)malloc(sizeof(ordered_set_t));
    s->capacity = capacity; 
    s->rear = 0; 
    s->front = 0;
    s->used = 0; 

    /* allocate insert counts */
    s->insert_counts = malloc(capacity * sizeof(int));

    /* allocate items */
    s->items = malloc(s->capacity * sizeof(node_t*)); 
    for(int i = 0; i < s->capacity; i++){
        s->items[i] = malloc(sizeof(node_t)); 
    }

	return s; 
}


bool insert_ordered(ordered_set_t *s, int id, char *string_value, int weight) {

    /* check if we need to realloc */
    if(s->used == s->capacity){
        int new_size = s->capacity + s->capacity; 
        s->items = realloc(s->items, new_size * sizeof(node_t*));
        for(int i = s->capacity; i < new_size; i++){
            s->items[i] = malloc(sizeof(node_t)); 
        }
        s->capacity = new_size; 
    }

    node_t *item = create_node(id, string_value, weight); 
    if(item->node_type->node->label != NULL){
        for(int i = 0; i < s->used; i++){
           int compare = strcmp(s->items[i]->node_type->node->label, item->node_type->node->label) == 0; 
           if(compare == true){
                s->insert_counts[i] += 1; 
                return false; 
           }
        }
        s->items[s->used] = item; 
        s->used += 1;         
    } else {
        for(int i = 0; i < s->used; i++){
           if(s->items[i]->id == id){
                s->insert_counts[i] += 1; 
                return false; 
           }
        }
        s->items[s->used] = item; 
        s->used += 1;         
    }

    return true; 
}

int get_insert_count(ordered_set_t *s, node_t *item) {
    for(int i = 0; i < s->used; i++){
        if(s->items[i]->node_type->node->label != NULL){
            int compare = strcmp(s->items[i]->node_type->node->label, item->node_type->node->label) == 0; 
            if(compare){
                return s->insert_counts[i]; 
            }
        } else {
            if(s->items[i]->id == item->id){
                return s->insert_counts[i];
            }
        }
    }
    return 0; 
} 


int get_value_key(ordered_set_t *s, char *key) {

    for(int i = 0; i < s->used; i++){
        if(s->items[i]->node_type->node->label == NULL){
            printf("Set does not store char values\n"); 
            exit(0); 
        }

        int compare = strcmp(s->items[i]->node_type->node->label, key) == 0; 
        if(compare) return i; 
    } 

    return -1; 
}


int get_value_id(ordered_set_t *s, int id) {
    for(int i = 0; i < s->used; i++){
        if(s->items[i]->id == id){
            return i; 
        }
    } 
    return -1; 
} 


void print_items_ordered(ordered_set_t *s){
    for(int i = 0; i < s->used; i++){
        node_t *item = s->items[i]; 
        if(s->items[i]->node_type->node->label != NULL){
            printf("[%d] -> %s\n", item->id, item->node_type->node->label); 
        } else {
            printf("%d\n", item->id); 
        }
    }
}


set_t *init_set(bool set_order) {
    set_t *s = (set_t*)malloc(sizeof(set_t));
    s->root = NULL; 
    s->count = 0; 
    s->ordered = set_order; 
    s->queue = NULL; 
	return s; 
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
    if(item->node_type->node->label != NULL){
        if(strcmp(root->node_type->node->label, item->node_type->node->label) > 0){
            root->left = insert_set_value_sorted(root->left, item);
        } else if(strcmp(root->node_type->node->label, item->node_type->node->label) < 0) {
            root->right = insert_set_value_sorted(root->right, item);         
        }

    } else {
        if(root->id < item->id){
            root->left = insert_set_value_sorted(root->left, item);
        } else if(root->id > item->id){
            root->right = insert_set_value_sorted(root->right, item);
        }

    }
    return root; 
} 


int get_item_sorted(set_t *s, char *key) {
    queue_t *q = init_queue(s->count);
    get_items_sorted(s->root, q);
	for(int i = q->front_index; i <= q->rear_index; i++) {
        if(strcmp(q->items[i]->node_type->node->label, key) == 0){
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
    push(q, root); 
    get_items_sorted(root->right, q); 
} 


void print_set_sorted(set_t *s) {
    s->queue = init_queue(s->count); 
    get_items_sorted(s->root, s->queue); 
	for(int i = s->queue->front_index; i <= s->queue->rear_index; i++) {
        printf("%s\n", s->queue->items[i]->node_type->node->label); 
    }
} 
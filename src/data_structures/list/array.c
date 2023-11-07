#include "includes/array.h"

array_t *init_array() {
	array_t *a = (array_t*)malloc(sizeof(array_t));
    a->capacity = 2;
    a->insert_counts = 0; 
	a->front_index = a->item_count = 0; 
	a->rear_index = a->capacity - 1;
    a->items = malloc(a->capacity * sizeof(node_t*)); 
    for(int i = 0; i < a->capacity; i++){
        a->items[i] = malloc(sizeof(node_t)); 
    }
    return a;  
}

void insert(array_t *a, node_t *item){
    if(a->item_count == a->capacity){
        int new_capacity = a->capacity + a->capacity; 
        a->items = realloc(a->items, new_capacity * sizeof(node_t*)); 
        for(int i = a->capacity; i < new_capacity; i++){
            a->items[i] = malloc(sizeof(node_t)); 
        }
        a->capacity = new_capacity; 
    }

	a->rear_index = (a->rear_index+1) % a->capacity; 
	a->items[a->rear_index] = item; 
    a->item_count += 1; 
}


void insert_char(array_t *a, char *item){
    if(a->item_count == a->capacity){
        int new_capacity = a->capacity + a->capacity; 
        a->items = realloc(a->items, new_capacity * sizeof(node_t*)); 
        for(int i = a->capacity; i < new_capacity; i++){
            a->items[i] = malloc(sizeof(node_t)); 
        }
        a->capacity = new_capacity; 
    }

	a->rear_index = (a->rear_index+1) % a->capacity; 
	a->items[a->rear_index] = create_node(a->item_count, item, a->rear_index); 
    a->item_count += 1; 
}


void remove_char(array_t *a, char *item) {

    int remove_index; 
    for(int i = 0; i < a->item_count; i++){
        bool compare = strcmp(a->items[i]->label, item) == 0; 
        if(compare){
            if(i != a->item_count){
                free(a->items[i]->label);
                free(a->items[i]);
            }
            remove_index = i; 
            break;
        }
    }

    /* shift */
    for(int i = remove_index; i < a->item_count; i++){
        a->items[i] = a->items[i+1]; 
    }
    a->item_count -= 1; 
} 


void pop_array(array_t *a) {
    if(a->item_count == 0) return;
	a->front_index = (a->front_index + 1) % a->capacity; 
	a->item_count = a->item_count - 1; 
}


void print_array(array_t *a){
    for(int i = 0; i < a->item_count; i++){
        printf(
            "[%d] -> (%d, %s)\n", 
            i, a->items[i]->id, a->items[i]->label
        ); 
    } 
}
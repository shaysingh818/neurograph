#ifndef SET_H
#define SET_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <limits.h>
#include "../../queue/includes/queue.h"


struct Set {
    node_t *root;
    queue_t *queue;  
    bool ordered; 
    int count; 
    int *items;  
};

typedef struct Set set_t; 


struct OrderedSet {
    int capacity, used, front, rear; 
    int *insert_counts;  
    node_t **items; 
}; 

typedef struct OrderedSet ordered_set_t; 


/* ordered array based set methods */
ordered_set_t *init_array_set(int capacity);
bool insert_ordered(ordered_set_t *s, int id, char *string_value, int weight);
int get_insert_count(ordered_set_t *s, node_t *item);
int get_value_id(ordered_set_t *s, int id); 
int get_value_key(ordered_set_t *s, char *key);
void print_items_ordered(ordered_set_t *s);


/* ordered set methods */

set_t *init_set(bool set_order);
bool insert_sorted(set_t *s, int id, char *string_value, int weight);
node_t *insert_set_value_sorted(node_t *root, node_t *item);
int get_item_sorted(set_t *s, char *key); 
void get_items_sorted(node_t *root, queue_t *q);
void print_set_sorted(set_t *s); 



#endif
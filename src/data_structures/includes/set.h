#ifndef SET_H
#define SET_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <limits.h>
#include "queue.h"


struct Set {
    node_t *root;
    queue_t *queue;  
    bool ordered; 
    int count; 
    int *items;  
};

typedef struct Set set_t; 


/* set methods */
set_t *init_set(bool set_order);

/* unordered set methods */
bool insert_ordered(set_t *s, int id, char *string_value, int weight);
bool insert_set_value_ordered(node_t **root, node_t *item);
int get_value_ordered(set_t *s, char *key);  
void print_items_ordered(set_t *s);
void get_items_ordered(set_t *s, queue_t *q);  

/* ordered set methods */
bool insert_sorted(set_t *s, int id, char *string_value, int weight);
node_t *insert_set_value_sorted(node_t *root, node_t *item);
int get_item_sorted(set_t *s, char *key); 
void get_items_sorted(node_t *root, queue_t *q);
void print_set_sorted(set_t *s); 

#endif
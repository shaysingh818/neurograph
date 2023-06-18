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
void set_insert(set_t *s, int data);
void print_set(set_t *s); 

node_t *push_set(node_t *root, int data);
void get_items(node_t *root, queue_t *q); 

#endif
#ifndef ARRAY_H
#define ARRAY_H

#include <stdlib.h>
#include <string.h> 
#include <stdio.h>
#include <unistd.h>
#include <stdbool.h>
#include "node.h" 

struct Array {
    int capacity, used, front_index, rear_index, item_count; 
    int *insert_counts;  
    node_t **items; 
};

typedef struct Array array_t; 

array_t *init_array();
void insert(array_t *a, node_t *item);
void remove_array_item(array_t *a, int index);  
void pop_array(array_t *a);
void print_array(array_t *a);   

#endif
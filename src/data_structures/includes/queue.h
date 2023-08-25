#ifndef QUEUE_H
#define QUEUE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <limits.h>
#include "node.h"


struct Queue {
	unsigned capacity; 
	int front_index, rear_index, item_count;
	node_t* front, rear; 
	node_t **items; 
}; 

typedef struct Queue queue_t;


/* structural methods */
queue_t *init_queue(unsigned capacity);

/* shared methods */
int is_full(queue_t* q);
int is_empty(queue_t* q);

int front(queue_t* q);
int rear(queue_t *q);

/* insertion methods */
void push(queue_t *q, node_t *item); 

/* deletion methods */
void pop(queue_t *q);

/* printer methods */
void print_queue(queue_t *q); 


#endif
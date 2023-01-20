#include "includes/queue.h"


queue_t *init_queue(unsigned capacity) {
	
	queue_t *q = (queue_t*)malloc(sizeof(queue_t)); 
	q->capacity = capacity; 
	q->front_index = q->item_count = 0; 
	q->rear_index = capacity - 1; 

	q->items = malloc(q->capacity * sizeof(node_t*)); 
	for(int i = 0; i < q->capacity; i++){
		q->items[i] = malloc(sizeof(node_t)); 
	}

	return q; 
}



int front(queue_t* q){
	if(is_empty(q)) {
		return INT_MIN; 
	}
	return q->front_index; 
}


int rear(queue_t* q){
	if(is_empty(q)) {
		return INT_MIN; 
	}
	return q->rear_index; 
}


int is_full(queue_t* q) {
	return (q->item_count == q->capacity); 
}

int is_empty(queue_t* q) {
	return (q->item_count == 0); 
}


void push(queue_t *q, node_t *n) {
	
	if(is_full(q)) {
		return; 
	}

	q->rear_index = (q->rear_index+1) % q->capacity; 
	q->items[q->rear_index] = n; 
	q->item_count = q->item_count + 1; 
}


void pop(queue_t * q) {

	if(is_empty(q)) {
		return; 
	}

	node_t *item = q->items[q->front_index]; 
	q->front_index = (q->front_index + 1) % q->capacity; 
	q->item_count = q->item_count - 1; 
}


void print_queue(queue_t *q) {
	for(int i = q->front_index; i <= q->rear_index; i++) {
		printf("%s ", q->items[i]->label); 
	}
	printf("\n"); 
}

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


item_t *init_item(int integer, char *string, int priority, node_t *node) {
	
	item_t *item = (item_t*)malloc(sizeof(item_t)); 
	item->integer = integer;
   	item->priority = priority; 	
	item->string = NULL;
	item->node = node;

	/* copy in string value if not NULL  */
	if(string != NULL) {
		size_t string_size = strlen(string) + 1; 
		item->string = (char*)malloc(string_size * sizeof(char));
		strcpy(item->string, string); 
	} 

	return item; 
}


int is_full(queue_t* q) {
	return (q->item_count == q->capacity); 
}


int is_empty(queue_t* q) {
	return (q->item_count == 0); 
}


/* shared methods */ 
int front(queue_t* q){
	if(is_empty(q)) {
		INT_MIN; 
	}
	return q->front_index; 
}


int rear(queue_t* q){
	if(is_empty(q)) {
		return INT_MIN; 
	}
	return q->rear_index; 
}


/* insertion methods */ 
void push(queue_t *q, item_t *item) {
	
	if(is_full(q)) {
		return; 
	}

	q->rear_index = (q->rear_index+1) % q->capacity; 
	q->items[q->rear_index] = item; 
	q->item_count = q->item_count + 1; 
}


/* deletion methods */ 
void pop(queue_t * q) {

	if(is_empty(q)) {
		return; 
	}

	q->front_index = (q->front_index + 1) % q->capacity; 
	q->item_count = q->item_count - 1; 
}


/* printing methods */
void print_queue_item(item_t *item) {
	printf("Integer: %d\n", item->integer);
	printf("String: %s\n", item->string); 
	printf("Priority: %d\n", item->priority);
   	printf("=================================\n"); 	
}

void print_queue(queue_t *q) {	
	for(int i = q->front_index; i <= q->rear_index; i++) {
		print_queue_item(q->items[i]); 
	}
	printf("\n"); 
}
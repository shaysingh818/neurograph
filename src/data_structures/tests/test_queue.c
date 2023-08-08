
#include "includes/test_queue.h"


void test_init_queue(){

	int count = 5; 
	bool equality_status = true; 

	/* create nodes */ 
    item_t *item1 = init_item(1, "String Item 1", 0, NULL);  
    item_t *item2 = init_item(2, "String Item 2 ", 0, NULL); 
    item_t *item3 = init_item(3, "String Item 3 ", 0, NULL); 
    item_t *item4 = init_item(4, "String Item 4", 0, NULL); 
    item_t *item5 = init_item(5, "String Item 5", 0, NULL); 

    /* test if queue works */ 
    queue_t *q = init_queue(count); 
    push(q, item1);
    push(q, item2); 
    push(q, item3); 
    push(q, item4); 
    push(q, item5);
	assert(q->item_count == count); 

	if(!equality_status) {
		printf("%s::%s... FAILED\n", __FILE__, __FUNCTION__); 
	} else {
		printf("%s::%s... \e[0;32mPASSED\e[0m\n", __FILE__, __FUNCTION__);
	}
}

void test_is_full() {

	int count = 5; 
	bool equality_status = true; 

	/* create nodes */ 
    item_t *item1 = init_item(1, "String Item 1", 0, NULL);  
    item_t *item2 = init_item(2, "String Item 2 ", 0, NULL); 
    item_t *item3 = init_item(3, "String Item 3 ", 0, NULL); 
    item_t *item4 = init_item(4, "String Item 4", 0, NULL); 
    item_t *item5 = init_item(5, "String Item 5", 0, NULL); 

    /* test if queue works */ 
    queue_t *q = init_queue(count); 
    push(q, item1);
    push(q, item2); 
    push(q, item3); 
    push(q, item4);

	/* should not be full at this point */
	bool result = is_full(q);
	assert(result == false); 

	/* last insert here makes it full*/
    push(q, item5);

	result = is_full(q);
	assert(result == true);  

	if(!equality_status) {
		printf("%s::%s... FAILED\n", __FILE__, __FUNCTION__); 
	} else {
		printf("%s::%s... \e[0;32mPASSED\e[0m\n", __FILE__, __FUNCTION__);
	}

}

void test_is_empty(){

	int count = 5; 
	bool equality_status = true; 

	/* create nodes */ 
    item_t *item1 = init_item(1, "String Item 1", 0, NULL);  
    item_t *item2 = init_item(2, "String Item 2 ", 0, NULL); 
    item_t *item3 = init_item(3, "String Item 3 ", 0, NULL); 
    item_t *item4 = init_item(4, "String Item 4", 0, NULL); 
    item_t *item5 = init_item(5, "String Item 5", 0, NULL); 

    /* test if queue works */ 
    queue_t *q = init_queue(count); 
    push(q, item1);
    push(q, item2); 
    push(q, item3); 
    push(q, item4);

	for(int i = 0; i < count; i++){
		pop(q); 
	}

	bool result = is_empty(q);
	assert(result == true); 

	if(!equality_status) {
		printf("%s::%s... FAILED\n", __FILE__, __FUNCTION__); 
	} else {
		printf("%s::%s... \e[0;32mPASSED\e[0m\n", __FILE__, __FUNCTION__);
	}

}

void test_front_rear() {

	int count = 5; 
	bool equality_status = true; 

	/* create nodes */ 
    item_t *item1 = init_item(1, "String Item 1", 0, NULL);  
    item_t *item2 = init_item(2, "String Item 2 ", 0, NULL); 
    item_t *item3 = init_item(3, "String Item 3 ", 0, NULL); 
    item_t *item4 = init_item(4, "String Item 4", 0, NULL); 
    item_t *item5 = init_item(5, "String Item 5", 0, NULL); 

    /* test if queue works */ 
    queue_t *q = init_queue(count); 
    push(q, item1);
    push(q, item2); 
    push(q, item3); 
    push(q, item4);
    push(q, item5);

	int front_index = front(q); 
	int rear_index = rear(q); 

	bool front_condition = q->items[front_index]->integer == 1; 
	bool rear_condition = q->items[rear_index]->integer == 5;
	assert(front_condition == true && rear_condition == true);  

	if(!equality_status) {
		printf("%s::%s... FAILED\n", __FILE__, __FUNCTION__); 
	} else {
		printf("%s::%s... \e[0;32mPASSED\e[0m\n", __FILE__, __FUNCTION__);
	}

}
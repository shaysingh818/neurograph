
#include "includes/test_queue.h"


void test_init_queue(){

	int count = 5; 
	bool equality_status = true; 

	/* create nodes */ 
    node_t *item1 = create_node(1, "String Item 1", 0);  
    node_t *item2 = create_node(2, "String Item 2 ", 0); 
    node_t *item3 = create_node(3, "String Item 3 ", 0); 
    node_t *item4 = create_node(4, "String Item 4", 0); 
    node_t *item5 = create_node(5, "String Item 5", 0); 

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
    node_t *item1 = create_node(1, "String Item 1", 0);  
    node_t *item2 = create_node(2, "String Item 2 ", 0); 
    node_t *item3 = create_node(3, "String Item 3 ", 0); 
    node_t *item4 = create_node(4, "String Item 4", 0); 
    node_t *item5 = create_node(5, "String Item 5", 0); 


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
    node_t *item1 = create_node(1, "String Item 1", 0);  
    node_t *item2 = create_node(2, "String Item 2 ", 0); 
    node_t *item3 = create_node(3, "String Item 3 ", 0); 
    node_t *item4 = create_node(4, "String Item 4", 0); 
    node_t *item5 = create_node(5, "String Item 5", 0); 

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
    node_t *item1 = create_node(1, "String Item 1", 0);  
    node_t *item2 = create_node(2, "String Item 2 ", 0); 
    node_t *item3 = create_node(3, "String Item 3 ", 0); 
    node_t *item4 = create_node(4, "String Item 4", 0); 
    node_t *item5 = create_node(5, "String Item 5", 0); 

    /* test if queue works */ 
    queue_t *q = init_queue(count); 
    push(q, item1);
    push(q, item2); 
    push(q, item3); 
    push(q, item4);
    push(q, item5);

	int front_index = front(q); 
	int rear_index = rear(q); 

	bool front_condition = q->items[front_index]->id == 1; 
	bool rear_condition = q->items[rear_index]->id == 5;
	assert(front_condition == true && rear_condition == true);  

	if(!equality_status) {
		printf("%s::%s... FAILED\n", __FILE__, __FUNCTION__); 
	} else {
		printf("%s::%s... \e[0;32mPASSED\e[0m\n", __FILE__, __FUNCTION__);
	}

}
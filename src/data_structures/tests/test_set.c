#include "includes/test_set.h"

void test_set() {

    /* expected behavior */
    int expected_items[4] = {1, 2, 3, 4};  
    bool equality_status = true; 

    /* init instance of set */
    set_t *s = init_set(true);
    set_insert(s, 1);  
    set_insert(s, 2);  
    set_insert(s, 3);  
    set_insert(s, 4);  
    set_insert(s, 1);  

    /* retrieve values and store in queue  */
    queue_t *q = init_queue(s->count); 
    get_items(s->root, q);

	for(int i = q->front_index; i <= q->rear_index; i++) {
        if(q->items[i]->integer != expected_items[i]){
            equality_status = false; 
        }        
    }

	if(!equality_status) {
		printf("%s::%s... FAILED\n", __FILE__, __FUNCTION__); 
	} else {
		printf("%s::%s... \e[0;32mPASSED\e[0m\n", __FILE__, __FUNCTION__);
	}

}
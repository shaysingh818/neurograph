
#include "includes/queue_test.h"

void test_init_queue(){

	/* create nodes */ 
    node_t *node1 = create_node(1, 'A'); 
    node_t *node2 = create_node(2, 'B'); 
    node_t *node3 = create_node(3, 'C'); 
    
    /* test if queue works */ 
    queue_t *q = init_queue(5); 
    push(q, node1); 
    push(q, node2); 
    push(q, node3);

	/* scan results and check against queue */ 
	int result = TRUE; 
	int queue_results[3] = {1,2,3}; 
	for(int i = q->front_index; i <= q->rear_index; i++){
		if(q->items[i]->id != queue_results[i]) {
			result = FALSE; 
		}
	}	

	/* validate results */
    if(!result) {
        printf("%s::%s... FAILED\n", __FILE__, __FUNCTION__);
    }
    printf("%s::%s... \e[0;32mPASSED\e[0m\n", __FILE__, __FUNCTION__);

}


void test_pop_queue(){

	/* create nodes */ 
    node_t *node1 = create_node(1, 'A'); 
    node_t *node2 = create_node(2, 'B'); 
    node_t *node3 = create_node(3, 'C'); 
    
    /* test if queue works */ 
    queue_t *q = init_queue(5); 
    push(q, node1); 
    push(q, node2); 
    push(q, node3);

	/* pop queue */ 
	pop(q); 

	/* scan results and check against queue */ 
	int result = TRUE;
   	int result_index = 0; 	
	char queue_results[2] = {'B','C'}; 
	for(int i = q->front_index; i <= q->rear_index; i++){
		if(q->items[i]->label != queue_results[result_index]) {
			result = FALSE; 
		}
		result_index += 1; 
	}


	/* validate results */
    if(!result) {
        printf("%s::%s... FAILED\n", __FILE__, __FUNCTION__);
    }
    printf("%s::%s... \e[0;32mPASSED\e[0m\n", __FILE__, __FUNCTION__);

}

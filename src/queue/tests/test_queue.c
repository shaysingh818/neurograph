
#include "includes/test_queue.h"
#include "../..//includes/queue.h"


void test_init_queue(){

	/* create nodes */ 
    node_t *node1 = create_node(1, "A", 0); 
    node_t *node2 = create_node(2, "B", 0); 
    node_t *node3 = create_node(3, "C", 0); 
    
    /* test if queue works */ 
    queue_t *q = init_queue(5); 
    push(q, node1); 
    push(q, node2); 
    push(q, node3);

	/* scan results and check against queue */ 
	int result = true; 
	int queue_results[3] = {1,2,3}; 
	for(int i = q->front_index; i <= q->rear_index; i++){
		if(q->items[i]->id != queue_results[i]) {
			result = false; 
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
    node_t *node1 = create_node(1, "A", 0); 
    node_t *node2 = create_node(2, "B", 0); 
    node_t *node3 = create_node(3, "C", 0); 
    
    /* test if queue works */ 
    queue_t *q = init_queue(5); 
    push(q, node1); 
    push(q, node2); 
    push(q, node3);

	/* pop queue */ 
	pop(q); 

	/* scan results and check against queue */ 
	int result = true;
   	int result_index = 0; 	
	char *queue_results[2] = {"B","C"}; 
	for(int i = q->front_index; i <= q->rear_index; i++){
		int condition = strcmp(q->items[i]->label, queue_results[result_index]);
		if(condition != 0) {
			result = false; 
		}
		result_index += 1; 
	}


	/* validate results */
    if(!result) {
        printf("%s::%s... FAILED\n", __FILE__, __FUNCTION__);
    }
    printf("%s::%s... \e[0;32mPASSED\e[0m\n", __FILE__, __FUNCTION__);

}


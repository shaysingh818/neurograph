#include "includes/queue.h"


int main(int argc, char **argv) {

	/* create nodes */ 
    node_t *node1 = create_node(1, "A", 0); 
    node_t *node2 = create_node(2, "B", 0); 
    node_t *node3 = create_node(3, "C", 0); 
    
    /* test if queue works */ 
    queue_t *q = init_queue(5); 
    push(q, node1); 
    push(q, node2); 
    push(q, node3);
}

cimport libneurograph.data_structures.cnode as node

cdef extern from "<neurograph/data_structures/queue/includes/queue.h>":

    struct Queue:
        int capacity
        int used
        int front_index
        int rear_index
        int item_count
        node.Node *front
        node.Node *rear
        node.Node **items

    Queue *init_queue(int capacity)
    int is_full(Queue *q)
    int is_empty(Queue *q)
    int front(Queue *q) 
    int rear(Queue *q)
    void push(Queue *q, node.Node *item)
    void print_queue(Queue *q)   
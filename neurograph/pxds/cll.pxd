cimport pxds.cnode

cdef extern from "../src/data_structures/list/includes/array.h":

    struct Array:
        int capacity
        int used
        int front_index
        int rear_index
        int item_count
        int *insert_counts
        pxds.cnode.Node **items

    Array *init_array();
    void insert(Array *a, pxds.cnode.Node *item);
    void insert_char(Array *a, char *item); 
    void remove_array_item(Array *a, int index);  
    void pop_array(Array *a);
    void print_array(Array *a);   
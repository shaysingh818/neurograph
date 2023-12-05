cimport libneurograph.data_structures.cqueue as queue
cimport libneurograph.data_structures.cnode as node

cdef extern from "<data_structures/set/includes/set.h>":

    struct Set:
        node.Node *root
        queue.Queue *queue
        bint ordered
        int count
        int *items

    struct OrderedSet:
        int capacity
        int used
        int rear
        int *insert_counts
        node.Node **items

    OrderedSet *init_array_set(int capacity)
    bint insert_ordered(OrderedSet *s, int id, char *string_value, int weight);
    int get_insert_count(OrderedSet *s, node.Node *item);
    int get_value_id(OrderedSet *s, int id); 
    int get_value_key(OrderedSet *s, char *key);
    void print_items_ordered(OrderedSet *s);


    Set *init_set(bint set_order);
    bint insert_sorted(Set *s, int id, char *string_value, int weight);
    node.Node *insert_set_value_sorted(node.Node *root, node.Node *item);
    int get_item_sorted(Set *s, char *key); 
    void get_items_sorted(node.Node *root, queue.Queue *q);
    void print_set_sorted(Set *s); 
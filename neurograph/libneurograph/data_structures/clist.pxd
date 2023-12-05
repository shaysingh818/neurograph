cimport libneurograph.data_structures.cnode as node

cdef extern from "<data_structures/list/includes/array.h>":

    struct Array:
        int capacity
        int used
        int front_index
        int rear_index
        int item_count
        int *insert_counts
        node.Node **items

    Array *init_array()
    void insert(Array *a, node.Node *item)
    void insert_char(Array *a, char *item)
    void remove_char(Array *a, char *item) 
    void remove_array_item(Array *a, int index)
    void pop_array(Array *a)
    void print_array(Array *a)   


cdef extern from "<data_structures/list/includes/adj_list.h>":

    struct AdjacencyList:
        int v
        int e
        int *visited
        int *used
        bint directed
        bint err
        node.Edge **edges
        node.NodeList **items

    AdjacencyList *init_adj_list(int v, int e, bint directed);
    AdjacencyList *transpose_items(AdjacencyList *g, AdjacencyList *r); 

    int add_node(
        AdjacencyList *g, int src_id, char *src_label, 
        int dest_id, char *dest_label, int weight
    ); 

    int add_end_node(AdjacencyList *g, int src_id, char *src_label, int weight);
    int push_unweighted_node(AdjacencyList *g, char *src, char *dst); 
    int push_weighted_node(AdjacencyList *g, char *src, char *dst, int weight);
    node.Node *get_node_by_id(AdjacencyList *g, int id);
    void resize_adj_list(AdjacencyList *g, int new_size);  
    void print_graph(AdjacencyList *g);

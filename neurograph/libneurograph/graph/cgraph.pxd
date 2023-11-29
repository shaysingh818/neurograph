cimport libneurograph.data_structures.cnode as node
cimport libneurograph.data_structures.clist as arraylist
cimport libneurograph.data_structures.cset as setlist
cimport libneurograph.data_structures.cmatrix as matrix
cimport libneurograph.extractors.cframe as frame

cdef extern from "<neurograph/graph/includes/graph.h>":

    struct Walk:
        int *path
        int steps
        int weighted_sum
        int cycles

    struct Graph:
        int vertices
        int edges
        char *filename
        bint directed
        arraylist.AdjacencyList *list
        matrix.AdjacencyMatrix *matrix
        Walk *walk

    
    Graph *init_graph(int v, int e, bint directed); 
    Walk *init_walk(int steps);
    matrix.AdjacencyMatrix *to_matrix(matrix.AdjacencyMatrix *m, arraylist.AdjacencyList *g, bint directed);
    arraylist.AdjacencyList *to_list(arraylist.AdjacencyList *g, matrix.AdjacencyMatrix *m, bint directed);

    void remove_unused_slots(Graph *g); 
    void label_node(Graph *g, int index, int label); 
    void print_graph_list(Graph *g); 
    void print_graph_matrix(Graph *g);
    void print_graph_walk(Graph *g); 
    void print_walk(Walk *w);

    Graph *frame_to_unweighted_graph(frame.Frame *frame, arraylist.Array *cols, bint directed);
    Graph *frame_to_weighted_graph(frame.Frame *frame, arraylist.Array *cols, bint directed); 
    int get_max_vertex_count(char *filename, int file_size); 
    setlist.Set *get_graph_node_ids(Graph *g); 
    setlist.OrderedSet *get_graph_nodes(Graph *g); 
    setlist.Set *get_graph_node_ids_file(char *filename, int file_size); 
    setlist.Set *get_graph_nodes_from_file(char *filename, int file_size);
    Graph *serialize_graph_list(char *filename, int file_size, bint directed); 
    Graph *serialize_graph_list_sorted_label(char *filename, int file_size);
    void deserialize_graph_list(Graph *list, char *filename); 
    Graph *serialize_mat_graph(char *filename, int file_size);
    void deserialize_mat_graph(Graph *mat); 

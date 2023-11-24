from pxds.data_structures.cnode import Node
from pxds.data_structures.clist import AdjacencyList, Array
from pxds.data_structures.cset import Set, OrderedSet
from pxds.data_structures.cmatrix import Matrix
from pxds.extractors.cframe import Frame

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
        AdjacencyList *list
        AdjacencyMatrix *matrix
        Walk *walk

    
    Graph *init_graph(int v, int e, bool directed); 
    Walk *init_walk(int steps);
    AdjacencyMatrix *to_matrix(AdjacencyMatrix *m, AdjacencyList *g, bool directed);
    AdjacencyList *to_list(AdjacencyList *g, AdjacencyMatrix *m, bool directed);

    void remove_unused_slots(Graph *g); 
    void label_node(Graph *g, int index, int label); 
    void print_graph_list(Graph *g); 
    void print_graph_matrix(Graph *g);
    void print_graph_walk(Graph *g); 
    void print_walk(Walk *w);

    Graph *frame_to_unweighted_graph(Frame *frame, Array *cols, bool directed);
    Graph *frame_to_weighted_graph(Frame *frame, Array *cols, bool directed); 
    int get_max_vertex_count(char *filename, int file_size); 
    Set *get_graph_node_ids(Graph *g); 
    OrderedSet *get_graph_nodes(Graph *g); 
    Set *get_graph_node_ids_file(char *filename, int file_size); 
    Set *get_graph_nodes_from_file(char *filename, int file_size);
    Graph *serialize_graph_list(char *filename, int file_size, bool directed); 
    Graph *serialize_graph_list_sorted_label(char *filename, int file_size);
    void deserialize_graph_list(Graph *list, char *filename); 
    Graph *serialize_mat_graph(char *filename, int file_size);
    void deserialize_mat_graph(Graph *mat); 

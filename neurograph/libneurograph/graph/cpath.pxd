
cimport libneurograph.data_structures.cnode as node
cimport libneurograph.data_structures.cmatrix as matrix
cimport libneurograph.graph.cgraph as graph

cdef extern from "<neurograph/graph/includes/path.h>":

    int *bellman_ford_list(graph.Graph *g, node.Node *root, int *dist); 
    int *dijkstra_list(graph.Graph *g, int start_vertex);
    int shortest_path_list(graph.Graph *g, int start_vertex, int end_vertex);  
    graph.Walk *random_walk_list(graph.Graph *g, int start_vertex, int steps); 
    graph.Walk *weighted_random_walk_list(graph.Graph *g, int start_vertex, int steps);

    graph.Walk *random_walk_mat(graph.Graph *m, int start_vertex, int steps);
    int *dijkstra_mat(graph.Graph *m, int start_vertex); 
    int shortest_path_mat(graph.Graph *m, int start_vertex, int end_vertex); 
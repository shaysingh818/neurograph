
cimport libneurograph.data_structures.cnode as node
cimport libneurograph.data_structures.cmatrix as matrix
cimport libneurograph.graph.cgraph as graph

cdef extern from "<graph/includes/community.h>":

    int degree_centrality_list(graph.Graph *g, node.Node *root);
    int weighted_degree_centrality_list(graph.Graph *g); 
    float closeness_centrality_list(graph.Graph *g, int vertex);
    float normalized_closeness_centrality_list(graph.Graph *g, int vertex); 
    int page_rank_list(graph.Graph *g, node.Node *root); 
    int **kosaraju_list(graph.Graph *g, int start_vertex);
    int max_label_occurrence(graph.Graph *g, int node_id, node.Node *root);
    int *label_propagator_list(graph.Graph *g, int *labels, int start_vertex);
    int *label_propagation_iterative_list(graph.Graph *g, int start_vertex); 
    int triangle_count_list(graph.Graph *g, int vertex); 

    int *degree_centrality_mat(graph.Graph *m);
    matrix.Matrix *label_nodes_mat(graph.Graph *m, int labels[]); 
    matrix.Matrix *label_propogation_mat(matrix.Matrix *A, int iterations); 
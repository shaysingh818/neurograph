cimport libneurograph.data_structures.cnode as node
cimport libneurograph.graph.cgraph as graph
cimport libneurograph.data_structures.cqueue as queue

cdef extern from "<graph/includes/search.h>":

    queue.Queue *bfs(graph.Graph *g, node.Node *root); 
    int dfs(queue.Queue *q, graph.Graph *g, node.Node *root);
    int k_dfs(queue.Queue *q, graph.Graph *g, node.Node *root);  
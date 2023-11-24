cimport libneurograph.data_structures.cnode as node

cdef extern from "<neurograph/data_structures/matrix/includes/matrix.h>":

    struct Matrix:
        int rows
        int cols
        double **arr
    
    Matrix *init_vec(int rows, int cols, bint identity)
    Matrix *init_matrix(int rows, int cols)
    Matrix *copy_matrix(Matrix *m) 
    Matrix *copy_matrix_values(Matrix *m, Matrix *n)
    void print_vec(Matrix *m) 


cdef extern from "<neurograph/data_structures/matrix/includes/adj_mat.h>":

    struct AdjacencyMatrix:
        int v
        int e
        int *visited
        int *used
        bint directed
        bint err
        Matrix *weights
        node.Node  *items

    AdjacencyMatrix *init_adj_mat(int v, int e, bint directed)
    void add_node_mat(
        AdjacencyMatrix *m, int src_id, char *src, 
        int dst_id, char *dst, double weight
    )

    AdjacencyMatrix *transpose_items_mat(AdjacencyMatrix *m, AdjacencyMatrix *r); 
    node.Node *search_node_by_id_mat(AdjacencyMatrix *m, int id);
    void print_adj_mat(AdjacencyMatrix *m); 
    


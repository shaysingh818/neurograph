cimport libneurograph.data_structures.cnode as node

cdef extern from "<data_structures/matrix/includes/matrix.h>":

    struct Matrix:
        int rows
        int cols
        double **arr
    
    Matrix *init_vec(int rows, int cols, bint identity)
    Matrix *init_matrix(int rows, int cols)
    Matrix *apply(double(*activation_function)(double), Matrix *m)  
    Matrix *copy_matrix(Matrix *m)
    Matrix *load_matrix(char *filename)
    Matrix **to_rows(Matrix *m)
    Matrix **to_cols(Matrix *m)
    Matrix **batch_rows(Matrix *m, int limit)
    Matrix **batch_matrix(Matrix *m, int batch_size)

    bint compare_matrix(Matrix *m, Matrix *n)
    double uniform_distribution(double low, double high)
    void copy_mat(Matrix *v1, Matrix *v2)
    void print_vec(Matrix *v1)
    void matrix_free(Matrix *m)
    void randomize(Matrix *mat, int n) 
    void print_matrix(Matrix *mat)
    void fill_mat(Matrix *m, int n)
    void save_matrix(Matrix *m, char *filename)  
    void copy_matrix_values(Matrix *m, Matrix *n)
    void entry(Matrix *m, int row, int col, double value)

    Matrix *scalar_multiply(Matrix *v1, double value)
    Matrix *power(Matrix *v1, int power)
    Matrix *dot(Matrix *n, Matrix *m)
    Matrix *multiply(Matrix *v1, Matrix *v2)
    Matrix *elementwise_multiply(Matrix *v1, Matrix *v2) 
    Matrix *add(Matrix *n, Matrix *m)
    Matrix *scale(Matrix *v, double value)
    Matrix *scale_add(Matrix *n, Matrix *m)
    Matrix *transpose(Matrix *n)
    Matrix *difference(Matrix *x, Matrix *y)
    Matrix *vectorize(Matrix *input)
    Matrix *im2col(Matrix *input, Matrix *feature_map)


cdef extern from "<data_structures/matrix/includes/adj_mat.h>":

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
    


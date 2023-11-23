
cdef extern from "../src/data_structures/matrix/includes/matrix.h":

    struct Matrix:
        int rows
        int cols
        double **arr
    
    Matrix *init_vec(int rows, int cols, bint identity)
    Matrix *init_matrix(int rows, int cols)
    Matrix *copy_matrix(Matrix *m) 
    Matrix *copy_matrix_values(Matrix *m, Matrix *n)
    void print_vec(Matrix *m)  


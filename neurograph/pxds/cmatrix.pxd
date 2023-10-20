
cdef extern from "../src/data_structures/includes/matrix.h":

    struct Matrix:
        int rows
        int cols
        double **arr
    
    Matrix *init_vec(int rows, int cols, bint identity)
    void print_vec(Matrix *m);  


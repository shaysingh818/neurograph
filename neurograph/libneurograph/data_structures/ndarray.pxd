
 cdef extern from "<data_structures/ndarray/includes/ndarray.h>":

    struct NDArray:
        int rank
        int size
        int *shape
        double *values

    # /* creation */
    NDArray *ndarray(int rank, int *shape);

    # /* utils  */
    int *reshape(NDArray *t, int rank, int *indices);
    int nindex(NDArray *t, int *indices);
    int *indices(NDArray *t, int index); 
    double nidx(NDArray *t, int *indices);  
    void nset(NDArray *t, int *indices, double value);
    NDArray *napply(double(*activation_function)(double), NDArray *t); 

    # /* save and load operations */
    void save_ndarray(NDArray *t, char *filename);
    NDArray *load_ndarray(char *filename);

    # /* printing debugging methods */
    void print_tensor(NDArray *t); 
    void shape(NDArray *t);
    void matrix(NDArray *t);  
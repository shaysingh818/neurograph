cimport libneurograph.computation_graph.cvalue as value
cimport libneurograph.data_structures.cmatrix as matrix

cdef extern from "<neurograph/computation_graph/includes/loss.h>":

    # tanh
    double tanh_activation(double x); 
    matrix.Matrix *tanh_prime(matrix.Matrix *x);

    # sigmoid
    double sigmoid(double x);
    matrix.Matrix sigmoid_prime(matrix.Matrix *x);

    # MSE
    double mse(matrix.Matrix *y_true, matrix.Matrix *y_pred);
    matrix.Matrix *mse_prime(matrix.Matrix *y_true, matrix.Matrix *y_pred); 
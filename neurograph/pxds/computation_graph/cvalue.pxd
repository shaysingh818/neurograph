import pxds.data_structures.cmatrix as matrix

cdef extern from "<neurograph/computation_graph/includes/value.h>":

    struct Value:
        char *alias
        struct Value *left
        struct Value *right
        matrix.Matrix *val
        matrix.Matrix *output; 
        matrix.Matrix *upstream_gradient
        matrix.Matrix *left_grad
        matrix.Matrix *right_grad
        matrix.Matrix *local_grad
        matrix.Matrix *(*backward_operation)(struct Value *val)
        matrix.Matrix *(*forward_operation)(struct Value *val)
        double (*loss)(double val)
        matrix.Matrix *(*loss_prime)(matrix.Matrix *val)
 
    Value *value(matrix.Matrix *set_value); 
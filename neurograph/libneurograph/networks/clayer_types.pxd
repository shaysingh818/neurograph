cimport libneurograph.data_structures.cmatrix as matrix
cimport libneurograph.computation_graph.cvalue as value

cdef extern from "<networks/includes/layer_types.h>":

    struct LossValue:
        double (*loss)(double val)
        matrix.Matrix *(*loss_prime)(matrix.Matrix *val)

    struct Activation:
        char *loss_function_name
        int input_size, output_size; 
        double(*loss)(double val); 
        matrix.Matrix*(*loss_prime)(matrix.Matrix *val);

    struct Linear:
        int input_size
        int output_size
        value.Value *weights
        value.Value *biases
    
    LossValue *loss_val(
        double(*loss)(double val),
        matrix.Matrix*(*loss_prime)(matrix.Matrix *val)
    ); 
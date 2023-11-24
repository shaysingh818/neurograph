import pxds.computation_graph.cvalue as value
import pxds.data_structures.cmatrix as matrix
import pxds.computation_graph.cgraph as cg

cdef extern from "<neurograph/computation_graph/includes/ops.h>":

    # multiplication
    value.Value *mat_mul(cg.ComputationGraph *graph, value.Value *x, value.Value *y); 
    matrix.Matrix *mat_mul_forward(value.Value *val);
    matrix.Matrix *mat_mul_backward(value.Value *val);

    # scale add
    value.Value *scale_add_mat(cg.ComputationGraph *graph, value.Value *x, value.Value *y); 
    matrix.Matrix *scale_add_forward(value.Value *val);
    matrix.Matrix *scale_add_backward(value.Value *val);

    # apply loss
    value.Value *apply_loss(
        cg.ComputationGraph *graph, 
        value.Value *set_val, 
        double(*loss)(double val),
        matrix.Matrix*(*loss_prime)(value.Value *val)
    )
    matrix.Matrix *apply_loss_forward(value.Value *val);
    matrix.Matrix *apply_loss_backward(value.Value *val);
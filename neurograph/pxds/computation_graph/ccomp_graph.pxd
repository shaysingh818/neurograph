import pxds.computation_graph.cvalue as value
import pxds.data_structures.cmatrix as matrix

cdef extern from "<neurograph/computation_graph/includes/computation_graph.h>":

    struct ComputationGraph:
        int size
        int curr_index
        matrix.Matrix *inputs
        matrix.Matrix *output_error
        value.Value **nodes
    
    ComputationGraph *create_graph(); 
    void append_op(ComputationGraph *graph, value.Value *val);
    void forward_nodes(ComputationGraph *graph);
    void *backward_nodes(ComputationGraph *graph, matrix.Matrix *output_error);
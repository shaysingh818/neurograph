cimport libneurograph.data_structures.cmatrix as matrix
cimport libneurograph.data_structures.ctable as table
cimport libneurograph.computation_graph.cvalue as value
cimport libneurograph.computation_graph.ccomp_graph as cg
cimport libneurograph.computation_graph.cops as ops
cimport libneurograph.computation_graph.closs as loss
cimport libneurograph.networks.clayer_types as ltypes

cdef extern from "<networks/includes/layer.h>":

    union LayerObject:
        ltypes.Linear *linear
        ltypes.Activation *activation

    struct Layer:
        char *layer_name
        int input_size
        int output_size
        LayerObject *layer_type
        value.Value *inputs
        value.Value *outputs
        value.Value *(*forward)(cg.ComputationGraph *graph, Layer *layer, value.Value *prev_output)
        value.Value *(*update_params)(cg.ComputationGraph *graph, Layer *layer, int op_index)
        void (*save)(Layer *layer, char *filepath)
        Layer *(*load)(char *filepath)

    table.BinTable *loss_map(); 
    table.BinTable *layer_map();  

    # linear methods
    value.Value *linear_forward(cg.ComputationGraph *graph, Layer *layer, value.Value *prev_output);
    value.Value *update_linear(cg.ComputationGraph *graph, Layer *layer, int op_index);
    Layer *linear(int set_input_size, int set_output_size);
    Layer *load_linear(char *filepath); 
    void save_linear(Layer *linear, char *filepath);
    void set_linear_inputs(Layer *linear, matrix.Matrix *input); 

    #  loss layer methods
    value.Value *activation_forward(cg.ComputationGraph *graph, Layer *layer, value.Value *prev_output); 
    value.Value *update_activation(cg.ComputationGraph *graph, Layer *layer, int op_index);
    Layer *activation(int set_input_size, int set_output_size, char *loss_function_name);
    Layer *load_activation(char *filepath); 
    void save_activation(Layer *linear, char *filepath); 

    
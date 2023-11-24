import pxds.data_structures.cmatrix as matrix
import pxds.computation_graph.cvalue as value
import pxds.computation_graph.cgraph as cg
import pxds.networks.clayer as layer

cdef extern from "<neurograph/networks/includes/network.h>":

    struct Network:
        int num_layers
        int layer_count
        int batch_size;
        int front_index
        int rear_index
        int pass_index;  
        double learning_rate
        double loss;
        bint batched; 
        matrix.Matrix **input_batches;  
        value.Value *input; 
        layer.Layer **layers; 
        cg.ComputationGraph *graph; 

    # network methods 
    Network *init_network(double learning_rate, value.Value *input, int batch_size);
    void layer(Network *nn, layer.Layer *layer);
    void train(Network *nn, int epochs, matrix.Matrix *y); 
    void batch_train(Network *nn, int epochs, matrix.Matrix *y);  
    void update_network_params(Network *nn);
    void predict(Network *nn, matrix.Matrix *input, matrix.Matrix *expected_output); 

    # save model 
    void save_model_params(Network *nn, char *filepath);
    void load_model_params(Network *n, char *filepath);   

    # Loading model archtectures 
    Network *load_model_architecture(char *model_architecture_path, value.Value *inputs);

 
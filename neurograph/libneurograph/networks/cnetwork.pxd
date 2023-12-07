cimport libneurograph.data_structures.cmatrix as matrix
cimport libneurograph.computation_graph.cvalue as value
cimport libneurograph.computation_graph.ccomp_graph as cg
cimport libneurograph.networks.clayer as la

cdef extern from "<networks/includes/network.h>":

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
        la.Layer **layers; 
        cg.ComputationGraph *graph; 

    # network methods 
    Network *init_network(double learning_rate, value.Value *input, int batch_size);
    void layer(Network *nn, la.Layer *layer);
    void train(Network *nn, int epochs, matrix.Matrix *y, bint log); 
    void batch_train(Network *nn, int epochs, matrix.Matrix *y, bint log);  
    void update_network_params(Network *nn);
    matrix.Matrix *predict(Network *nn, matrix.Matrix *input); 

    # save model 
    void save_model_params(Network *nn, char *filepath);
    void load_model_params(Network *n, char *filepath);   

    # Loading model archtectures 
    Network *load_model_architecture(char *model_architecture_path, value.Value *inputs);

 
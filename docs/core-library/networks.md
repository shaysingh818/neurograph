
* Module for creating neural networks
* Contains helpers for creating layers 
* Built on the computation graph library for automatic differentiation

### Network
```c
struct Network {
    int num_layers, layer_count, batch_size;
    int front_index, rear_index, pass_index;  
    double learning_rate, loss;
    bool batched; 
    mat_t **input_batches;  
    value_t *input; 
    layer_t **layers; 
    computation_graph_t *graph; 
}; 

typedef struct Network net_t; 
```


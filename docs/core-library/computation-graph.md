* Graph structure used for finding gradients for each operation
* Depends on generic value (Tensors in future versions)

### Computation Graph
```c
struct ComputationGraph {
    int size, curr_index;  
    mat_t *inputs, *output_error; 
    value_t **nodes; 
}; 

typedef struct ComputationGraph computation_graph_t;
```

#### create_graph

```c
computation_graph_t *create_graph(); 
```


#### append_op

|Parameter Name|Type| Description|
|--------------|-----|------------|
|graph|`computation_graph`|Instance of computation graph|
|val|`value_t`|Instance of generic value|

```c
void append_op(computation_graph_t *graph, value_t *val);
```


#### append_op

|Parameter Name|Type| Description|
|--------------|-----|------------|
|graph|`computation_graph`|Instance of computation graph|

```c
void forward_nodes(computation_graph_t *graph); 
```


#### append_op

|Parameter Name|Type| Description|
|--------------|-----|------------|
|graph|`computation_graph`|Instance of computation graph|
|output_error|`mat_t`|Matrix instance of the output error from operation|

```c
void backward_nodes(computation_graph_t *graph, mat_t *output_error); 
```
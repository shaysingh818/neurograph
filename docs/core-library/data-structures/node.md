### Node

```c
/* Generic node */ 
struct Node {
	int id, weight, counter; 
	char *label;
	struct Node* next;
	struct Node* left; 
	struct Node* right;  
}; 

typedef struct Node node_t;

```

The Node structure is a common type used for storing data in structures and working with values in the graph library. It represents the common types needed such as integers for weight values and id's. Character types for working with text data. 

#### create_node

|Parameter Name|Type| Description|
|--------------|-----|------------|
|id|`int`|Integer id associated with node|
|label|`char*`|Character label assigned to node value|
|weight|`int`|Weight value to quantify relationship with other nodes|

```c
node_t *create_node(int id, char *label, int weight); 
```


#### print_node

|Parameter Name|Type| Description|
|--------------|-----|------------|
|node|`node_t`|Instance of another node pointer|

```c
void print_node(node_t *node); 
```


#### create_edge

|Parameter Name|Type| Description|
|--------------|-----|------------|
|n1|`node_t`|Instance of another node pointer|
|n2|`node_t`|Instance of another node pointer|
|weight|`int`|Weight value to quantify relationship with other nodes|

```c
edge_t* create_edge(node_t *n1, node_t *n2, int weight);
```

#### print_edge

|Parameter Name|Type| Description|
|--------------|-----|------------|
|edge|`edge_t`|Instance of another edge pointer|

```c
void print_edge(edge_t *edge); 
```
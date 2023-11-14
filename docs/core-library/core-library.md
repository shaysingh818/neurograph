## Data Structures

The data structures library is a suite of data structures needed for creating dataframes, representing graphs and performing matrix operations. Currently the data structures support performing operations on the `node_t` structure. Eventually it will support generic types using void pointers. 

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
void print_node(edge_t *edge); 
```

### Queue
```c
struct Queue {
	unsigned capacity; 
	int front_index, rear_index, item_count;
	node_t* front, rear; 
	node_t **items; 
}; 

typedef struct Queue queue_t;
```

#### init_queue

|Parameter Name|Type| Description|
|--------------|-----|------------|
|capacity|`unsigned`|Capacity that queue can hold|

```c
queue_t init_queue(unsigned *capacity); 
```

#### is_full

|Parameter Name|Type| Description|
|--------------|-----|------------|
|queue|`queue_t`|Instance of queue pointer|

```c
int is_full(queue_t *queue); 
```


#### is_empty

|Parameter Name|Type| Description|
|--------------|-----|------------|
|queue|`queue_t`|Instance of queue pointer|

```c
int is_empty(queue_t *queue); 
```


#### front

|Parameter Name|Type| Description|
|--------------|-----|------------|
|queue|`queue_t`|Instance of queue pointer|

```c
int front(queue_t *queue); 
```

#### rear

|Parameter Name|Type| Description|
|--------------|-----|------------|
|queue|`queue_t`|Instance of queue pointer|

```c
int rear(queue_t *queue); 
```


#### push

|Parameter Name|Type| Description|
|--------------|-----|------------|
|queue|`queue_t`|Instance of queue pointer|
|item|`node_t`|Instance of node pointer|

```c
void push(queue_t *queue, node_t *item); 
```

#### pop

|Parameter Name|Type| Description|
|--------------|-----|------------|
|queue|`queue_t`|Instance of queue pointer|

```c
void pop(queue_t *queue); 
```

#### print_queue

|Parameter Name|Type| Description|
|--------------|-----|------------|
|queue|`queue_t`|Instance of queue pointer|

```c
void print_queue(queue_t *queue); 
```

## Extractors


## Computation Graph


## Graph Library


## Deep Learning
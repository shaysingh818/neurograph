### Adjacency List

The list data structure package contains structures for adjacency lists, arrays and linked lists. The adjacency lists are needed for representing graphs. Arrays are used for general memory usage. Linked lists are not used so much but are convienient to have in the long term.


```c
struct AdjacencyList {
	int v;
   	int e; 	
	int *visited, *used;
	bool directed;
   	bool err; 	
   	edge_t **edges;
	node_list_t **items; 	
}; 

typedef struct AdjacencyList adj_list_t; 
```


#### init_adj_list

|Parameter Name|Type| Description|
|--------------|-----|------------|
|v|`int`|Vertices|
|e|`int`|Edges|
|directed|`bool`|Directed graph|

```c
adj_list_t *init_adj_list(int v, int e, bool directed);
```

#### transpose_items

|Parameter Name|Type| Description|
|--------------|-----|------------|
|g|`adj_list_t`|Graph to be transposed|
|r|`adj_list _t`|Reversed Result|

```c
adj_list_t *transpose_items(adj_list_t *g, adj_list_t *r); 
```

#### add_node

|Parameter Name|Type| Description|
|--------------|-----|------------|
|g|`adj_list_t`|Graph to add node to|
|src_id|`int`|ID of source node|
|src_label|`char*`|Character result of source node|
|dest_id|`int`|Destination node id|
|dest_label|`char*`|Destination node label|
|weight|`int`|Weight of relationship|

```c
int add_node(
	adj_list_t *g, int src_id, char *src_label, 
	int dest_id, char *dest_label, int weight
); 
```


#### add_end_node

|Parameter Name|Type| Description|
|--------------|-----|------------|
|g|`adj_list_t`|Graph to add end node to|
|src_id|`int`|ID of source node|
|src_label|`char*`|Character result of source node|
|weight|`int`|Weight of relationship|

```c
int add_end_node(adj_list_t *g, int src_id, char *src_label, int weight);
```

#### get_node_by_id

|Parameter Name|Type| Description|
|--------------|-----|------------|
|g|`adj_list_t`|Graph to add end node to|
|id|`int`|ID of node to search|

```c
node_t *get_node_by_id(adj_list_t *g, int id);
```

#### resize_adj_list

|Parameter Name|Type| Description|
|--------------|-----|------------|
|g|`adj_list_t`|Graph to resize|
|id|`int`|New vertice size|

```c
void resize_adj_list(adj_list_t *g, int new_size);  
```

## Array

```c
struct Array {
    int capacity, used, front_index, rear_index, item_count; 
    int *insert_counts;  
    node_t **items; 
};
typedef struct Array array_t; 
```

#### init_array

```c
array_t *init_array(); 
```


#### insert

|Parameter Name|Type| Description|
|--------------|-----|------------|
|a|`array_t`|Array to add item to|
|item|`node_t`|Item to add to array|

```c
void insert(array_t *a, node_t *item);
```


#### insert_char

|Parameter Name|Type| Description|
|--------------|-----|------------|
|a|`array_t`|Array to add string to|
|item|`char*`|Character string to add to array|

```c
void insert_char(array_t *a, char *item);
```


#### remove_char

|Parameter Name|Type| Description|
|--------------|-----|------------|
|a|`array_t`|Array to remove char from|
|item|`char*`|Character string to add to array|

```c
void remove_char(array_t *a, char *item);
```

#### pop_array

|Parameter Name|Type| Description|
|--------------|-----|------------|
|a|`array_t`|Array to pop item from|

```c
void pop_array(array_t *a);
```

#### print_array

|Parameter Name|Type| Description|
|--------------|-----|------------|
|a|`array_t`|Array to print|

```c
void print_array(array_t *a);
```
## Data Structures

The data structures library is a suite of data structures needed for creating dataframes, representing graphs and performing matrix operations. Currently the data structures support performing operations on the `node_t` structure. Eventually it will support generic types using void pointers. 


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
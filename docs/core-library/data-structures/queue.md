### Queue

The Queue Library is needed for keeping track of graph walks, processing results in dataframes and working with items that require FIFO/LIFO ordering.

```c
struct Queue {
	unsigned capacity; 
	int front_index, rear_index, item_count;
	node_t* front, rear; 
	node_t **items; 
}; 

typedef struct Queue queue_t;
```


####  Queue Sample

```C

/* create nodes */ 
node_t *item1 = create_node(1, "String Item 1", 0);  
node_t *item2 = create_node(2, "String Item 2 ", 0); 
node_t *item3 = create_node(3, "String Item 3 ", 0); 
node_t *item4 = create_node(4, "String Item 4", 0); 
node_t *item5 = create_node(5, "String Item 5", 0); 

/* test if queue works */ 
queue_t *q = init_queue(count); 
push(q, item1);
push(q, item2); 
push(q, item3); 
push(q, item4); 
push(q, item5);
assert(q->item_count == count); 

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
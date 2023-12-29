
### Set

Set data structure is used for handling unique items in a list. 

```c
struct Set {
    node_t *root;
    queue_t *queue;  
    bool ordered; 
    int count; 
    int *items;  
};

typedef struct Set set_t; 
```


#### init_set

|Parameter Name|Type| Description|
|--------------|-----|------------|
|set_order|`bool`|Toggle if set is ordered|

```c
set_t *init_set(bool set_order);
```


#### insert_sorted

|Parameter Name|Type| Description|
|--------------|-----|------------|
|s|`set_t`|Set instance|
|id|`int`|Set ID|
|string_value|`char*`|Character value|
|weight|`int`|Weight value (for potential nodes)|

```c
bool insert_sorted(set_t *s, int id, char *string_value, int weight);
```


#### insert_set_value_sorted

|Parameter Name|Type| Description|
|--------------|-----|------------|
|root|`node_t`|Root in set tree|
|item|`node_t`|Item to add to tree|

```c
node_t *insert_set_value_sorted(node_t *root, node_t *item);
```

#### get_item_sorted

|Parameter Name|Type| Description|
|--------------|-----|------------|
|s|`set_t`|Instance of set|
|key|`char*`|String value to search for|

```c
int get_item_sorted(set_t *s, char *key); 
```

#### get_items_sorted

|Parameter Name|Type| Description|
|--------------|-----|------------|
|root|`node_t`|Root in set tree|
|q|`queue_t`|Results stored in queue|

```c
void get_items_sorted(node_t *root, queue_t *q);
```


#### print_set_sorted

|Parameter Name|Type| Description|
|--------------|-----|------------|
|s|`set_t`|Instance of set|

```c
void print_set_sorted(set_t *s); 
```


### Ordered Set

Set data structure is used for handling unique items in a list in the order they're inserted.

```c
struct OrderedSet {
    int capacity, used, front, rear; 
    int *insert_counts;  
    node_t **items; 
}; 

typedef struct OrderedSet ordered_set_t; 
```


#### init_array_set

|Parameter Name|Type| Description|
|--------------|-----|------------|
|capacity|`int`|Max capacity of items inserted|

```c
ordered_set_t *init_array_set(int capacity);
```


#### insert_ordered

|Parameter Name|Type| Description|
|--------------|-----|------------|
|s|`ordered_set_t`|Set instance|
|id|`int`|Set ID|
|string_value|`char*`|Character value|
|weight|`int`|Weight value (for potential nodes)|

```c
bool insert_ordered(ordered_set_t *s, int id, char *string_value, int weight);
```


#### get_insert_count

|Parameter Name|Type| Description|
|--------------|-----|------------|
|s|`ordered_set_t`|Set instance|
|item|`node_t`|Item to insert|

```c
int get_insert_count(ordered_set_t *s, node_t *item);
```

#### get_value_id

|Parameter Name|Type| Description|
|--------------|-----|------------|
|s|`ordered_set_t`|Set instance|
|id|`int`|Set ID|

```c
int get_value_id(ordered_set_t *s, int id); 
```

#### get_value_key

|Parameter Name|Type| Description|
|--------------|-----|------------|
|s|`ordered_set_t`|Set instance|
|key|`char`|Character value to search|

```c
int get_value_key(ordered_set_t *s, char *key);
```


#### print_items_ordered

|Parameter Name|Type| Description|
|--------------|-----|------------|
|s|`ordered_set_t`|Set instance|

```c
void print_items_ordered(ordered_set_t *s);
```
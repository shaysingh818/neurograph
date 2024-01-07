### Hash Table 
#### hash_table

|Parameter Name|Type| Description|
|--------------|-----|------------|
|table|`hash_table_t`|Hash Table instance|
|load_factor|`double`|Load factor for probing|
|key_cmp|`compare_func`|Key comparison function|
|key_destructor|`destructor_func`|function to deallocate key|
|val_destructor|`destructor_func`|function to deallocate value|
|hash_function|`hash_func`|Hash function to create hash key|

```c
hash_table_t *hash_table(
	int size, 
	double load_factor,
	compare_func key_cmp, 
	destructor_func key_destructor,
	destructor_func val_destructor,
	hash_func hash_function
); 
```


#### delete_hash_table

|Parameter Name|Type| Description|
|--------------|-----|------------|
|table|`hash_table_t`|Hash Table instance|

```c
void delete_hash_table(hash_table_t *table);
```


#### add_table_map

|Parameter Name|Type| Description|
|--------------|-----|------------|
|table|`hash_table_t`|Hash Table instance|
|key|`void`|Key to map to value|
|value|`void`|Value to map from key|

```c
void add_table_map(hash_table_t *table, void *key, void *value); 
```

#### delete_table_key

|Parameter Name|Type| Description|
|--------------|-----|------------|
|table|`hash_table_t`|Hash Table instance|
|key|`void`|Key to delete|

```c
void delete_table_key(hash_table_t *table, void *key); 
```


#### lookup_table_key

|Parameter Name|Type| Description|
|--------------|-----|------------|
|table|`hash_table_t`|Hash Table instance|
|key|`void`|Key to delete|

```c
void *lookup_table_key(hash_table_t *table, void *key); 
```


#### table_resize

|parameter name|type| description|
|--------------|-----|------------|
|table|`hash_table_t`|hash table instance|
|new_size|`int`|new size to allocate|

```c
void table_resize(hash_table_t *table, int new_size); 
```

#### probe

|parameter name|type| description|
|--------------|-----|------------|
|k|`int`|hash table instance|
|i|`int`|new size to allocate|
|m|`int`|new size to allocate|

```c
int probe(int k, int i, int m);
```


#### print_table

|parameter name|type| description|
|--------------|-----|------------|
|table|`hash_table_t`|hash table instance|

```c
void print_table(hash_table_t *table); 
```

### Map

```c

struct hash_linked_list {
	int hash_key;
	void *key;
	void *value;  
	struct hash_linked_list *next; 
}; 

typedef struct hash_linked_list h_ll_t; 


struct HashTable {
	h_ll_t **table;  
	int size, used, active; 
	compare_func key_cmp; 
	destructor_func key_destructor;
	destructor_func val_destructor;  
	hash_func hash_function; 
}; 

typedef struct HashTable map_t;

```



#### init_table

|Parameter Name|Type| Description|
|--------------|-----|------------|
|size|`int`|size of table|
|key_cmp|`compare_func`|Key comparision function|
|key_destructor|`destructor_func`|function to deallocate key|
|val_destructor|`destructor_func`|function to deallocate value|
|hash_function|`hash_func`|function to hash key|

```c
map_t *init_table(
	int size, 
	compare_func key_cmp, 
	destructor_func key_destructor, 
	destructor_func val_destructor,
	hash_func hash_function
);
```

#### delete_table

|Parameter Name|Type| Description|
|--------------|-----|------------|
|table|`map_t`|table instance|

```c
void delete_table(map_t *table); 
```

#### lookup_key

|Parameter Name|Type| Description|
|--------------|-----|------------|
|table|`map_t`|table instance|
|key|`void`|void key pointer|

```c
void *lookup_key(map_t *table, void *key); 
```

#### insert_key

|Parameter Name|Type| Description|
|--------------|-----|------------|
|table|`map_t`|table instance|
|key|`void`|void key pointer|

```c
void *insert_key(map_t *table, void *key); 
```


#### delete_key

|Parameter Name|Type| Description|
|--------------|-----|------------|
|table|`map_t`|table instance|
|key|`void`|void key pointer|

```c
void *delete_key(map_t *table, void *key); 
```


#### add_map

|Parameter Name|Type| Description|
|--------------|-----|------------|
|table|`map_t`|table instance|
|key|`void`|void key pointer|
|value|`void`|void value pointer|

```c
void add_map(map_t *table, void *key, void *value); 
```

#### resize

|Parameter Name|Type| Description|
|--------------|-----|------------|
|table|`map_t`|table instance|
|new_size|`int`|new size of table|

```c
void resize(map_t *table, int new_size);  
```

#### contains_key

|Parameter Name|Type| Description|
|--------------|-----|------------|
|table|`map_t`|table instance|
|key|`void`|void key pointer|

```c
bool contains_key(map_t *table, void* key); 
```

#### new_hash_ll

```c
h_ll_t *new_hash_ll();
```

#### get_prev_link

|Parameter Name|Type| Description|
|--------------|-----|------------|
|list|`h_ll_t`|Hash Linked List instance|
|hash_key|`int`|Numeric Hash Key|
|key|`void`|Key Value|
|key_cmp|`compare_func`|Function to compare key|

```c
h_ll_t *get_prev_link(h_ll_t *list, int hash_key, void *key, compare_func key_cmp);
```


#### lookup_key_list

|Parameter Name|Type| Description|
|--------------|-----|------------|
|list|`h_ll_t`|Hash Linked List instance|
|hash_key|`int`|Numeric Hash Key|
|key|`void`|Key Value|
|key_cmp|`compare_func`|Function to compare key|

```c
h_ll_t *lookup_key_list(h_ll_t *list, int hash_key, void *key, compare_func key_cmp);  
```


#### contains_key_list

|Parameter Name|Type| Description|
|--------------|-----|------------|
|list|`h_ll_t`|Hash Linked List instance|
|hash_key|`int`|Numeric Hash Key|
|key|`void`|Key Value|
|key_cmp|`compare_func`|Function to compare key|

```c
bool contains_key_list(h_ll_t *list, int hash_key, void *key, compare_func key_cmp); 
```


#### delete_key_list

|Parameter Name|Type| Description|
|--------------|-----|------------|
|list|`h_ll_t`|Hash Linked List instance|
|hash_key|`int`|Numeric Hash Key|
|key|`void`|Key Value|
|key_cmp|`compare_func`|Function to compare key|
|key_destructor|`destructor_func`|function to deallocate key|
|val_destructor|`destructor_func`|function to deallocate value|

```c
bool delete_key_list(
    h_ll_t *list, 
    int hash_key, 
    void *key, 
    compare_func key_cmp, 
    destructor_func key_destructor, 
    destructor_func val_destructor
); 
```

#### add_map_list

|Parameter Name|Type| Description|
|--------------|-----|------------|
|list|`h_ll_t`|Hash Linked List instance|
|hash_key|`int`|Numeric Hash Key|
|key|`void`|Key Value|
|value|`void`|Key application value

```c
void add_map_list(h_ll_t *list, int hash_key, void *key, void *value);
```

#### insert_key_list

|Parameter Name|Type| Description|
|--------------|-----|------------|
|list|`h_ll_t`|Hash Linked List instance|
|hash_key|`int`|Numeric Hash Key|
|key|`void`|Key Value|
|key_cmp|`compare_func`|Function to compare key|

```c
void insert_key_list(h_ll_t *list, int hash_key, void *key, compare_func key_cmp); 
```


#### delete_hash_ll

|Parameter Name|Type| Description|
|--------------|-----|------------|
|list|`h_ll_t`|Hash Linked List instance|
|hash_key|`int`|Numeric Hash Key|
|key_destructor|`destructor_func`|function to deallocate key|
|val_destructor|`destructor_func`|function to deallocate value|
|free_resources|`bool`|Toggle freeing map resources|

```c
void delete_hash_ll(
    h_ll_t *list, 
    destructor_func key_destructor, 
    destructor_func val_destructor, 
    bool free_resources
);
```

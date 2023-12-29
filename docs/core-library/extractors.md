
### Frame 

```c
struct Frame {
	int buffer_size, header_count; 
	int curr_row, row_count, row_limit; 
	char *filename, *file_buffer, *delimiter; 
	bool status;
	mat_t *matrix;    
	array_t *headers; 
    hash_table_t *frame;
};

typedef struct Frame frame_t; 
```


#### create_frame

|Parameter Name|Type| Description|
|--------------|-----|------------|
|filepath|`char*`|path to csv file|
|buffer_size|`int`|max buffer size for each file line|
|row_limit|`int`|Amount of rows to load|
|delimiter|`char*`|Delimiter to separate|

```c
frame_t *create_frame(char *filepath, int buffer_size, int row_limit, char *delimiter);
```


#### dataframe

|Parameter Name|Type| Description|
|--------------|-----|------------|
|filepath|`char*`|path to csv file|
|buffer_size|`int`|max buffer size for each file line|
|row_limit|`int`|Amount of rows to load|
|delimiter|`char*`|Delimiter to separate|

```c
frame_t *dataframe(char *filepath, int buffer_size, int row_limit, char *delimiter);  
```


#### init_row_value

|Parameter Name|Type| Description|
|--------------|-----|------------|
|index|`int`|row index|
|value|`char*`|row value|

```c
row_value_t *init_row_value(int index, char *value); 
```

#### frame_to_matrix

|Parameter Name|Type| Description|
|--------------|-----|------------|
|frame|`frame_t`|Instance of data frame|
|cols|`array_t`|Array with column values stored|

```c
mat_t *frame_to_matrix(frame_t *frame, array_t *cols); 
```


#### extract_headers

|Parameter Name|Type| Description|
|--------------|-----|------------|
|frame|`frame_t`|Instance of data frame|

```c
void extract_headers(frame_t *frame);
```


#### init_rows

|Parameter Name|Type| Description|
|--------------|-----|------------|
|frame|`frame_t`|Instance of data frame|

```c
void init_rows(frame_t *frame); 
```


#### print_cols 

|Parameter Name|Type| Description|
|--------------|-----|------------|
|frame|`frame_t`|Instance of data frame|

```c
void print_cols(frame_t *frame); 
```


#### print_rows 

|Parameter Name|Type| Description|
|--------------|-----|------------|
|frame|`frame_t`|Instance of data frame|

```c
void print_rows(frame_t *frame);
```


#### select_cols 

|Parameter Name|Type| Description|
|--------------|-----|------------|
|frame|`frame_t`|Instance of data frame|
|headers|`void**`|Headers to select from frame|

```c
void select_cols(frame_t *frame, void** headers); 
```


#### drop_cols 

|Parameter Name|Type| Description|
|--------------|-----|------------|
|frame|`frame_t`|Instance of data frame|
|cols|`array_t`|Columns to drop from frame|

```c
void drop_cols(frame_t *frame, array_t *cols); 
```


#### get_row_key 

|Parameter Name|Type| Description|
|--------------|-----|------------|
|frame|`frame_t`|Instance of data frame|
|key|`char*`|Row key to search for|

```c
char **get_row_key(frame_t *frame, char *key); 
```


#### add_frame_cols 

|Parameter Name|Type| Description|
|--------------|-----|------------|
|frame|`frame_t`|Instance of data frame|
|col1|`char*`|Column on dataframe|
|col2|`char*`|Column on dataframe|
|result_col|`char*`|Name of result column key|

```c
void add_frame_cols(frame_t *frame, char *col1, char *col2, char *result_col); 
```

#### subtract_frame_cols 

|Parameter Name|Type| Description|
|--------------|-----|------------|
|frame|`frame_t`|Instance of data frame|
|col1|`char*`|Column on dataframe|
|col2|`char*`|Column on dataframe|
|result_col|`char*`|Name of result column key|

```c
void subtract_frame_cols(frame_t *frame, char *col1, char *col2, char *result_col); 
```
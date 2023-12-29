
### Matrix

```c
struct Matrix {
    int rows; 
    int cols; 
    double **arr; 
}; 

typedef struct Matrix mat_t; 
```


#### init_vec

|Parameter Name|Type| Description|
|--------------|-----|------------|
|rows|`int`|rows of matrix|
|cols|`double`|cols of matrix|
|identity|`bool`|Load identity of matrix|

```c
mat_t *init_vec(int rows, int cols, bool identity);
```

#### init_matrix

|Parameter Name|Type| Description|
|--------------|-----|------------|
|rows|`int`|rows of matrix|
|cols|`double`|cols of matrix|

```c
mat_t *init_matrix(int rows, int cols);
```

#### apply

|Parameter Name|Type| Description|
|--------------|-----|------------|
|activation_function|`double(*activation_function)(double)`|function to apply to matrix|
|m|`mat_t`|matrix instance|

```c
mat_t *apply(double(*activation_function)(double), mat_t *m);  
```

#### copy_matrix

|Parameter Name|Type| Description|
|--------------|-----|------------|
|m|`mat_t`|matrix instance|

```c
mat_t *copy_matrix(mat_t *m);
```

#### load_matrix

|Parameter Name|Type| Description|
|--------------|-----|------------|
|filename|`char*`|Name of file to load matrix from|

```c
mat_t *load_matrix(char *filename);
```


#### to_rows

|Parameter Name|Type| Description|
|--------------|-----|------------|
|m|`mat_t`|matrix instance|

```c
mat_t **to_rows(mat_t *m);
```


#### to_cols

|Parameter Name|Type| Description|
|--------------|-----|------------|
|m|`mat_t`|matrix instance|

```c
mat_t **to_cols(mat_t *m);
```


#### batch_rows

|Parameter Name|Type| Description|
|--------------|-----|------------|
|m|`mat_t`|matrix instance|
|limit|`int`|amount to batch the matrix rows by|

```c
mat_t **batch_rows(mat_t *m, int limit);
```


#### batch_matrix

|Parameter Name|Type| Description|
|--------------|-----|------------|
|m|`mat_t`|matrix instance|
|batch_size|`int`|amount to batch the matrix rows by|

```c
mat_t **batch_matrix(mat_t *m, int batch_size); 
```


#### copy_arr_to_matrix

|Parameter Name|Type| Description|
|--------------|-----|------------|
|m|`int`|rows|
|n|`int`|cols|
|arr|`double[m][n]`|2d array in C|

```c
mat_t *copy_arr_to_matrix(int m, int n, double arr[m][n]); 
```


#### compare_matrix

|Parameter Name|Type| Description|
|--------------|-----|------------|
|m|`mat_t`|first matrix to compare|
|n|`mat_t`|second matrix to compare|

```c
bool compare_matrix(mat_t *m, mat_t *n); 
```


#### uniform_distribution

|Parameter Name|Type| Description|
|--------------|-----|------------|
|low|`double`|lower bound|
|high|`double`|upper bound|

```c
double uniform_distribution(double low, double high);
```

#### get

|Parameter Name|Type| Description|
|--------------|-----|------------|
|m|`mat_t`|matrix instance|
|row|`int`|row value index|
|col|`int`|col value index|

```c
double get(mat_t *m, int row, int col); 
```


#### copy_arr_to_matrix

|Parameter Name|Type| Description|
|--------------|-----|------------|
|v1|`mat_t`|first matrix to copy|
|v2|`mat_t`|second matrix to copy|

```c
void copy_mat(mat_t *v1, mat_t *v2);
```

#### print_vec

|Parameter Name|Type| Description|
|--------------|-----|------------|
|v1|`mat_t`|matrix instance to print|

```c
void print_vec(mat_t *v1);
```

#### matrix_free

|Parameter Name|Type| Description|
|--------------|-----|------------|
|m|`mat_t`|matrix instance to free|

```c
void matrix_free(mat_t *m);  
```


#### randomize

|Parameter Name|Type| Description|
|--------------|-----|------------|
|m|`mat_t`|matrix instance to free|
|n|`int`|bounded value|

```c
void randomize(mat_t *mat, int n); 
```

#### print_matrix

|Parameter Name|Type| Description|
|--------------|-----|------------|
|m|`mat_t`|matrix instance to free|

```c
void print_matrix(mat_t *mat);
```


#### fill_matrix

|Parameter Name|Type| Description|
|--------------|-----|------------|
|m|`mat_t`|matrix instance to free|
|n|`int`|values to fill matrix with|

```c
void fill_mat(mat_t *m, int n); 
```

#### save_matrix

|Parameter Name|Type| Description|
|--------------|-----|------------|
|m|`mat_t`|matrix instance to free|
|filename|`char`|name of file to save matrix to|

```c
void save_matrix(mat_t *m, char *filename);   
```


#### copy_matrix_values

|Parameter Name|Type| Description|
|--------------|-----|------------|
|m|`mat_t`|first matrix instance|
|m|`mat_t`|second matrix instance |

```c
void copy_matrix_values(mat_t *m, mat_t *n);
```


#### entry

|Parameter Name|Type| Description|
|--------------|-----|------------|
|m|`mat_t`|first matrix instance|
|row|`int`|row index|
|col|`int`|col index|
|value|`double`|value to insert|

```c
void entry(mat_t *m, int row, int col, double value); 
```


#### scalar_multiply

|Parameter Name|Type| Description|
|--------------|-----|------------|
|v1|`mat_t`|matrix instance|
|value|`double`|value to multiply by|

```c
mat_t *scalar_multiply(mat_t *v1, double value);
```


#### power

|Parameter Name|Type| Description|
|--------------|-----|------------|
|v1|`mat_t`|matrix instance|
|power|`int`|value to multiply by|

```c
mat_t *scalar_multiply(mat_t *v1, double value);
```


#### dot

|Parameter Name|Type| Description|
|--------------|-----|------------|
|n|`mat_t`|matrix instance to dot product by|
|m|`mat_t`|second matrix instance to dot product by|

```c
mat_t *dot(mat_t *n, mat_t *m);
```

#### multiply

|Parameter Name|Type| Description|
|--------------|-----|------------|
|v1|`mat_t`|matrix instance to multiply by|
|v2|`mat_t`|second matrix instance to multiply by|

```c
mat_t *multiply(mat_t *v1, mat_t *v2);
```


#### elementwise_multiply

|Parameter Name|Type| Description|
|--------------|-----|------------|
|v1|`mat_t`|matrix instance to multiply by|
|v2|`mat_t`|second matrix instance to multiply by|

```c
mat_t *elementwise_multiply(mat_t *v1, mat_t *v2); 
```

#### add

|Parameter Name|Type| Description|
|--------------|-----|------------|
|n|`mat_t`|matrix instance|
|m|`mat_t`|second matrix instance|

```c
mat_t *add(mat_t *n, mat_t *m);
```


#### scale

|Parameter Name|Type| Description|
|--------------|-----|------------|
|v|`mat_t`|matrix instance|
|value|`double`|value to scale by|

```c
mat_t *scale(mat_t *v, double value); 
```


#### scale_add

|Parameter Name|Type| Description|
|--------------|-----|------------|
|n|`mat_t`|matrix instance|
|m|`mat_t`|second matrix instance|

```c
mat_t *scale_add(mat_t *n, mat_t *m);
```

#### transpose

|Parameter Name|Type| Description|
|--------------|-----|------------|
|n|`mat_t`|matrix instance|

```c
mat_t *transpose(mat_t *n);
```


#### difference

|Parameter Name|Type| Description|
|--------------|-----|------------|
|x|`mat_t`|matrix instance|
|y|`mat_t`|second matrix instance|

```c
mat_t *difference(mat_t *x, mat_t *y);
```


#### vectorize

|Parameter Name|Type| Description|
|--------------|-----|------------|
|input|`mat_t`|matrix instance|

```c
mat_t *vectorize(mat_t *input); 
```


#### im2col

|Parameter Name|Type| Description|
|--------------|-----|------------|
|input|`mat_t`|matrix instance|
|feature_map|`mat_t`|matrix instance of feature map|

```c
mat_t *im2col(mat_t *input, mat_t *feature_map); 
```


### AdjacencyMatrix

```c
struct AdjacencyMatrix {
	int v;
   	int e; 	
	int *visited, *used;
	bool directed;
   	bool err; 	
    mat_t *weights; 
	node_t **items; 	
}; 

typedef struct AdjacencyMatrix adj_mat_t;
```


#### init_adj_mat

|Parameter Name|Type| Description|
|--------------|-----|------------|
|v|`int`|vertices|
|e|`int`|edges|
|directed|`bool`|toggle if graph is directed|

```c
adj_mat_t *init_adj_mat(int v, int e, bool directed);
```


#### add_node_mat

|Parameter Name|Type| Description|
|--------------|-----|------------|
|m|`adj_mat_t`|adjacency matrix instance|
|src_id|`int`|source node id|
|src|`char*`|character value for source node|
|dst_id|`int`|destination node id|
|dst|`char*`|character value for destination node|
|weight|`double`|weight value for node relationship|

```c
void add_node_mat(
    adj_mat_t *m, int src_id, char *src, 
    int dst_id, char *dst, double weight
);
```


#### tranpose_items_mat

|Parameter Name|Type| Description|
|--------------|-----|------------|
|m|`adj_mat_t`|adjacency matrix instance|
|r|`adj_mat_t`|second adjacency matrix instance|

```c
adj_mat_t *transpose_items_mat(adj_mat_t *m, adj_mat_t *r); 
```

#### search_node_by_id_mat

|Parameter Name|Type| Description|
|--------------|-----|------------|
|m|`adj_mat_t`|adjacency matrix instance|
|id|`int`|id of node to search|

```c
node_t *search_node_by_id_mat(adj_mat_t *m, int id);
```

#### print_adj_mat

|Parameter Name|Type| Description|
|--------------|-----|------------|
|m|`adj_mat_t`|adjacency matrix instance|

```c
void print_adj_mat(adj_mat_t *m); 
```
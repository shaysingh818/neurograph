
NDArray is used for representing data in multiple dimensions. The NDArray structure allows you to set the rank, dimensions and values stored in memory. The values are  stored as a contigious array. Strides are used to perform indexing in 2 or more dimensions. 

## Array Utilities

|Method|Description|
|------|-----------|
|[`ndarray(int rank, int *shape)`](###ndarray)| Creates instance of ndarray data structure|
|[`reshape(ndarray_t *t, int rank, int *shape)`](### `reshape(t,rank,shape)`)| Reshape ndarray with new rank and shape dimensions |
|[`int nindex(ndarray_t *t, int *indices)`](### `nindex(t, indices)`)| Gets one dimensional index value from array of indices |
|[`int *indices(ndarray_t *t, int index)`](### `indices(t, index)`)| Get's indices associated with contigous index value  |
|[`double nidx(ndarray_t *t, int *indices)`](### `nidx(t, indices)`)| Get's value associated with indices |
|[`void nset(ndarray_t *t, int *indices, double value)`](### `nset(t, indices)`)| Set value at specific permutation of indices |
|[`void save_ndarray(ndarray_t *t, char *filename)`](### `save_ndarray(t, filename)`)| Save NDArray values to file in memory |
|[`ndarray_t *load_ndarray(char *filename)`](### `load_ndarray(filename)`)| Load NDArray values from saved file |


### `ndarray(rank, shape)`
<hr>
* **Parameters**<br>
    * `rank`: Integer value that represents amount of dimensions in value. Eg. 2d, 3d Arrays
    * `shape` : Array of integers that correspond to the dimensions of the value. Example values: `(2, 3), (6, 6)`. 

**Notes**: This method creates the NDArray using the `ndarray_t` structure from the core library. This does not work from C -> python (backwards compatible)

**Example Code**:
```c

/* create 3 X 3 2d array */ 
ndarray_t *t = ndarray(2, (int[]){3, 3});
print_ndarray(t);

/* create 2 X 2 X 2 3d array */ 
ndarray_t *t1 = ndarray(3, (int[]){2, 2, 2});
print_ndarray(t1);

```
<hr>


### `reshape(t,rank,shape)`
<hr>
* **Parameters**<br>
    * `t` : Reference to instance of ndarray that will be reshaped
    * `rank`: Integer value that represents amount of dimensions in value. Eg. 2d, 3d Arrays
    * `shape` : Array of integers that correspond to the dimensions of the value. Example values: `(2, 3), (6, 6)`. 

**Notes**: This method requires you to provide a new rank and shape, even if the prior rank was the same. 

**Example Code**:
```c

/* create 3 X 3 2d array */ 
ndarray_t *t = ndarray(2, (int[]){3, 3});
print_ndarray(t);

/* reshape ndarray */
reshape(t, 3, (int[]){2, 2, 2})

```
<hr>


### `nindex(t, indices)`
<hr>
* **Parameters**<br>
    * `t` : Reference to instance of ndarray that will be reshaped
    * `indices`: Set of indices to map to one dimensional index. Length of indices is the rank of the value

**Example Code**:
```c

/* create 3 X 3 2d array */ 
ndarray_t *t = ndarray(2, (int[]){3, 3});

/* example nindex usage for Unit tests */
int index = 0; 
for(int i = 0; i < 3; i++){
    for(int j = 0; j < 3; j++){
        int test_index =  nindex(t, (int[]){i, j});
        assert(test_index == index);    
        index += 1;     
    }
}

```
<hr>


### `indices(t,index)`
<hr>
* **Parameters**<br>
    * `t` : Reference to instance of ndarray 
    * `index`: Integer value that maps to index of contiguous array

**Notes**: This method is a helper for flattening and performing transposes/contractions

**Example Code**:
```c

/* create 3 X 3 2d array */ 
ndarray_t *t = ndarray(2, (int[]){3, 3});
print_ndarray(t);


/*  set values of ndarray   */ 
int index = 0; 
for(int i = 0; i < 3; i++){
    for(int j = 0; j < 3; j++){
        nset(t, (int[]){i, j}, index+1);
        index += 1;     
    }
}

/* validate indexs match */
index = 0;
for(int i = 0; i < 3; i++){
    for(int j = 0; j < 3; j++){
        int *idxs = indices(t, index); 
        assert(idxs[0] == i);
        assert(idxs[1] == j);  
        index += 1; 
    }
}

```
<hr>


### `nidx(t,indices)`
<hr>
* **Parameters**<br>
    * `t` : Reference to instance of ndarray 
    * `indices`: Array of indices to map to value in ndarray

**Example Code**:
```c

/* create 3 X 3 2d array */ 
ndarray_t *t = ndarray(2, (int[]){3, 3});

/*  set values of ndarray   */ 
int index = 0; 
for(int i = 0; i < 3; i++){
    for(int j = 0; j < 3; j++){
        nset(t, (int[]){i, j}, index+1);
        index += 1;     
    }
}

double value = nidx(t, (int[]){0, 0}) /* grab value at  (0, 0) */ 
double value1 = nidx(t, (int[]){0, 1}) /* grab value at  (0, 1) */ 

```
<hr>


### `nset(t,indices, value)`
<hr>
* **Parameters**<br>
    * `t` : Reference to instance of ndarray 
    * `indices`: Array of indices to map to value in ndarray
    * `value`: Value we want to set in ndarray

**Example Code**:
```c

/* create 3 X 3 2d array */ 
ndarray_t *t = ndarray(2, (int[]){3, 3});

/*  set values of ndarray   */ 
int index = 0; 
for(int i = 0; i < 3; i++){
    for(int j = 0; j < 3; j++){
        nset(t, (int[]){i, j}, index+1); /* set value */
        index += 1;     
    }
}

```
<hr>


### `save_ndarray(t,filename)`

<hr>
* **Parameters**<br>
    * `t` : Reference to instance of ndarray 
    * `filename`: Path to save ndarray in memory


**Example Code**:
```c

/* create 3 X 3 2d array */ 
ndarray_t *t = ndarray(2, (int[]){3, 3});

/*  set values of ndarray   */ 
int index = 0; 
for(int i = 0; i < 3; i++){
    for(int j = 0; j < 3; j++){
        nset(t, (int[]){i, j}, index+1); /* set value */
        index += 1;     
    }
}

/* save ndarray  to path */
save_ndarray(t, "path/to/file/values")

```
<hr>


### `load_ndarray(filename)`

<hr>
* **Parameters**<br>
    * `filename`: Path reference to saved ndarray

**Note**: The loaded ndarray will set your shape and dimensions for you, all you need is the filepath.

**Example Code**:
```c

/* load saved ndarray */
ndarray_t *loaded = load_ndarray("path/to/file/values");
```
<hr>

## Operations

|Method|Description|
|------|-----------|
|[`ndot(ndarray_t *a, ndarray_t *b)`](### `ndot(a, b)`)| Dot Product of two ndarray's|
|[`nadd(ndarray_t *t, ndarray_t *val)`](### `nadd(t,val)`)| Add two ndarray's |
|[`nsubtract(ndarray_t *t1, ndarray_t *t2)`](### `nsubtract(t1, t2)`)| Subtract two ndarray's |
|[`nscale_add(ndarray_t *a, ndarray_t *b)`](### `nscale_add(a, b)`)| Add A ndarray by vector  |
|[`ntranspose(ndarray_t *t)`](### `ntranspose(t)`)| Tranpose of ndarray instance (rows as columns) |
|[`permute(ndarray_t *t, int *indice_order)`](### `permute(t, indice_order)`)| Contract NDArray and reorder indices |


### `ndot(a, b)`

<hr>
* **Parameters**<br>
    * `a`: First tensor to perform dot product
    * `b`: Second tensor to perform dot product

**Note**: Operation returns a new ndarray with the result of a and b.

**Example Code**:
```c

/* add two 3 X 3 ndarrays */
ndarray_t *t1 = ndarray(2, (int[]){3, 3}); 
ndarray_t *t2 = ndarray(2, (int[]){3, 3}); 
ndarray_t *result = ndot(t1, t2);
```
<hr>


### `nadd(a, b)`

<hr>
* **Parameters**<br>
    * `a`: First tensor to add
    * `b`: Second tensor to add

**Note**: Operation returns a new ndarray with the result of a and b.

**Example Code**:
```c

/* add two 3 X 3 ndarrays */
ndarray_t *t1 = ndarray(2, (int[]){3, 3}); 
ndarray_t *t2 = ndarray(2, (int[]){3, 3}); 
ndarray_t *result = nadd(t1, t2);
```
<hr>

### `nsubtract(t1, t2)`

<hr>
* **Parameters**<br>
    * `t1`: First tensor to subtract
    * `t2`: Second tensor to subtract

**Note**: Operation returns a new ndarray with the result of a and b.

**Example Code**:
```c

/* add two 3 X 3 ndarrays */
ndarray_t *t1 = ndarray(2, (int[]){3, 3}); 
ndarray_t *t2 = ndarray(2, (int[]){3, 3}); 
ndarray_t *result = nsubtract(t1, t2);
```
<hr>


### `nscale_add(a, b)`

<hr>
* **Parameters**<br>
    * `a`: First tensor to scale add
    * `b`: Second tensor to scale add

**Note**: Operation returns a new ndarray with the result of a and b.

**Example Code**:
```c

/* add two 3 X 3 ndarrays */
ndarray_t *t1 = ndarray(2, (int[]){3, 3}); 
ndarray_t *t2 = ndarray(2, (int[]){1, 3}); /* 1  X 3 */
ndarray_t *result = nscale_add(t1, t2);
```
<hr>


### `ntranspose(t)`

<hr>
* **Parameters**<br>
    * `t`: Instance of ndarray to perform transpose on

**Note**: Operation returns a new ndarray with the result of tranpose operation.

**Example Code**:
```c

/* add two 3 X 3 ndarrays */
ndarray_t *t1 = ndarray(2, (int[]){3, 4}); 
ndarray_t *result = ntranspose(t1); /* 4 X 3 ndarray */

```
<hr>


### `permute(t)`

<hr>
* **Parameters**<br>
    * `t`: Instance of ndarray to perform permute/contraction on

**Note**: Operation returns a new ndarray with the result of contraction.

**Example Code**:
```c

/* add two 3 X 3 ndarrays */
ndarray_t *t1 = ndarray(3, (int[]){3, 4, 5}); 
ndarray_t *result = permute(t1, (int[]){2, 1, 0}); /* 5 X 4 X 3  ndarray */

```
<hr>


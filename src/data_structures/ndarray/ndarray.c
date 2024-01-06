#include "includes/ndarray.h"


ndarray_t *ndarray(int rank, int *shape) {

    /* init attibutes */
	ndarray_t *tensor = (ndarray_t*)malloc(sizeof(ndarray_t));
    tensor->rank = rank; 
    tensor->shape = malloc(rank * sizeof(int));
    tensor->status = true; 

    /* copy shape */
    int tensor_size = 1;
    for(int i = 0; i < rank; i++){
        tensor->shape[i] = shape[i];
        tensor_size *= shape[i];
    }
    tensor->size = tensor_size;

    /* allocate tensor values */
    tensor->values = malloc(tensor_size * sizeof(double)); 
    for(int i  = 0; i < tensor_size; i++){
        tensor->values[i] = 0.00;    
    }

    return tensor; 
} 


int *reshape(ndarray_t *t, int rank, int *indices) {

    t->rank = rank; 
	t->shape = realloc(t->shape, t->rank * sizeof(int));

    int accum = 1;
    for(int j = 0; j < t->rank; j++){
        t->shape[j] = indices[j];
        accum *= indices[j];
    }

    if(accum != t->size){
        printf("Reshape invalid, %d != %d\n", accum, t->size);
        t->status = false;
        exit(0); 
    } 

    return t->shape;
}


int nindex(ndarray_t *t, int *indices) {
    int stride = 1, offset = 0, index = 0; 
    for(int k = t->rank-1; k >= 0; k--){
        int val = stride * indices[k];
        stride *= t->shape[k]; 
        index += val; 
    }
    return index; 
}


int *indices(ndarray_t *t, int index) {

    /* Get the indices for a dimension based on it's index */
    int *indexs = malloc(t->rank * sizeof(int)); 
    int count = t->rank-1, curr_index = index; 
    for(int k = 0; k < t->rank-1; k++){
        int dim_size = t->shape[k];
        indexs[count] = curr_index % dim_size;
        curr_index /= dim_size;
        count -= 1;
    }
    
    /* calculcate final offset*/
    indexs[0] = curr_index;
    return indexs; 
} 

double nidx(ndarray_t *t, int *indices) {
    int index = nindex(t, indices); 
    return t->values[index]; 
}


void nset(ndarray_t *t, int *indices, double value) {
    int index = nindex(t, indices); 
    t->values[index] = value; 
}


ndarray_t *napply(double(*activation_function)(double), ndarray_t *t) {
    for(int i = 0; i < t->size; i++){
        t->values[i] = (*activation_function)(t->values[i]);
    }
    return t; 
}


void save_ndarray(ndarray_t *t, char *filename) {

	FILE* file = fopen(filename, "w");
	fprintf(file, "rank: %d\n", t->rank);

    /* validate if file path exists */

	for (int i = 0; i < t->rank; i++) {
		fprintf(file, "dim: %d\n", t->shape[i]);
	}

	for (int n = 0; n < t->size; n++) {
		fprintf(file, "%.2f\n", t->values[n]);
	}
	fclose(file);
}


ndarray_t *load_ndarray(char *filename) {

    /* open file */
	FILE* fp = fopen(filename, "r");
    char file_buffer[1024];
    int counter = 0;

    /* validate if file path exists */

    /* read activation config */
    int rank; 
    fscanf(fp, "rank: %d\n", &rank);

    /* load dimensions */
    int *dims = malloc(rank * sizeof(int)); 
    for(int i = 0; i < rank; i++){
        int dim;
        fscanf(fp, "dim: %d\n", &dim);
        dims[i] = dim;  
    }

    /* load values to tensor */
    ndarray_t *t = ndarray(rank, dims);
	while(fgets(file_buffer, 1024, fp)) {
        int len = strlen(file_buffer); 
        if(file_buffer[len-1] == '\n') {
            file_buffer[len-1] = '\0'; 
        }
        double val = atof(file_buffer); 
        t->values[counter] = val;
        counter += 1;         
    }

    return t;
}


void print_tensor(ndarray_t *t){
    printf("Shape: ");
    printf("(");
    for(int n = 0; n < t->rank; n++){
        printf("%d,", t->shape[n]); 
    }
    printf(")\n");
    printf("[");
    for(int i = 0; i < t->size; i++){
        printf("%.2f ", t->values[i]); 
    }
    printf("]");
    printf("\n"); 
}


void err_msg(ndarray_t *t, char *err_msg) {
    t->err_msg = malloc(strlen(err_msg) * sizeof(err_msg));
    strcpy(t->err_msg, err_msg);
    t->status = false; 
} 


#ifndef NDARRAY_H
#define NDARRAY_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>
#include <time.h> 
#include <immintrin.h>



struct NDArray {
    int rank, size; 
    int *shape; 
    double *values;
    bool status;
    char *err_msg; 
}; 

typedef struct NDArray ndarray_t;

/* creation */
ndarray_t *ndarray(int rank, int *shape);

/* utils  */
int *reshape(ndarray_t *t, int rank, int *indices);
int nindex(ndarray_t *t, int *indices);
int *indices(ndarray_t *t, int index);
double *rows(ndarray_t *t, int row_num);
double *cols(ndarray_t *t, int col_num);
double nidx(ndarray_t *t, int *indices);  
void nset(ndarray_t *t, int *indices, double value);
void fill(ndarray_t *t, double value); 
ndarray_t *napply(double(*activation_function)(double), ndarray_t *t); 

/* save and load operations */
void save_ndarray(ndarray_t *t, char *filename);
ndarray_t *load_ndarray(char *filename);

/* printing debugging methods */
void print_tensor(ndarray_t *t); 
void matrix(ndarray_t *t); 
void err_msg(ndarray_t *t, char *err_msg); 

#endif
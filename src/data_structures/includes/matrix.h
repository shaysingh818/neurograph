#ifndef MATRIX_H
#define MATRIX_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>
#include <time.h> 

/* constants */
#define MAXCHAR 100

struct Matrix {
    int rows; 
    int cols; 
    double **arr; 
}; 

typedef struct Matrix mat_t; 


/* matrix utilities */
mat_t *init_vec(int rows, int cols, bool identity);
mat_t *init_matrix(int rows, int cols);
mat_t *apply(double(*activation_function)(double), mat_t *m);  
mat_t *copy_matrix(mat_t *m);
mat_t *load_matrix(char *filename);
mat_t **to_rows(mat_t *m);
mat_t **to_cols(mat_t *m); 
mat_t **batch_rows(mat_t *m, int limit); 
mat_t *copy_arr_to_matrix(int m, int n, double arr[m][n]);  

bool compare_matrix(mat_t *m, mat_t *n); 
double uniform_distribution(double low, double high); 
void copy_mat(mat_t *v1, mat_t *v2);
void print_vec(mat_t *v1);
void matrix_free(mat_t *m);  
void randomize(mat_t *mat, int n); 
void print_matrix(mat_t *mat);
void fill_mat(mat_t *m, int n); 
void save_matrix(mat_t *m, char *filename);   

/* matrix operations*/
mat_t *scalar_multiply(mat_t *v1, double value);
mat_t *power(mat_t *v1, int power);
mat_t *dot(mat_t *n, mat_t *m);
mat_t *multiply(mat_t *v1, mat_t *v2);
mat_t *elementwise_multiply(mat_t *v1, mat_t *v2); 
mat_t *add(mat_t *n, mat_t *m);
mat_t *scale(mat_t *v, double value); 
mat_t *scale_add(mat_t *n, mat_t *m);
mat_t *transpose(mat_t *n);
mat_t *difference(mat_t *x, mat_t *y);
mat_t *vectorize(mat_t *input); 
mat_t *im2col(mat_t *input, mat_t *feature_map); 

#endif
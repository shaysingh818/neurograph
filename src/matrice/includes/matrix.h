#ifndef MATRIX_H
#define MATRIX_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h> 

struct Vector {
    int rows; 
    int cols; 
    double **items; 
}; 

typedef struct Vector vec_t; 


/* represents an entry in a matrice */
struct Entry {
    int id; 
    char *label;
}; 

typedef struct Entry entry_t; 


struct MatrixGraph {
    int rows;
    int cols; /* in case the rows and cols aren't equal*/
    int vertices;
    int *weights; /* weights for matrice graph relationships */
    entry_t **matrix;
};

typedef struct MatrixGraph mat_t;

/* create standard vector */
vec_t *init_vec(int rows, int cols, bool identity);
vec_t *multiply(vec_t *v1, vec_t *v2); 
vec_t *scalar_multiply(vec_t *v1, double value);
vec_t *power(vec_t *v1, int power); 

/* useful utilities (for label propogation) */
void copy_mat(vec_t *v1, vec_t *v2);

/* print vec */
void print_vec(vec_t *v1); 


/* entry instance */
entry_t *init_entry(int id, char *label); 
entry_t *search_entry_by_id(mat_t *m, int id);

/* matrice instance */ 
mat_t *init_mat(int set_rows, int set_cols); 
mat_t *init_matrice_graph(int vertices);

/* insert method */ 
void insert(mat_t *m, entry_t *src, entry_t *dst, int weight, bool directed);

/* formatter methods */
void print_matrix_ids(mat_t *m);
void print_matrix_weights(mat_t *m);
void print_matrix_labels(mat_t *m);


#endif


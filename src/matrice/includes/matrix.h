#ifndef MATRIX_H
#define MATRIX_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h> 


/* represents an entry in a matrice */
struct Entry {
    int id; 
    char *label; 
}; 

typedef struct Entry entry_t; 


struct Matrix {
    int rows;
    int cols; /* in case the rows and cols aren't equal*/
    int vertices;
    int *weights; /* weights for matrice graph relationships */
    entry_t **matrix;
};

typedef struct Matrix mat_t;


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


/* graph methods */
void bfs_mat(mat_t *m, int value); 
void dfs_mat(mat_t *m, int value); 
void degree_centrality_mat(mat_t *m, int value); 

#endif


#ifndef MATRIX_H
#define MATRIX_H

#include <stdio.h>
#include <stdlib.h>

struct Matrix {
    int vertices;
    int edges;
    int **arr;
};

typedef struct Matrix mat_t;


/* adjacency matrix methods */
mat_t *init_mat(int vertices, int edges);
void entry(mat_t *m, int v1, int v2);
void weighted_entry(mat_t *m, int v1, int v2, int weight);
void print_matrix(mat_t *m);

#endif


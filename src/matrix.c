#include "includes/matrix.h"

mat_t *init_mat(int vertices, int edges) {

	mat_t *m;
	m = (mat_t*)malloc(sizeof(mat_t)); 
	m->vertices = vertices;
   	m->edges = edges; 	

	m->arr = malloc(sizeof(int*)*m->vertices); 
	for(int i = 0; i < m->edges; i++){
		m->arr[i] = malloc(sizeof(int)*m->edges); 
	}

	return m; 
}


void entry(mat_t *m, int v1, int v2) {
	if(v1 == v2) {
		printf("Same vertice %d and  %d\n", v1, v2); 
	}
	m->arr[v1][v2] = 1; 
	m->arr[v2][v1] = 1; 
}


void weighted_entry(mat_t *m, int v1, int v2, int weight) {
	if(v1 == v2) {
		printf("Same vertice %d and  %d\n", v1, v2); 
	}
	m->arr[v1][v2] = weight; 
	m->arr[v2][v1] = weight; 
}


void print_matrix(mat_t *m) {
	for(int i = 0; i < m->vertices; i++) {
		for(int j = 0; j < m->edges; j++){
			printf("%d ", m->arr[i][j]); 			
		}
		printf("\n"); 
	}
}


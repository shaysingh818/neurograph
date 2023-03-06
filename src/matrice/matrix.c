#include "includes/matrix.h"

entry_t *init_entry(int id, char *label) {

	entry_t *e;
	e = (entry_t*)malloc(sizeof(entry_t)); 

	size_t label_size = strlen(label) + 1; 
	e->label = malloc(label_size * sizeof(char)); 
	e->id = id; 

	strcpy(e->label, label); 
	return e; 
}


mat_t *init_matrice_graph(int vertices) {

	mat_t *m;
	m = (mat_t*)malloc(sizeof(mat_t)); 
	m->vertices = vertices;

	/* allocate matrice */
	m->matrix = malloc(sizeof(entry_t*) * vertices * vertices); 
	if(m->matrix != NULL) {
		for(int i = 0; i < vertices; i++){
			for(int j = 0; j < vertices; j++){
				m->matrix[i*vertices+j] = (entry_t*)malloc(sizeof(entry_t));
				m->matrix[i*vertices+j]->id = -1;  
			}
		}
	}

	/* allocate weights with samed dimension */
	m->weights = malloc(sizeof(int*) * vertices * vertices); 
	if(m->weights != NULL) {
		for(int i = 0; i < vertices; i++){
			for(int j = 0; j < vertices; j++){
				m->weights[i*vertices+j] = -1;  
			}
		}
	}

	return m; 
}


void insert(mat_t *m, entry_t *src, entry_t *dst, int weight,  bool directed) {

	int src_id = src->id; 
	int dst_id = dst->id; 	
	int directed_index = src_id*m->vertices+dst_id;
	int undirected_index = dst_id*m->vertices+src_id;  

	if(directed) {
		m->matrix[directed_index] = dst;
		m->weights[directed_index] = weight;  
	} else {

		/* add node values */
		m->matrix[directed_index] = dst; 
		m->matrix[undirected_index] = src;  

		/* add weights */
		m->weights[directed_index] = weight; 
		m->weights[undirected_index] = weight;  
	}

}


void print_matrix_ids(mat_t *m) {
	for(int i = 0; i < m->vertices; i++) {
		for(int j = 0; j < m->vertices; j++){
			printf("%d ", m->matrix[i*m->vertices+j]->id); 			
		}
		printf("\n"); 
	}
}


void print_matrix_labels(mat_t *m) {
	for(int i = 0; i < m->vertices; i++) {
		printf("%d : ", i); 
		for(int j = 0; j < m->vertices; j++){
			if(m->matrix[i*m->vertices+j]->label != NULL){
				printf("-> %s", m->matrix[i*m->vertices+j]->label); 			
			}
		}
		printf("\n"); 
	}
}


void print_matrix_weights(mat_t *m) {
	for(int i = 0; i < m->vertices; i++) {
		printf("%d : ", i); 
		for(int j = 0; j < m->vertices; j++){
			if(m->matrix[i*m->vertices+j]->label != NULL){
				printf("-> %d", m->weights[i*m->vertices+j]); 			
			}
		}
		printf("\n"); 
	}
}


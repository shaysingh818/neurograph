#include "includes/matrix.h"


vec_t *init_vec(int rows, int cols, bool identity) {

	vec_t *v;
	v = (vec_t*)malloc(sizeof(vec_t)); 
	v->rows = rows;
	v->cols = cols;

	/* allocate matrice */
	v->items = malloc(sizeof(double*)*v->rows); 
	for(int i = 0; i < v->rows; i++){
		v->items[i] = malloc(sizeof(double) * v->cols);
	}

	if(identity){
		for(int i = 0; i < v->rows; i++){
			v->items[i][i] = 1; 
		}
	}

	return v; 
}


vec_t *scalar_multiply(vec_t *v, double value) {

	/* this assumes the matrix is upper triangular */
	vec_t *result = init_vec(v->rows, v->cols, false); 

	for(int i = 0; i < v->rows; i++){
		double slot; 
		for(int j = 0; j < v->cols; j++){
			slot = (value / v->items[i][j]) / value;
			if(i == j){
				result->items[i][j] = slot; 		
			}
		}
	}

	return result;
}

vec_t *scale(vec_t *v, double value) {

	/* this assumes the matrix is upper triangular */
	vec_t *result = init_vec(v->rows, v->cols, false); 

	for(int i = 0; i < v->rows; i++){
		double slot; 
		for(int j = 0; j < v->cols; j++){
			result->items[i][j] *= value; 		
		}
	}

	return result;
}


void copy_mat(vec_t *v1, vec_t *v2){

	if(v1->rows != v2->cols){
		printf("Bad matrix\n"); 
	}

	for(int j = 0; j < v1->rows; j++){
		for(int i = 0; i < v1->cols; i++){
			v1->items[i][j] = v2->items[i][j]; 
		} 
	} 

}


vec_t *multiply(vec_t *v1, vec_t *v2) {

	if(v1->cols != v2->rows){
		printf("cannot multiply\n"); 
	}

	vec_t *result = init_vec(v1->rows, v1->cols, false);

	for(int i = 0; i < v1->rows; i++){
		for(int j = 0; j < v1->cols; j++){
			result->items[i][j] = 0; 	

			for(int n = 0; n < v1->rows; n++){
				double value = v2->items[i][n] * v1->items[n][j];
				result->items[i][j] += value; 
			}
		} 
	} 

	return result;
}


vec_t *power(vec_t *v1, int power) {

	/* temp matrice */
	int i, j, k; 
	vec_t *temp = init_vec(v1->rows, v1->cols, false);  

	/* init result matrix to identity */
	vec_t *result = init_vec(v1->rows, v1->cols, true);

	/* multiply matrix by itself for power */
	while(power > 0){

		if(power % 2 == 1){

			/* if the power is odd, multiply result by matrix */
			temp = multiply(result, v1); 
			copy_mat(result, temp); 

		}

		vec_t *x = multiply(v1, v1); 
		copy_mat(result, x); 
		copy_mat(v1, result);
		
		power /= 2; 
	}

	return result; 

} 

vec_t *dot(vec_t *n, vec_t *m){
	
	// check if matrix m has equal rows as cols of n
	vec_t *result_mat = init_vec(n->rows, m->cols, false);

    if(n->cols == m->rows) {
        for(int i = 0; i < n->rows; i++){
            for(int j = 0; j < m->cols; j++){
				double sum = 0; 
				for(int k = 0; k < m->rows; k++){
					sum += n->items[i][k] * m->items[k][j];
				}
				result_mat->items[i][j] = sum; 
            }
        }        
    }

	return result_mat; 	
}

vec_t *add(vec_t *n, vec_t *m){

	vec_t *result_mat = init_vec(n->rows, n->cols, false); 
	// confirm that cols of m are equal to n
	for(int i = 0; i < n->rows; i++){
		for(int j = 0; j < m->cols; j++){
			double value = n->items[i][j] + m->items[i][j];
			result_mat->items[i][j] = value;  
		}
	}

	return result_mat; 
}


vec_t *scale_add(vec_t *n, vec_t *m){

	vec_t *result_mat = init_vec(n->rows, n->cols, false); 
	for(int i = 0; i < n->rows; i++){
		for(int j = 0; j < n->cols; j++){
			double value = n->items[i][j] +  m->items[0][j];  
			result_mat->items[i][j] = value;
		}
	}

	return result_mat; 
}


vec_t *transpose(vec_t *n){

	vec_t *result_mat = init_vec(n->cols, n->rows, false); 
	for(int i = 0; i < n->rows; i++){
		for(int j = 0; j < n->cols; j++){
			result_mat->items[j][i] = n->items[i][j];  
		}
	}		

	return result_mat; 
}


vec_t *difference(vec_t *x, vec_t *y){

	vec_t *result = init_vec(x->rows, x->cols, false); 
	for(int i = 0; i < x->rows; i++){
		for(int j = 0; j < x->cols; j++){
			result->items[i][j] = x->items[i][j] - y->items[i][j];  
		}
	}

	return result; 
}

vec_t *apply(double(*activation_function)(double), vec_t *m) {

	vec_t *result = init_vec(m->rows, m->cols, false); 

	for(int i = 0; i < m->rows; i++){
		for(int j = 0; j < m->cols; j++){
			result->items[i][j] = (*activation_function)(m->items[i][j]);
		}
	}

	return result; 
}


double uniform_distribution(double low, double high) {
	double difference = high - low; // The difference between the two
	int scale = 10000;
	int scaled_difference = (int)(difference * scale);
	return low + (1.0 * (rand() % scaled_difference) / scale);
}


void print_vec(vec_t *v) {
	for(int i = 0; i < v->rows; i++){
		for(int j = 0; j < v->cols; j++){
			printf(" %.2f", v->items[i][j]); 
		}
		printf("\n"); 
	}
}


entry_t *init_entry(int id, char *label) {

	entry_t *e;
	e = (entry_t*)malloc(sizeof(entry_t)); 

	size_t label_size = strlen(label) + 1; 
	e->label = malloc(label_size * sizeof(char)); 
	e->id = id;

	strcpy(e->label, label); 
	return e; 
}

entry_t *search_entry_by_id(mat_t *m, int search_id){

	for(int i = 0; i < m->vertices; i++) {
		for(int j = 0; j < m->vertices; j++){
			int id = m->matrix[i*m->vertices+j]->id; 
			if(search_id == id){
				return m->matrix[i*m->vertices+j]; 
			}
		}
	}
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

void randomize(vec_t *vec, int n){
	srand((unsigned)time(NULL));
	double min = -1.0 / sqrt(n);
	double max = 1.0 / sqrt(n);
	for(int i = 0; i < vec->rows; i++){
		for(int j = 0; j < vec->cols; j++){
			vec->items[i][j] = uniform_distribution(min, max); 	
		}
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


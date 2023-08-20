#include "includes/matrix.h"


mat_t *init_vec(int rows, int cols, bool identity) {

	mat_t *v;
	v = (mat_t*)malloc(sizeof(mat_t)); 
	v->rows = rows;
	v->cols = cols;

	/* allocate matrice */
	v->arr = malloc(sizeof(double*)*v->rows); 
	for(int i = 0; i < v->rows; i++){
		v->arr[i] = malloc(sizeof(double) * v->cols);
	}

	if(identity){
		for(int i = 0; i < v->rows; i++){
			v->arr[i][i] = 1; 
		}
	}

	return v; 
}

mat_t *init_matrix(int rows, int cols){

	mat_t *mat; 
	mat = (mat_t*)malloc(sizeof(mat_t)); 
	mat->rows = rows; 
	mat->cols = cols; 

	mat->arr = malloc(sizeof(double*)*mat->rows);
	for(int i = 0; i < mat->rows; i++){
		mat->arr[i] = malloc(sizeof(double)*mat->cols);
	}	

	return mat; 
}


mat_t *copy_matrix(mat_t *m){
	mat_t *new = init_matrix(m->rows, m->cols); 
	for(int i = 0; i < m->rows; i++){
		for(int j = 0; j < m->cols; j++){
            new->arr[i][j] = m->arr[i][j];
		}
	}
	return new; 
}

void save_matrix(mat_t *m, char* filename) {
	FILE* file = fopen(filename, "w");
	fprintf(file, "%d\n", m->rows);
	fprintf(file, "%d\n", m->cols);
	for (int i = 0; i < m->rows; i++) {
		for (int j = 0; j < m->cols; j++) {
			fprintf(file, "%.2f\n", m->arr[i][j]);
		}
	}
	fclose(file);
}

mat_t *load_matrix(char *filename) {
	FILE* file = fopen(filename, "r");
	char entry[MAXCHAR]; 
	fgets(entry, MAXCHAR, file);
	int rows = atoi(entry);
	fgets(entry, MAXCHAR, file);
	int cols = atoi(entry);
	mat_t *m = init_matrix(rows, cols);
	for (int i = 0; i < m->rows; i++) {
		for (int j = 0; j < m->cols; j++) {
			fgets(entry, MAXCHAR, file);
			m->arr[i][j] = atof(entry);
		}
	}
	fclose(file);
	return m;
}

mat_t **to_rows(mat_t *m) {

    mat_t **rows = (mat_t**)malloc(sizeof(mat_t*));
	for(int i = 0; i < m->rows; i++){
		rows[i] = malloc(sizeof(mat_t)); 	
	}

	for(int i = 0; i < m->rows; i++){
		mat_t *temp = init_matrix(1, m->cols); 
		for(int j = 0; j < m->cols; j++){
            temp->arr[0][j] = m->arr[i][j];
		}
		rows[i] = copy_matrix(temp); 
	}
	return rows; 
}


mat_t **to_cols(mat_t *m) {

    mat_t **cols = (mat_t**)malloc(sizeof(mat_t*));
	for(int i = 0; i < m->cols; i++){
		cols[i] = malloc(sizeof(mat_t)); 	
	}

	for(int i = 0; i < m->rows; i++){
		mat_t *temp = init_matrix(1, m->cols); 
		for(int j = 0; j < m->cols; j++){
			temp->arr[0][j] = m->arr[j][i]; 
		}
		cols[i] = copy_matrix(temp); 
	}

	return cols; 
}


mat_t **batch_rows(mat_t *m, int limit) {

	/* limit can't be greater than the rows */
	if(limit > m->rows) {
		printf("Limit supplied is greater than the amount of rows\n"); 
		exit(1); 
	}

	/* batch rows */
    mat_t **rows = (mat_t**)malloc(sizeof(mat_t*));
	for(int i = 0; i < limit; i++){
		rows[i] = malloc(sizeof(mat_t)); 	
	}

	for(int i = 0; i < limit; i++){
		mat_t *temp = init_matrix(1, m->cols); 
		for(int j = 0; j < m->cols; j++){
            temp->arr[0][j] = m->arr[i][j];
		}
		rows[i] = copy_matrix(temp); 
	}
	return rows; 
} 


mat_t *copy_arr_to_matrix(int m, int n, double arr[m][n]) {
    mat_t *matrix = init_vec(m, n, false);
    for(int i = 0; i < matrix->rows; i++){
        for(int j = 0; j < matrix->cols; j++){
            matrix->arr[i][j] = arr[i][j];
        }
    }
	return matrix; 
} 



bool compare_matrix(mat_t *n, mat_t *m){
	
    if (n->rows != m->rows || n->cols != m->cols) {
        printf("Error: matrices must be of the same size for comparison\n");
        exit(1);
    }

	bool result = true; 
	for(int i = 0; i < n->rows; i++){
		for(int j = 0; j < n->cols; j++){
			double rounded_value = round(m->arr[i][j]*100)/100;
			bool test = n->arr[i][j] == rounded_value; 
			printf("%.2f : %.2f -> %d\n", rounded_value, n->arr[i][j], test); 
			if(n->arr[i][j] != rounded_value){
				result = false; 
			}
		}
	}
	return result; 
}


mat_t *scalar_multiply(mat_t *v, double value) {

	/* this assumes the matrix is upper triangular */
	mat_t *result = init_matrix(v->rows, v->cols); 

	for(int i = 0; i < v->rows; i++){
		double slot; 
		for(int j = 0; j < v->cols; j++){
			slot = (value / v->arr[i][j]) / value;
			if(i == j){
				result->arr[i][j] = slot; 		
			}
		}
	}

	return result;
}


mat_t *scale(mat_t *n, double value){

	mat_t *result_mat = init_matrix(n->rows, n->cols); 
	for(int i = 0; i < n->rows; i++){
		for(int j = 0; j < n->cols; j++){
			double temp = n->arr[i][j] *= value;  
			result_mat->arr[i][j] = temp;
		}
	}

	return result_mat; 
}

mat_t *scale_add(mat_t *n, mat_t *m){

	mat_t *result_mat = init_matrix(n->rows, n->cols); 
	for(int i = 0; i < n->rows; i++){
		for(int j = 0; j < n->cols; j++){
			double value = n->arr[i][j] +  m->arr[0][j];  
			result_mat->arr[i][j] = value;
		}
	}

	return result_mat; 
}


void copy_mat(mat_t *v1, mat_t *v2){

	if(v1->rows != v2->cols){
		printf("Bad matrix\n"); 
	}

	for(int j = 0; j < v1->rows; j++){
		for(int i = 0; i < v1->cols; i++){
			v1->arr[i][j] = v2->arr[i][j]; 
		} 
	} 

}


mat_t *multiply(mat_t *v1, mat_t *v2) {

	if(v1->cols != v2->rows){
		printf("cannot multiply\n"); 
	}

	mat_t *result = init_matrix(v1->rows, v1->cols);

	for(int i = 0; i < v1->rows; i++){
		for(int j = 0; j < v1->cols; j++){
			result->arr[i][j] = 0; 	

			for(int n = 0; n < v1->rows; n++){
				double value = v2->arr[i][n] * v1->arr[n][j];
				result->arr[i][j] += value; 
			}
		} 
	} 

	return result;
}


mat_t *elementwise_multiply(mat_t *v1, mat_t *v2) {

    if (v1->rows != v2->rows || v1->cols != v2->cols) {
        printf("Error: matrices must be of the same size for element-wise multiplication");
        exit(1);
    }

    mat_t *result = init_matrix(v1->rows, v1->cols);

    for (int i = 0; i < v1->rows; i++) {
        for (int j = 0; j < v1->cols; j++) {
            result->arr[i][j] = v1->arr[i][j] * v2->arr[i][j];
        }
    }

    return result;
}


mat_t *power(mat_t *v1, int power) {

	/* temp matrice */
	int i, j, k; 
	mat_t *temp = init_matrix(v1->rows, v1->cols);  

	/* init result matrix to identity */
	mat_t *result = init_matrix(v1->rows, v1->cols);

	/* multiply matrix by itself for power */
	while(power > 0){

		if(power % 2 == 1){

			/* if the power is odd, multiply result by matrix */
			temp = multiply(result, v1); 
			copy_mat(result, temp); 

		}

		mat_t *x = multiply(v1, v1); 
		copy_mat(result, x); 
		copy_mat(v1, result);
		
		power /= 2; 
	}

	return result; 

} 

/* operations */
mat_t *dot(mat_t *n, mat_t *m){	
    if(n->cols == m->rows) {
		mat_t *result_mat = init_matrix(n->rows, m->cols);
        for(int i = 0; i < n->rows; i++){
            for(int j = 0; j < m->cols; j++){
				double sum = 0; 
				for(int k = 0; k < m->rows; k++){
					sum += n->arr[i][k] * m->arr[k][j];
				}
				result_mat->arr[i][j] = sum; 
            }
        }
		return result_mat; 	
    } else {
		printf("Dimension mismatch for dot product\n");
		exit(1);  
	}

}

mat_t *add(mat_t *n, mat_t *m){

	mat_t *result_mat = init_matrix(n->rows, n->cols); 
	// confirm that cols of m are equal to n
	for(int i = 0; i < n->rows; i++){
		for(int j = 0; j < m->cols; j++){
			double value = n->arr[i][j] + m->arr[i][j];
			result_mat->arr[i][j] = value;  
		}
	}

	return result_mat; 
}


mat_t *transpose(mat_t *n){

	mat_t *result_mat = init_matrix(n->cols, n->rows); 
	for(int i = 0; i < n->rows; i++){
		for(int j = 0; j < n->cols; j++){
			result_mat->arr[j][i] = n->arr[i][j];  
		}
	}		

	return result_mat; 
}


mat_t *difference(mat_t *x, mat_t *y){

	mat_t *result = init_matrix(x->rows, x->cols); 
	for(int i = 0; i < x->rows; i++){
		for(int j = 0; j < x->cols; j++){
			result->arr[i][j] = x->arr[i][j] - y->arr[i][j];  
		}
	}

	return result; 
}

mat_t *apply(double(*activation_function)(double), mat_t *m) {

	mat_t *result = init_matrix(m->rows, m->cols); 

	for(int i = 0; i < m->rows; i++){
		for(int j = 0; j < m->cols; j++){
			result->arr[i][j] = (*activation_function)(m->arr[i][j]);
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


void print_vec(mat_t *v) {
	for(int i = 0; i < v->rows; i++){
		for(int j = 0; j < v->cols; j++){
			printf(" %.2f", v->arr[i][j]); 
		}
		printf("\n"); 
	}
}

void randomize(mat_t *vec, int n){
	srand((unsigned)time(NULL));
	double min = -1.0 / sqrt(n);
	double max = 1.0 / sqrt(n);
	for(int i = 0; i < vec->rows; i++){
		for(int j = 0; j < vec->cols; j++){
			vec->arr[i][j] = uniform_distribution(min, max); 	
		}
	}
}

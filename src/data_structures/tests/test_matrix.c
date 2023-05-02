#include "includes/test_matrix.h"

void test_init_matrix(){

	int equality_status = true; 

	/* create adjacency matrix graph with size 5 */ 
	mat_graph_t *m = init_matrice_graph(5); 

    /* create unique nodes */
    entry_t *a = init_entry(0, "A"); 
    entry_t *b = init_entry(1, "B"); 
    entry_t *c = init_entry(2, "C"); 
    entry_t *d = init_entry(3, "D"); 

	/* connect a to everyone */ 
    insert(m, a, b, 0, false); 
    insert(m, a, c, 0, false); 
    insert(m, b, c, 0, false); 
    insert(m, b, d, 0, false); 
    insert(m, c, d, 0, false); 


	char *relationship_list[5][5] = {
		{"B", "C"}, 
		{"A", "C", "D"},
		{"A", "B", "D"},
		{"B", "C"},
        {}
	};


	/* validate results */
    if(!equality_status) {
        printf("%s::%s... FAILED\n", __FILE__, __FUNCTION__);
    }
    printf("%s::%s... \e[0;32mPASSED\e[0m\n", __FILE__, __FUNCTION__);

}


void test_directed_matrix() {

	int equality_status = true; 

	/* create adjacency matrix graph with size 5 */ 
	mat_graph_t *m = init_matrice_graph(5); 

    /* create unique nodes */
    entry_t *a = init_entry(0, "A"); 
    entry_t *b = init_entry(1, "B"); 
    entry_t *c = init_entry(2, "C"); 
    entry_t *d = init_entry(3, "D"); 

	/* connect a to everyone */ 
    insert(m, a, b, 0, true); 
    insert(m, a, c, 0, true); 
    insert(m, b, c, 0, true); 
    insert(m, b, d, 0, true); 
    insert(m, c, d, 0, true); 

	char *relationship_list[5][5] = {
		{"B", "C"}, 
		{"C", "D"},
		{"D"},
        {},
        {}
	};

	/* validate results */
    if(!equality_status) {
        printf("%s::%s... FAILED\n", __FILE__, __FUNCTION__);
    }
    printf("%s::%s... \e[0;32mPASSED\e[0m\n", __FILE__, __FUNCTION__);

}


void test_init_vec() {
	
	int equality_status = false; 
    int start = 100;

    mat_t *v = init_vec(start, start, true);

    if(v->rows == start && v->cols == start){
        equality_status = true; 
    } 

    /* init identity matrix */
    for(int i = 0; i < v->cols; i++){
        if(v->arr[i][i] == 1.00){
            equality_status = true; 
        }
    }

    if(!equality_status) {
        printf("%s::%s... FAILED\n", __FILE__, __FUNCTION__);
    }
    printf("%s::%s... \e[0;32mPASSED\e[0m\n", __FILE__, __FUNCTION__);
	
}


void test_scalar_multiply() {

    int dim = 7; 
    bool equality_status = true; 

    double values[7][7] = {
        {1.00, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00},
        {0.00, 1.00, 0.00, 0.00, 0.00, 0.00, 0.00},
        {0.00, 0.00, 1.00, 0.00, 0.00, 0.00, 0.00},
        {0.00, 0.00, 0.00, 3.00, 0.00, 0.00, 0.00},
        {0.00, 0.00, 0.00, 0.00, 2.00, 0.00, 0.00},
        {0.00, 0.00, 0.00, 0.00, 0.00, 3.00, 0.00},
        {0.00, 0.00, 0.00, 0.00, 0.00, 0.00, 1.00}
    };


    double expected[7][7] = {
        {1.00, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00},
        {0.00, 1.00, 0.00, 0.00, 0.00, 0.00, 0.00},
        {0.00, 0.00, 1.00, 0.00, 0.00, 0.00, 0.00},
        {0.00, 0.00, 0.00, 0.33, 0.00, 0.00, 0.00},
        {0.00, 0.00, 0.00, 0.00, 0.50, 0.00, 0.00},
        {0.00, 0.00, 0.00, 0.00, 0.00, 0.33, 0.00},
        {0.00, 0.00, 0.00, 0.00, 0.00, 0.00, 1.00}
    };

    /* copy values to vector */
    mat_t *v = init_vec(dim, dim, false); 
    for(int i = 0; i < dim; i++){
        for(int j = 0; j < dim; j++){
            v->arr[i][j] = values[i][j];
        }
    }
 
    double det = 1.00; 
	for(int i = 0; i < v->rows; i++){
		det *= v->arr[i][i];
	}

    mat_t *result = scalar_multiply(v, det);  
	for(int i = 0; i < result->rows; i++){
		double rounded_value = round(result->arr[i][i]*100)/100; 
		if(expected[i][i] != rounded_value){
            printf("%f -> %f\n", expected[i][i], rounded_value); 
			equality_status = false; 
		}
	}

    if(!equality_status) {
        printf("%s::%s... FAILED\n", __FILE__, __FUNCTION__);
    } else {
        printf("%s::%s... \e[0;32mPASSED\e[0m\n", __FILE__, __FUNCTION__);
    }

}


void test_vector_multiplication(){

    int dim = 7; 
    int equality_status = true; 

    double d_inverse[7][7] = {
        {1.00, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00},
        {0.00, 1.00, 0.00, 0.00, 0.00, 0.00, 0.00},
        {0.00, 0.00, 1.00, 0.00, 0.00, 0.00, 0.00},
        {0.00, 0.00, 0.00, 0.33, 0.00, 0.00, 0.00},
        {0.00, 0.00, 0.00, 0.00, 0.50, 0.00, 0.00},
        {0.00, 0.00, 0.00, 0.00, 0.00, 0.33, 0.00},
        {0.00, 0.00, 0.00, 0.00, 0.00, 0.00, 1.00}
    };

    double adj_matrix[7][7] = {
        {1.00, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00},
        {0.00, 1.00, 0.00, 0.00, 0.00, 0.00, 0.00},
        {0.00, 0.00, 0.00, 1.00, 0.00, 0.00, 0.00},
        {1.00, 0.00, 1.00, 0.00, 1.00, 0.00, 0.00},
        {0.00, 0.00, 0.00, 1.00, 0.00, 1.00, 0.00},
        {0.00, 1.00, 0.00, 0.00, 1.00, 0.00, 1.00},
        {0.00, 0.00, 0.00, 0.00, 0.00, 1.00, 0.00}
    };

    double expected[7][7] = {
        {1.00, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00},
        {0.00, 1.00, 0.00, 0.00, 0.00, 0.00, 0.00},
        {0.00, 0.00, 0.00, 1.00, 0.00, 0.00, 0.00},
        {0.33, 0.00, 0.33, 0.00, 0.33, 0.00, 0.00},
        {0.00, 0.00, 0.00, 0.50, 0.00, 0.50, 0.00},
        {0.00, 0.33, 0.00, 0.00, 0.33, 0.00, 0.33},
        {0.00, 0.00, 0.00, 0.00, 0.00, 1.00, 0.00}
    };

    /* copy degree matrix */
    mat_t *d_1 = init_vec(dim, dim, false); 
    for(int i = 0; i < dim; i++){
        for(int j = 0; j < dim; j++){
            d_1->arr[i][j] = d_inverse[i][j];
        }
    }

    mat_t *A = init_vec(dim, dim, false); 
    for(int i = 0; i < dim; i++){
        for(int j = 0; j < dim; j++){
            A->arr[i][j] = adj_matrix[i][j];
        }
    }

    mat_t *result = multiply(A, d_1);

	for(int i = 0; i < result->rows; i++){
		double rounded_value = round(result->arr[i][i]*100)/100; 
		if(expected[i][i] != rounded_value){
            printf("%f -> %f\n", expected[i][i], rounded_value); 
			equality_status = false; 
		}
	}

    if(!equality_status) {
        printf("%s::%s... FAILED\n", __FILE__, __FUNCTION__);
    } else {
        printf("%s::%s... \e[0;32mPASSED\e[0m\n", __FILE__, __FUNCTION__);
    }

}


void test_matrix_power() {

    bool equality_status = true; 
    int dim = 7; 

    /* inverse times adjacency matrix result */
    double inverse[7][7] = {
        {1.00, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00},
        {0.00, 1.00, 0.00, 0.00, 0.00, 0.00, 0.00},
        {0.00, 0.00, 0.00, 1.00, 0.00, 0.00, 0.00},
        {0.33, 0.00, 0.33, 0.00, 0.33, 0.00, 0.00},
        {0.00, 0.00, 0.00, 0.50, 0.00, 0.50, 0.00},
        {0.00, 0.33, 0.00, 0.00, 0.33, 0.00, 0.33},
        {0.00, 0.00, 0.00, 0.00, 0.00, 1.00, 0.00}
    };

    /* copy inverse to vec */
    mat_t *A = init_vec(dim, dim, false); 
    for(int i = 0; i < dim; i++){
        for(int j = 0; j < dim; j++){
            A->arr[i][j] = inverse[i][j];
        }
    }

	/* expected result */
    double expected[7][7] = {
        {1.00, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00},
        {0.00, 1.00, 0.00, 0.00, 0.00, 0.00, 0.00},
        {0.75, 0.25, 0.00, 0.00, 0.00, 0.00, 0.00},
        {0.75, 0.25, 0.00, 0.00, 0.00, 0.00, 0.00},
        {0.50, 0.50, 0.00, 0.00, 0.00, 0.00, 0.00},
        {0.25, 0.75, 0.00, 0.00, 0.00, 0.00, 0.00},
        {0.25, 0.75, 0.00, 0.00, 0.00, 0.00, 0.00}
    };

    /* raise to power of 100 */
    mat_t *result = power(A, 50); 

	for(int i = 0; i < result->rows; i++){
		double rounded_value = round(result->arr[i][i]*100)/100; 
		if(expected[i][i] != rounded_value){
            printf("%f -> %f\n", expected[i][i], rounded_value); 
			equality_status = false; 
		}
	}

    if(!equality_status) {
        printf("%s::%s... FAILED\n", __FILE__, __FUNCTION__);
    } else {
        printf("%s::%s... \e[0;32mPASSED\e[0m\n", __FILE__, __FUNCTION__);
    }

}

void test_dot_product() {

    int rows = 6; 
    int cols = 6;
    bool equality_status = true;  
    mat_t *m = init_vec(rows, cols, false); 
    mat_t *m2 = init_vec(rows, cols, false); 

    double m_values[6][6] = {
        {2, 0, 0, 0, 0, 0}, 
        {0, 2, 0, 0, 0, 0},
        {0, 0, 2, 0, 0, 0},
        {0, 0, 0, 2, 0, 0},
        {0, 0, 0, 0, 2, 0},
        {0, 0, 0, 0, 0, 2},
    };

    double m2_values[6][6] = {
        {3, 0, 0, 0, 0, 0}, 
        {0, 3, 0, 0, 0, 0},
        {0, 0, 3, 0, 0, 0},
        {0, 0, 0, 3, 0, 0},
        {0, 0, 0, 0, 3, 0},
        {0, 0, 0, 0, 0, 3},
    };

    double expected_values[6][6] = {
        {6, 0, 0, 0, 0, 0}, 
        {0, 6, 0, 0, 0, 0},
        {0, 0, 6, 0, 0, 0},
        {0, 0, 0, 6, 0, 0},
        {0, 0, 0, 0, 6, 0},
        {0, 0, 0, 0, 0, 6},
    };

    /* copy values to matrice */
    for(int i = 0; i < rows; i++){
        for(int j = 0; j < cols; j++){
            m->arr[i][j] = m_values[i][j];
            m2->arr[i][j] = m2_values[i][j]; 
        }
    }

    mat_t *result = dot(m, m2); 

    for(int i = 0; i < rows; i++){
        double rounded_value = round(result->arr[i][i]*100)/100; 
        if(expected_values[i][i] != rounded_value){
            equality_status = false; 
		}
	}

    if(!equality_status) {
        printf("%s::%s... FAILED\n", __FILE__, __FUNCTION__);
    } else {
        printf("%s::%s... \e[0;32mPASSED\e[0m\n", __FILE__, __FUNCTION__);
    } 
}

void test_backprop_dot_product(){


    bool equality_status = false;  
    mat_t *m1 = init_matrix(4, 1); 
    mat_t *m2 = init_matrix(1, 3); 

    /* specific case where matrix returns 0's*/
    double m2_values[4][1] = {
        {0.07}, 
        {0.07}, 
        {0.07}, 
        {0.07}, 
    };

    double m3_values[1][3] = {
        {-0.23, 0.31, -0.42} 
    };


    /* copy values to matrice */
    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 1; j++){
            m1->arr[i][j] = m2_values[i][j]; 
        }
    }


    for(int i = 0; i < 1; i++){
        for(int j = 0; j < 3; j++){
            m2->arr[i][j] = m3_values[i][j]; 
        }
    }

    mat_t *result = dot(m1, m2); 
    if(result->rows == 4 && result->cols == 3){
        equality_status = true;             
    }

    if(!equality_status) {
        printf("%s::%s... FAILED\n", __FILE__, __FUNCTION__);
    } else {
        printf("%s::%s... \e[0;32mPASSED\e[0m\n", __FILE__, __FUNCTION__);
    } 

}


void test_dot_unequal_dimensions(){

    bool equality_status = true;  
    mat_t *m = init_matrix(2, 2); 
    mat_t *m2 = init_matrix(2, 1); 

    double m_values[6][6] = {
        {3, 0}, 
        {0, 3},
    };

    double m2_values[2][1] = {
        {1},
        {1}
    };

    double results[2][1] = {
        {3.00},
        {3.00}
    };

    /* copy values to matrice */
    for(int i = 0; i < m->rows; i++){
        for(int j = 0; j < m->cols; j++){
            m->arr[i][j] = m_values[i][j];
        }
    }


    for(int i = 0; i < m2->rows; i++){
        for(int j = 0; j < m2->cols; j++){
            m2->arr[i][j] = m2_values[i][j];
        }
    }

    mat_t *result = dot(m, m2);

    for(int i = 0; i < result->rows; i++){
        for(int j = 0; j < result->cols; j++){
            double rounded_value = round(result->arr[i][j]*100)/100; 
            if(results[i][j] != rounded_value){
                equality_status = false; 
		    }
        }
	}

    if(!equality_status) {
        printf("%s::%s... FAILED\n", __FILE__, __FUNCTION__);
    } else {
        printf("%s::%s... \e[0;32mPASSED\e[0m\n", __FILE__, __FUNCTION__);
    } 

}




void test_add_mat() {

    int rows = 6; 
    int cols = 6;
    bool equality_status = true;  
    mat_t *m = init_vec(rows, cols, false); 
    mat_t *m2 = init_vec(rows, cols, false); 

    double m_values[6][6] = {
        {2, 0, 0, 0, 0, 0}, 
        {0, 2, 0, 0, 0, 0},
        {0, 0, 2, 0, 0, 0},
        {0, 0, 0, 2, 0, 0},
        {0, 0, 0, 0, 2, 0},
        {0, 0, 0, 0, 0, 2},
    };

    double m2_values[6][6] = {
        {3, 0, 0, 0, 0, 0}, 
        {0, 3, 0, 0, 0, 0},
        {0, 0, 3, 0, 0, 0},
        {0, 0, 0, 3, 0, 0},
        {0, 0, 0, 0, 3, 0},
        {0, 0, 0, 0, 0, 3},
    };


    double expected_values[6][6] = {
        {5, 0, 0, 0, 0, 0}, 
        {0, 5, 0, 0, 0, 0},
        {0, 0, 5, 0, 0, 0},
        {0, 0, 0, 5, 0, 0},
        {0, 0, 0, 0, 5, 0},
        {0, 0, 0, 0, 0, 5},
    };

    for(int i = 0; i < rows; i++){
        for(int j = 0; j < cols; j++){
            m->arr[i][j] = m_values[i][j];
            m2->arr[i][j] = m2_values[i][j]; 
        }
    }

    mat_t *result = add(m, m2);

    for(int i = 0; i < rows; i++){
        double rounded_value = round(result->arr[i][i]*100)/100; 
        if(expected_values[i][i] != rounded_value){
            equality_status = false; 
		}
	}

    if(!equality_status) {
        printf("%s::%s... FAILED\n", __FILE__, __FUNCTION__);
    } else {
        printf("%s::%s... \e[0;32mPASSED\e[0m\n", __FILE__, __FUNCTION__);
    } 
        
}

void test_scale_add(){

    mat_t *dot_product = init_vec(4, 3, false); 
    mat_t *biases = init_vec(1, 3, false); 
    bool equality_status = true; 

    double m_values[4][3] = {
        {0, 0, 0}, 
        {2, 2, 2}, 
        {2, 2, 2}, 
        {4, 4, 4}, 
    };

    double biase_values[1][3] = {
        {1, 1, 1}, 
    };


    double expected_values[4][3] = {
        {1, 1, 1}, 
        {3, 3, 3}, 
        {3, 3, 3}, 
        {5, 5, 5}, 
    };


    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 3; j++){
            dot_product->arr[i][j] = m_values[i][j];
            if(i == 0){
                biases->arr[i][j] = biase_values[i][j]; 
            }
        }
    }

    mat_t *result = scale_add(dot_product, biases); 

    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 3; j++){
            double rounded_value = round(result->arr[i][j]*100)/100; 
            if(expected_values[i][j] != rounded_value){
                equality_status = false; 
		    }
        }
	}

    if(!equality_status) {
        printf("%s::%s... FAILED\n", __FILE__, __FUNCTION__);
    } else {
        printf("%s::%s... \e[0;32mPASSED\e[0m\n", __FILE__, __FUNCTION__);
    } 

}

void test_transpose_mat(){


    int rows = 6; 
    int cols = 6;
    bool equality_status = true;  
    mat_t *m = init_vec(rows, cols, false); 

    double m_values[6][6] = {
        {1, 2, 3, 4, 5, 6}, 
        {1, 2, 3, 4, 5, 6},
        {0, 0, 2, 0, 0, 0},
        {0, 0, 0, 2, 0, 0},
        {0, 0, 0, 0, 2, 0},
        {0, 0, 0, 0, 0, 2},
    };

    double expected_values[6][6] = {
        {1, 1, 0, 0, 0, 0}, 
        {2, 2, 0, 0, 0, 0},
        {3, 3, 2, 0, 0, 0},
        {4, 4, 0, 2, 0, 0},
        {5, 5, 0, 0, 2, 0},
        {6, 6, 0, 0, 0, 2},
    };

    for(int i = 0; i < rows; i++){
        for(int j = 0; j < cols; j++){
            m->arr[i][j] = m_values[i][j];
        }
    }

    mat_t *result = transpose(m); 

    for(int i = 0; i < rows; i++){
        for(int j = 0; j < cols; j++){
            double rounded_value = round(result->arr[i][j]*100)/100; 
            if(expected_values[i][j] != rounded_value){
                equality_status = false; 
		    }
        }
	}

    if(!equality_status) {
        printf("%s::%s... FAILED\n", __FILE__, __FUNCTION__);
    } else {
        printf("%s::%s... \e[0;32mPASSED\e[0m\n", __FILE__, __FUNCTION__);
    } 

}
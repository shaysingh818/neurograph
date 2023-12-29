#include "includes/test_matrix.h"

void test_init_vec() {
	
	int equality_status = true; 
    int start = 100;

    mat_t *v = init_vec(start, start, true);
    assert(v->rows == start && v->cols == start);  

    /* init identity matrix */
    for(int i = 0; i < v->cols; i++){
        assert(v->arr[i][i] == 1.00); 
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
        assert(expected[i][i] == rounded_value); 
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
    mat_t *d_1 = init_matrix(dim, dim); 
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
        assert(expected[i][i] == rounded_value); 
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
    mat_t *A = init_matrix(dim, dim); 
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
        assert(expected[i][i] == rounded_value); 
	}

    if(!equality_status) {
        printf("%s::%s... FAILED\n", __FILE__, __FUNCTION__);
    } else {
        printf("%s::%s... \e[0;32mPASSED\e[0m\n", __FILE__, __FUNCTION__);
    }

}

void test_to_rows_cols() {

    bool equality_status = true; 
    int rows = 3, cols = 3; 
    mat_t *m = init_matrix(rows, cols); 

    double m_values[3][3] = {
        {1,2,3}, 
        {1,2,3},
        {1,2,3},
    };

    /* copy values to matrice */
    for(int i = 0; i < rows; i++){
        for(int j = 0; j < cols; j++){
            m->arr[i][j] = m_values[i][j];
        }
    }

    /* test to rows */
    mat_t **results = to_rows(m); 
    for(int i = 0; i < m->rows; i++){

        /* scan results for matrix */
        for(int j = 0; j < results[i]->rows; j++){
            for(int k = 0; k < results[i]->cols; k++){
                assert(results[i]->arr[j][k] == m_values[j][k]); 
            }
        }
    }

    /* add to cols method test here for next release */
    mat_t **col_results = to_cols(m); 
    for(int i = 0; i < m->cols; i++){

        /* scan results for matrix */
        for(int j = 0; j < col_results[i]->rows; j++){
            for(int k = 0; k < col_results[i]->cols; k++){
                if(col_results[i]->arr[j][k] != m_values[k][i]) {
                    equality_status = false; 
                }
                assert(col_results[i]->arr[j][k] == m_values[k][i]);
            }
        }
    }


    if(!equality_status) {
        printf("%s::%s... FAILED\n", __FILE__, __FUNCTION__);
    } else {
        printf("%s::%s... \e[0;32mPASSED\e[0m\n", __FILE__, __FUNCTION__);
    }
}


void test_batch_rows() {

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


    /* copy values to matrice */
    for(int i = 0; i < rows; i++){
        for(int j = 0; j < cols; j++){
            m->arr[i][j] = m_values[i][j];
        }
    }

    int limit = 3; 
    mat_t **batch = batch_rows(m, limit);

    for(int j = 0; j < limit; j++){
        for(int k = 0; k < m->cols; k++){
            bool condition = m->arr[j][k] == batch[j]->arr[0][k];
            assert(condition == true);  
        }
    }


    if(!equality_status) {
        printf("%s::%s... FAILED\n", __FILE__, __FUNCTION__);
    } else {
        printf("%s::%s... \e[0;32mPASSED\e[0m\n", __FILE__, __FUNCTION__);
    }

} 

void test_batch_even_matrix() {

    int rows = 6; 
    int cols = 6;

    double m_values[6][6] = {
        {2, 0, 0, 0, 0, 0}, 
        {0, 2, 0, 0, 0, 0},
        {0, 0, 2, 0, 0, 0},
        {0, 0, 0, 2, 0, 0},
        {0, 0, 0, 0, 2, 0},
        {0, 0, 0, 0, 0, 2}
    };

    double expected_batches[3][3][6] = {
        {{2, 0, 0, 0, 0, 0}, 
        {0, 2, 0, 0, 0, 0},
        {0, 0, 2, 0, 0, 0}},

        {{0, 2, 0, 0, 0, 0}, 
        {0, 0, 2, 0, 0, 0},
        {0, 0, 0, 2, 0, 0}},

        {{0, 0, 2, 0, 0, 0}, 
        {0, 0, 0, 2, 0, 0},
        {0, 0, 0, 0, 2, 0}},
    };

    int batch_size = 3;
    mat_t *mat = copy_arr_to_matrix(rows, cols, m_values); 
    mat_t **results = batch_matrix(mat, batch_size);   

    /* result count is input matrix rows minus the batch size*/
    for(int i = 0; i < (mat->rows - batch_size); i++){
        mat_t *expected_matrix = copy_arr_to_matrix(batch_size, 6, expected_batches[i]);
        mat_t *result = results[i]; 
        bool compare_mat = compare_matrix(expected_matrix, result);
        assert(result->rows == batch_size && result->cols == 6); 
        assert(compare_mat == true);  
    }

    printf("%s::%s... \e[0;32mPASSED\e[0m\n", __FILE__, __FUNCTION__);
}


void test_batch_odd_matrix() {

    int rows = 7; 
    int cols = 6;

    double m_values[7][6] = {
        {2, 0, 0, 0, 0, 0}, 
        {0, 2, 0, 0, 0, 0},
        {0, 0, 2, 0, 0, 0},
        {0, 0, 0, 2, 0, 0},
        {0, 0, 0, 0, 2, 0},
        {0, 0, 0, 0, 0, 2},
        {0, 0, 0, 0, 0, 2}
    };

    double expected_batches[5][2][6] = {
        {{2, 0, 0, 0, 0, 0}, 
        {0, 2, 0, 0, 0, 0}},

        {{0, 2, 0, 0, 0, 0}, 
        {0, 0, 2, 0, 0, 0}},

        {{0, 0, 2, 0, 0, 0}, 
        {0, 0, 0, 2, 0, 0}},

        {{0, 0, 0, 2, 0, 0}, 
        {0, 0, 0, 0, 2, 0}},

        {{0, 0, 0, 0, 2, 0}, 
        {0, 0, 0, 0, 0, 2}},
    };

    int batch_size = 2;
    mat_t *mat = copy_arr_to_matrix(rows, cols, m_values); 
    mat_t **results = batch_matrix(mat, batch_size); 

    for(int i = 0; i < (mat->rows - batch_size); i++){
        mat_t *expected_matrix = copy_arr_to_matrix(batch_size, 6, expected_batches[i]);
        mat_t *result = results[i];
        bool compare_mat = compare_matrix(expected_matrix, result);
        assert(result->rows == batch_size && result->cols == 6); 
        assert(compare_mat == true);  
    }

    printf("%s::%s... \e[0;32mPASSED\e[0m\n", __FILE__, __FUNCTION__);
} 


void test_uniform_distribution() {

    int dims = 3; 
    bool equality_status = true; 
    mat_t *m = init_matrix(dims, dims); 
    randomize(m, dims);

    for(int i = 0; i < dims; i++){
        for(int j = 0; j < dims; j++){
            assert(m->arr[i][j] != 0); 
        }
    }

    if(!equality_status) {
        printf("%s::%s... FAILED\n", __FILE__, __FUNCTION__);
    } else {
        printf("%s::%s... \e[0;32mPASSED\e[0m\n", __FILE__, __FUNCTION__);
    }
}


void test_load_and_save_matrix() {

    char *filepath = "../../../examples/data/saved_matrix"; 
    bool equality_status = true; 
    int dims = 3; 
    mat_t *m = init_matrix(dims, dims); 

    double m_values[3][3] = {
        {1.00,2.00,3.00}, 
        {1.00,2.00,3.00},
        {1.00,2.00,3.00},
    };

    /* copy values to matrice */
    for(int i = 0; i < dims; i++){
        for(int j = 0; j < dims; j++){
            m->arr[i][j] = m_values[i][j];
        }
    }

    /* save matrix instance in file */
    save_matrix(m, filepath);


    /* try and load matrix from file */
    mat_t *loaded_matrix = load_matrix(filepath); 

    for(int i = 0; i < dims; i++){
        for(int j = 0; j < dims; j++){
            m->arr[i][j] = m_values[i][j];
            assert(loaded_matrix->arr[i][j] == m->arr[i][j]); 
        }
    }

    /* remove file */
    system("rm ../../../examples/data/saved_matrix"); 
    printf("%s::%s... \e[0;32mPASSED\e[0m\n", __FILE__, __FUNCTION__);

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
        assert(expected_values[i][i] == rounded_value); 
	}

    if(!equality_status) {
        printf("%s::%s... FAILED\n", __FILE__, __FUNCTION__);
    } else {
        printf("%s::%s... \e[0;32mPASSED\e[0m\n", __FILE__, __FUNCTION__);
    } 
}

void test_backprop_dot_product(){


    bool equality_status = true;  
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
    assert(result->rows == 4 && result->cols == 3); 

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
            assert(results[i][j] == rounded_value); 
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
        assert(expected_values[i][i] == rounded_value); 
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
            assert(expected_values[i][j] == rounded_value); 
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
            assert(expected_values[i][j] == rounded_value); 

        }
	}

    if(!equality_status) {
        printf("%s::%s... FAILED\n", __FILE__, __FUNCTION__);
    } else {
        printf("%s::%s... \e[0;32mPASSED\e[0m\n", __FILE__, __FUNCTION__);
    } 

}


void test_scale_multiply() {

    int dims = 3; 
    bool equality_status = true; 
    mat_t *m = init_matrix(dims, dims); 

    double m_values[3][3] = {
        {2, 2, 2}, 
        {2, 2, 2}, 
        {4, 4, 4}, 
    };


    double expected_values[3][3] = {
        {4.00, 4.00, 4.00}, 
        {4.00, 4.00, 4.00}, 
        {8.00, 8.00, 8.00}
    };


    for(int i = 0; i < dims; i++){
        for(int j = 0; j < dims; j++){
            m->arr[i][j] = m_values[i][j];
        }
    }

    /* test scale multiply */
    mat_t *result = scale(m, 2.00);

    /* match result */
    for(int i = 0; i < dims; i++){
        for(int j = 0; j < dims; j++){
            double rounded_value = round(result->arr[i][j]*100)/100; 
            assert(expected_values[i][j] == rounded_value); 

        }
	}


    if(!equality_status) {
        printf("%s::%s... FAILED\n", __FILE__, __FUNCTION__);
    } else {
        printf("%s::%s... \e[0;32mPASSED\e[0m\n", __FILE__, __FUNCTION__);
    } 

}


void test_elementwise_multiply() {

    int dims = 3; 
    bool equality_status = true; 
    mat_t *m1 = init_matrix(dims, dims); 
    mat_t *m2 = init_matrix(dims, dims); 

    double m1_values[3][3] = {
        {2, 2, 2}, 
        {2, 2, 2}, 
        {4, 4, 4}, 
    };


    double m2_values[3][3] = {
        {4, 4, 4}, 
        {4, 4, 4}, 
        {5, 5, 5}, 
    };
    
    double expected_values[3][3] = {
        {8.00, 8.00, 8.00}, 
        {8.00, 8.00, 8.00}, 
        {20.00, 20.00, 20.00}
    };


    /* copy values to matrix */
    for(int i = 0; i < dims; i++){
        for(int j = 0; j < dims; j++){
            m1->arr[i][j] = m1_values[i][j];
            m2->arr[i][j] = m2_values[i][j]; 
        }
    }


    /* test elementwise multiply */
    mat_t *result = elementwise_multiply(m1, m2); 

    /* match result */
    for(int i = 0; i < dims; i++){
        for(int j = 0; j < dims; j++){
            double rounded_value = round(result->arr[i][j]*100)/100; 
            assert(expected_values[i][j] == rounded_value); 

        }
	}

    if(!equality_status) {
        printf("%s::%s... FAILED\n", __FILE__, __FUNCTION__);
    } else {
        printf("%s::%s... \e[0;32mPASSED\e[0m\n", __FILE__, __FUNCTION__);
    } 

}



void test_add_matrix() {

    int dims = 3; 
    bool equality_status = true; 
    mat_t *m1 = init_matrix(dims, dims); 
    mat_t *m2 = init_matrix(dims, dims); 

    double m1_values[3][3] = {
        {2, 2, 2}, 
        {2, 2, 2}, 
        {4, 4, 4}, 
    };


    double m2_values[3][3] = {
        {4, 4, 4}, 
        {4, 4, 4}, 
        {5, 5, 5}, 
    };


    double expected_values[3][3] = {
        {6.00, 6.00, 6.00}, 
        {6.00, 6.00, 6.00}, 
        {9.00, 9.00, 9.00}
    };

    /* copy values to matrix */
    for(int i = 0; i < dims; i++){
        for(int j = 0; j < dims; j++){
            m1->arr[i][j] = m1_values[i][j];
            m2->arr[i][j] = m2_values[i][j]; 
        }
    }

    /* test add result */
    mat_t *result = add(m1, m2);

    /* match result */
    for(int i = 0; i < dims; i++){
        for(int j = 0; j < dims; j++){
            double rounded_value = round(result->arr[i][j]*100)/100; 
            assert(expected_values[i][j] == rounded_value); 
        }
	}

    if(!equality_status) {
        printf("%s::%s... FAILED\n", __FILE__, __FUNCTION__);
    } else {
        printf("%s::%s... \e[0;32mPASSED\e[0m\n", __FILE__, __FUNCTION__);
    } 

}


void test_matrix_difference() {

    int dims = 3; 
    bool equality_status = true; 
    mat_t *m1 = init_matrix(dims, dims); 
    mat_t *m2 = init_matrix(dims, dims); 

    double m1_values[3][3] = {
        {2, 2, 2}, 
        {2, 2, 2}, 
        {4, 4, 4}, 
    };


    double m2_values[3][3] = {
        {4, 4, 4}, 
        {4, 4, 4}, 
        {5, 5, 5}, 
    };


    double expected_values[3][3] = {
        {2.00, 2.00, 2.00}, 
        {2.00, 2.00, 2.00}, 
        {1.00, 1.00, 1.00}
    };

    /* copy values to matrix */
    for(int i = 0; i < dims; i++){
        for(int j = 0; j < dims; j++){
            m1->arr[i][j] = m1_values[i][j];
            m2->arr[i][j] = m2_values[i][j]; 
        }
    }


    mat_t *result = difference(m2, m1); 

    /* match result */
    for(int i = 0; i < dims; i++){
        for(int j = 0; j < dims; j++){
            double rounded_value = round(result->arr[i][j]*100)/100; 
            assert(expected_values[i][j] == rounded_value); 

        }
	}

    if(!equality_status) {
        printf("%s::%s... FAILED\n", __FILE__, __FUNCTION__);
    } else {
        printf("%s::%s... \e[0;32mPASSED\e[0m\n", __FILE__, __FUNCTION__);
    } 
}



void test_im2col() {


    double a_values[3][4] = {
        {1, 2, 3, 1}, 
        {4, 5, 6, 1}, 
        {7, 8, 9, 1}, 
    };

    double d_values[2][2] = {
        {1, 1},
        {1, 1}
    };

    mat_t *A = copy_arr_to_matrix(3, 4, a_values); 
    mat_t *D = copy_arr_to_matrix(2, 2, d_values); 
    mat_t *B = im2col(A, D);

    assert(A->rows == 3 && A->cols == 4);
    assert(D->rows == 2 && D->cols == 2);  

    mat_t *b_t = transpose(B); 
    assert(B->rows == 4 && B->cols == 6); 
    assert(b_t->rows == 6 && b_t->cols == 4); 

    mat_t *D_vec = vectorize(D);
    assert(D_vec->rows == D->rows*D->cols);
    assert(D_vec->cols == 1);  

    mat_t *result = multiply(b_t, D_vec);
    assert(result->rows == 6 && result->cols == 1); 

    printf("%s::%s... \e[0;32mPASSED\e[0m\n", __FILE__, __FUNCTION__);
} 
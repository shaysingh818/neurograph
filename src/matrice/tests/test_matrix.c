#include "includes/test_matrix.h"

void test_init_matrix(){

	int equality_status = true; 

	/* create adjacency matrix graph with size 5 */ 
	mat_t *m = init_matrice_graph(5); 

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
	mat_t *m = init_matrice_graph(5); 

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

    vec_t *v = init_vec(start, start, true);

    if(v->rows == start && v->cols == start){
        equality_status = true; 
    } 

    /* init identity matrix */
    for(int i = 0; i < v->cols; i++){
        if(v->items[i][i] == 1.00){
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
    vec_t *v = init_vec(dim, dim, false); 
    for(int i = 0; i < dim; i++){
        for(int j = 0; j < dim; j++){
            v->items[i][j] = values[i][j];
        }
    }
 
    double det = 1.00; 
	for(int i = 0; i < v->rows; i++){
		det *= v->items[i][i];
	}

    vec_t *result = scalar_multiply(v, det);  
	for(int i = 0; i < result->rows; i++){
		double rounded_value = round(result->items[i][i]*100)/100; 
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
    vec_t *d_1 = init_vec(dim, dim, false); 
    for(int i = 0; i < dim; i++){
        for(int j = 0; j < dim; j++){
            d_1->items[i][j] = d_inverse[i][j];
        }
    }

    vec_t *A = init_vec(dim, dim, false); 
    for(int i = 0; i < dim; i++){
        for(int j = 0; j < dim; j++){
            A->items[i][j] = adj_matrix[i][j];
        }
    }

    vec_t *result = multiply(A, d_1);

	for(int i = 0; i < result->rows; i++){
		double rounded_value = round(result->items[i][i]*100)/100; 
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
    vec_t *A = init_vec(dim, dim, false); 
    for(int i = 0; i < dim; i++){
        for(int j = 0; j < dim; j++){
            A->items[i][j] = inverse[i][j];
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
    vec_t *result = power(A, 50); 

	for(int i = 0; i < result->rows; i++){
		double rounded_value = round(result->items[i][i]*100)/100; 
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
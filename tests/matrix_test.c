#include "includes/matrix_test.h"

void test_init_matrix(){

	/* create adjacency matrix graph with size 5 */ 
	mat_t *m = init_mat(5, 5); 
	entry(m, 0, 1); 
	entry(m, 0, 2); 
	entry(m, 1, 2); 
	entry(m, 2, 0); 
	entry(m, 2, 3);

	/* expected output */ 
	int equality_status = TRUE; 
	int check_matrix[5][5] = {
		{0, 1, 1, 0, 0}, 
		{1, 0, 1, 0, 0},
		{1, 1, 0, 1, 0},
		{0, 0, 1, 0, 0},
		{0, 0, 0, 0, 0}
	}; 

	/* test if matrice values are correct */ 
	for(int i = 0; i < m->vertices; i++) {
        for(int j = 0; j < m->edges; j++){
			if(m->arr[i][j] != check_matrix[i][j]) {
				equality_status = FALSE; 
			}
        }
    }

	/* validate results */
    if(!equality_status) {
        printf("%s::%s... FAILED\n", __FILE__, __FUNCTION__);
    }
    printf("%s::%s... \e[0;32mPASSED\e[0m\n", __FILE__, __FUNCTION__);



}

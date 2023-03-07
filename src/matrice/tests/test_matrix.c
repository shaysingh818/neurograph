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

    print_matrix_labels(m); 

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

    print_matrix_labels(m); 

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


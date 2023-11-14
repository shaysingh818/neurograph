#include "includes/test_adj_mat.h" 


void test_init_adj_mat() {

    int vertices = 8, edges = 9; 
    adj_mat_t *mat = init_adj_mat(vertices, edges, false);

    assert(mat->v == vertices);
    assert(mat->e == edges);  
    assert(mat->weights->rows == vertices); 
    assert(mat->weights->cols == vertices);
    assert(mat->directed == false); 
    assert(mat->err == false);


    for(int i = 0; i < mat->v; i++){
        assert(mat->used[i] == 0); 
        assert(mat->visited[i] == 0); 
    }

	printf("%s::%s... \e[0;32mPASSED\e[0m\n", __FILE__, __FUNCTION__);
}


void test_add_node_mat_undirected() {


	char *relationship_list[5][5] = {
		{"B", "C", "D"}, 
		{"A", "C"},
		{"A", "B", "E"},
		{"A"},
		{"C"}
	}; 

    int vertices = 8, edges = 9; 
    adj_mat_t *mat = init_adj_mat(vertices, edges, false);
	add_node_mat(mat, 0, "A", 1, "B", 1);
	add_node_mat(mat, 0, "A", 2, "C", 1); 
	add_node_mat(mat, 0, "A", 3, "D", 1); 
	add_node_mat(mat, 1, "B", 2, "C", 0);
	add_node_mat(mat, 4, "E", 2, "C", 1);

    assert(mat->weights->rows == 8); 
    assert(mat->weights->cols == 8); 
    assert(mat->directed == false);

    /* get neighbors for each vertice */
    for(int i = 0; i < mat->v; i++){
        int node_index = 0;  
        for(int j = 0; j < mat->v; j++){
            node_t *neighbor = mat->items[i*mat->v+j];
            if(neighbor->label != NULL){
                int compare = strcmp(neighbor->label, relationship_list[i][node_index]) == 0;
                assert(compare == true);  
                node_index += 1; 
            } 
        }
    }

	printf("%s::%s... \e[0;32mPASSED\e[0m\n", __FILE__, __FUNCTION__);
}


void test_add_node_mat_directed() {

    char *relationship_list[8][8] = {
        {"B", "C", "D"}, 
        {"C"},
        {},
        {},
        {"C"},
        {},
        {},
        {}
    }; 

    int vertices = 8, edges = 9; 
    adj_mat_t *mat = init_adj_mat(vertices, edges, true);
    add_node_mat(mat, 0, "A", 1, "B", 1);
    add_node_mat(mat, 0, "A", 2, "C", 1); 
    add_node_mat(mat, 0, "A", 3, "D", 1); 
    add_node_mat(mat, 1, "B", 2, "C", 0);
    add_node_mat(mat, 4, "E", 2, "C", 1);

    assert(mat->weights->rows == 8); 
    assert(mat->weights->cols == 8); 
    assert(mat->directed == true);

    /* get neighbors for each vertice */
    for(int i = 0; i < mat->v; i++){
        int node_index = 0;  
        for(int j = 0; j < mat->v; j++){
            node_t *neighbor = mat->items[i*mat->v+j];
            if(neighbor->label != NULL){
                int compare = strcmp(neighbor->label, relationship_list[i][node_index]) == 0;
                assert(compare == true);  
                node_index += 1; 
            } 
        }
    }

    printf("%s::%s... \e[0;32mPASSED\e[0m\n", __FILE__, __FUNCTION__);

}


void test_search_by_id_mat() {

    /* expected labels */
    char *labels[5] = {"A", "B", "C", "D", "E"}; 
    int vertices = 8, edges = 9; 
    adj_mat_t *mat = init_adj_mat(vertices, edges, false);
    add_node_mat(mat, 0, "A", 1, "B", 1);
    add_node_mat(mat, 0, "A", 2, "C", 1); 
    add_node_mat(mat, 0, "A", 3, "D", 1); 
    add_node_mat(mat, 1, "B", 2, "C", 0);
    add_node_mat(mat, 4, "E", 2, "C", 1);

    assert(mat->weights->rows == 8); 
    assert(mat->weights->cols == 8); 
    assert(mat->directed == false);

    /* search the node ids incremental */
    for(int i = 0; i < 5; i++){
        node_t *search = search_node_by_id_mat(mat, i); 
        int compare = strcmp(search->label, labels[i]) == 0; 
        assert(compare == true); 
    }

    printf("%s::%s... \e[0;32mPASSED\e[0m\n", __FILE__, __FUNCTION__);
}


void test_transpose_items_mat() {

	/* expected neighors output */
	char *relationship_list[8][8] = {
		{"D"}, 
		{"A"},
		{"B"},
		{"C"},
		{"C", "G"},
		{"E"}, 
		{"F"}, 
		{"G", "H"}, 
	};

	/* create adjacency list */ 
    int vertices = 8; 
	adj_mat_t *m = init_adj_mat(vertices, vertices, true);
	adj_mat_t *result_list = init_adj_mat(vertices, vertices, true); 

	/* first community */ 
	add_node_mat(m, 0, "A", 1, "B", 0);
	add_node_mat(m, 1, "B", 2, "C", 0);
	add_node_mat(m, 2, "C", 3, "D", 0);
	add_node_mat(m, 3, "D", 0, "A", 0);

	/* bridge */ 
	add_node_mat(m, 2, "C", 4, "E", 0);

	/* second community */ 
	add_node_mat(m, 4, "E", 5, "F", 0);
	add_node_mat(m, 5, "F", 6, "G", 0);
	add_node_mat(m, 6, "G", 4, "E", 0);
	add_node_mat(m, 6, "G", 7, "H", 0);
	add_node_mat(m, 7, "H", 7, "H", 0);

	/* call the tranpose method */ 
	adj_mat_t *result = transpose_items_mat(m, result_list);

    /* get neighbors for each vertice */
    for(int i = 0; i < result->v; i++){
        int node_index = 0;  
        for(int j = 0; j < result->v; j++){
            node_t *neighbor = result->items[i*result->v+j];
            if(neighbor->label != NULL){
                int compare = strcmp(neighbor->label, relationship_list[i][node_index]) == 0;
                assert(compare == true);  
                node_index += 1; 
            } 
        }
    }

    printf("%s::%s... \e[0;32mPASSED\e[0m\n", __FILE__, __FUNCTION__);

} 
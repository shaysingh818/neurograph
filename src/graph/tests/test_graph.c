#include "includes/test_graph.h" 


void test_frame_to_unweighted_graph() {

    bool equality_status = true; 
	int indices[2] = {1, 3}; 

    /* expected graph results */
	char *relationship_list[12][5] = {
		{"B", "C", "D"}, 
		{"A", "C"},
		{"A", "B", "E"},
		{"A"},
		{"C"},
		{},
		{},
        {},
        {},
        {},
        {},
		{}
	}; 

    frame_t *frame = dataframe("../../examples/data/test.csv", 1024, 6, NULL);
	assert(frame->status);

    /* get cols here */
    array_t *selected_cols = init_array(); 
    insert_char(selected_cols, "src_label"); 
    insert_char(selected_cols, "dest_label");

    /* convert frame to un weighted graph */
    graph_t *result = frame_to_unweighted_graph(
       frame, selected_cols, false
    ); 
	assert(!result->list->err);

	/* check graph against relationships */ 
	for(int i = 0; i < result->vertices; i++) {
	    node_t *head = result->list->items[i]->head; 
	    int node_index = 0; 
	    while(head) {
			int condition = strcmp(head->node_type->node->label, relationship_list[i][node_index]);
			assert(condition == 0);
	        head = head->next;
	        node_index += 1; 
	    }
	} 

 	/* validate results */
    printf("%s::%s... \e[0;32mPASSED\e[0m\n", __FILE__, __FUNCTION__);
} 


void test_frame_to_weighted_graph() {

    bool equality_status = true; 
	int indices[3] = {1,3,4}; 

    /* expected graph results */
	int weight_list[6][5] = {
		{1,1,1}, 
		{1,2},
		{1,2, 3},
		{1},
		{3},
		{}
	}; 

    frame_t *frame = dataframe("../../examples/data/test.csv", 1024, 6, NULL);
	assert(frame->status);

    /* get cols here */
    array_t *selected_cols = init_array(); 
    insert_char(selected_cols, "src_label"); 
    insert_char(selected_cols, "dest_label");
    insert_char(selected_cols, "weight");

    /* convert frame to un weighted graph */
    graph_t *result = frame_to_weighted_graph(
       frame, selected_cols, false
    );
	assert(!result->list->err); 


	/* check graph against relationships */ 
	for(int i = 0; i < result->list->v; i++) {
	    node_t *head = result->list->items[i]->head; 
	    int node_index = 0; 
	    while(head) {
			assert(head->node_type->node->weight == weight_list[i][node_index]); 
	        head = head->next;
	        node_index += 1; 
	    }
	}

 	/* validate results */
    if(!equality_status) {
        printf("%s::%s... FAILED\n", __FILE__, __FUNCTION__);
    }
    printf("%s::%s... \e[0;32mPASSED\e[0m\n", __FILE__, __FUNCTION__);

}


void test_unused_slots() {

    bool equality_status = true; 
	int indices[3] = {1,3,4}; 

    frame_t *frame = dataframe("../../examples/data/test.csv", 1024, 6, NULL);
	assert(frame->status);

    /* get cols here */
    array_t *selected_cols = init_array(); 
    insert_char(selected_cols, "src_label"); 
    insert_char(selected_cols, "dest_label");
    insert_char(selected_cols, "weight");

    /* convert frame to weighted graph */
    graph_t *result = frame_to_weighted_graph(
       frame, selected_cols, false
    );
	assert(result->list->v == 5);


    printf("%s::%s... \e[0;32mPASSED\e[0m\n", __FILE__, __FUNCTION__);
}


void test_get_max_vertex_count() {

	char *path = "../../examples/gml/unit_tests/standard.gmul";
	int max_count = get_max_vertex_count(path, 1024); 
	assert(max_count == 7); 

	char *path2 = "../../examples/gml/unit_tests/standard2.gmul"; 
	int max_count_2 = get_max_vertex_count(path2, 1024);
	assert(max_count_2 == 6); 

    printf("%s::%s... \e[0;32mPASSED\e[0m\n", __FILE__, __FUNCTION__);
} 


void test_get_nodes_from_file() {

	bool equality_status = true; 

	char *expected_labels[7] = {"a", "b", "c", "d", "e", "f", "g"};
	int expected_ids[7] = {0,1,2,3,4,5,6};  

	/* get unique nodes for graph */
	char *path = "../../examples/gml/unit_tests/test.gmul";
	set_t *node_set = get_graph_nodes_from_file(path, 1024);
	queue_t *q = init_queue(node_set->count); 
	get_items_sorted(node_set->root, q);
	assert(q->rear_index == 6);  

	for(int i = q->front_index; i <= q->rear_index; i++){
		char *label = q->items[i]->node_type->node->label;
		int id = get_item_sorted(node_set, label); 
		int compare = strcmp(label, expected_labels[i]) == 0; 
		assert(id == expected_ids[i]); 
		assert(compare == true); 
	}

    printf("%s::%s... \e[0;32mPASSED\e[0m\n", __FILE__, __FUNCTION__);
} 

void test_get_nodes(){

	/* create adjacency list */
    int vertices = 7; 
	graph_t *g = init_graph(vertices, vertices, false);
    add_node(g->list, 0, "A", 1, "B", 5);
    add_node(g->list, 0, "A", 2, "C", 6);
    add_node(g->list, 1, "B", 2, "C", 15);
    add_node(g->list, 1, "B", 3, "D", 7);
    add_node(g->list, 1, "B", 4, "E", 8);
    add_node(g->list, 2, "C", 3, "D", 2);
    add_node(g->list, 2, "C", 5, "F", 4);
	add_node(g->list, 3, "D", 4, "E", 2);
	add_node(g->list, 3, "D", 5, "F", 9);
	add_node(g->list, 3, "D", 6, "G", 10);
	add_node(g->list, 4, "E", 6, "G", 3);

	//print_graph(g->list); 
	ordered_set_t *set = get_graph_nodes(g);
	assert(set->used == 7);

	int expected_ids[7] = {1,2,0,3,4,5,6}; 
	int expected_insert_counts[7] = {6,4,3,5,2,1,1};
	char *expected_labels[7] = {"B", "C", "A", "D", "E", "F", "G"}; 

	for(int i = 0; i < set->used; i++){
		int compare = strcmp(set->items[i]->node_type->node->label, expected_labels[i]) == 0;
		int insert_count = get_insert_count(set, set->items[i]);

		assert(set->items[i]->id == expected_ids[i]);
		assert(compare == true);  
		assert(insert_count == expected_insert_counts[i]); 
	}  

}

void test_serialize_adj_list_sorted_labels(){


    graph_t *g = serialize_graph_list_sorted_label("../../examples/gml/unit_tests/test.gmul", 1024);

	// /* expected relationships from adjacency list */ 
	char *relationship_list[7][10] = {
		{"c", "b", "d", "e", "f", "b"}, 
		{"a", "a", "d", "c", "f", "g"},
		{"a", "b"},
		{"a", "b"},
        {"a"},
        {"a", "b"},
        {"b"}
	};



	/* iterate through list and match relationships */ 
	for(int i = 0; i < g->list->v; i++) {
		node_t *head = g->list->items[i]->head; 
		int node_index = 0; 
		while(head) {
			int condition = strcmp(head->node_type->node->label, relationship_list[i][node_index]);
			assert(condition == 0); 
			head = head->next;
		   	node_index += 1; 
		}
	}

    printf("%s::%s... \e[0;32mPASSED\e[0m\n", __FILE__, __FUNCTION__);
}


void test_serialize_adj_list() {


	char *relationship_list[7][10] = {
		{"D"}, 
		{"F"},
		{"D"},
		{"A", "C", "E"},
        {"D", "F"},
        {"E", "G", "B"},
        {"F"}
	};

	int expected_ids[7][10] = {
		{3}, 
		{5},
		{3},
		{0, 2, 4},
        {3, 5},
        {4, 6, 1},
        {5}
	};


	char *path = "../../examples/gml/unit_tests/standard2.gmul";
	graph_t *g = serialize_graph_list(path, 1024, false);
	assert(g->vertices == 7); 

	for(int i = 0; i < g->vertices; i++) {
		node_t *head = g->list->items[i]->head; 
		int node_index = 0;
		while(head) {
			int condition = strcmp(head->node_type->node->label, relationship_list[i][node_index]) == 0;
			int id_condition = head->id == expected_ids[i][node_index]; 
			assert(condition == true); 			
			assert(id_condition); 
			head = head->next;
		   	node_index += 1; 
		}
	}

    printf("%s::%s... \e[0;32mPASSED\e[0m\n", __FILE__, __FUNCTION__);
} 


void test_deserialize_adj_list() {

	int indices[2] = {1, 5}; 
	char *input_path = "../../examples/data/movies.csv";
	char *output_path = "../../examples/data/output/sample.gmul";
    frame_t *frame = dataframe(input_path, 1024, 100, NULL);
	assert(frame->status);

    /* get cols here */
    array_t *selected_cols = init_array(); 
    insert_char(selected_cols, "movie_name"); 
    insert_char(selected_cols, "genre");

    /* convert frame to un weighted graph */
    graph_t *result = frame_to_unweighted_graph(
       frame, selected_cols, false
    );

	/* validate that resize worked */
	assert(result->list->v == 198); 
	remove_unused_slots(result);
	assert(result->list->v == 154);  

	/* call deserialize method here */
	deserialize_graph_list(result, output_path);

	/* check that file path exists */
	assert(access(output_path, F_OK) == 0); 

	/* validate we can reserialize the graph*/ 
	graph_t *g = serialize_graph_list(output_path, 2048, true);
	assert(g->list->v == 154);

    printf("%s::%s... \e[0;32mPASSED\e[0m\n", __FILE__, __FUNCTION__);
} 


void test_to_list() {

	/* vertices and equality status */ 
	int vertices = 5; 
	int equality_status = TRUE;

	/* test first example of weighted matrix */ 
	adj_list_t *g = init_adj_list(vertices, vertices, true);
	adj_mat_t *m = init_adj_mat(vertices, vertices, true);


	/* build matrix */ 
	add_node_mat(m, 0, "A", 1, "B", 0);  
	add_node_mat(m, 0, "A", 2, "C", 0);  
	add_node_mat(m, 1, "B", 2, "C", 0);  
	add_node_mat(m, 2, "C", 0, "A", 0);  
	add_node_mat(m, 2, "C", 3, "D", 0);  

	/* test directed matrix conversion */ 
	adj_list_t *output = to_list(g, m, false);
	
	/* expected relationships from adjacency list */ 
	char *relationship_list[5][5] = {
		{"B", "C"}, 
		{"C"},
		{"A", "D"},
		{},
		{}
	};

	/* iterate through list and match relationships */ 
	for(int i = 0; i < g->v; i++) {
		node_t *head = g->items[i]->head; 
		int node_index = 0; 
		while(head) {
			int condition = strcmp(head->node_type->node->label, relationship_list[i][node_index]); 
			assert(condition == 0); 
			head = head->next;
		   	node_index += 1; 
		}
	}

	/* validate results */ 
	if(!equality_status) {
		printf("%s::%s... FAILED\n", __FILE__, __FUNCTION__); 
	} else {
		printf("%s::%s... \e[0;32mPASSED\e[0m\n", __FILE__, __FUNCTION__);
	}
}


void test_to_weighted_list() {

	/* vertices and equality status */ 
	int vertices = 5; 
	int equality_status = TRUE;

	/* test first example of weighted matrix */ 
	adj_list_t *g = init_adj_list(vertices, vertices, false);
	adj_mat_t *m = init_adj_mat(vertices, vertices, false);

	/* build matrix */ 
	add_node_mat(m, 0, "A", 1, "B", 0);  
	add_node_mat(m, 0, "A", 2, "C", 0);  
	add_node_mat(m, 1, "B", 2, "C", 0);  
	add_node_mat(m, 2, "C", 0, "A", 0);  
	add_node_mat(m, 2, "C", 3, "D", 0);  

	/* expected relationships from adjacency list */ 
	int relationship_list[5][6] = {
		{1, 4, 1, 4}, 
		{1,1,3,3},
		{4,3,4,3, 5,5},
		{5,5}
	};

	/* test directed matrix conversion */ 
	adj_list_t *output = to_list(g, m, false);

	/* iterate through list and match relationships */ 
	for(int i = 0; i < g->v; i++) {
		node_t *head = g->items[i]->head; 
		int node_index = 0; 
		while(head) {
			if(head->node_type->node->weight != relationship_list[i][node_index]) {
				equality_status = FALSE;
			}
			head = head->next;
		   	node_index += 1; 
		}	
	}

	/* validate results */ 
	printf("%s::%s... \e[0;32mPASSED\e[0m\n", __FILE__, __FUNCTION__);
}


void test_to_directed_list() {

	/* vertices and equality status */ 
	int vertices = 8; 
	int equality_status = TRUE;

	/* test first example of weighted matrix */ 
	adj_list_t *g = init_adj_list(vertices, vertices, true);
	adj_mat_t *m = init_adj_mat(vertices, vertices, true);

	/* build matrix */ 
	add_node_mat(m, 0, "A", 1, "B", 0);  
	add_node_mat(m, 0, "A", 2, "C", 0);  
	add_node_mat(m, 1, "B", 2, "C", 0);  
	add_node_mat(m, 2, "C", 0, "A", 0);  
	add_node_mat(m, 2, "C", 3, "D", 0);  

	/* expected relationships from adjacency list */ 
	char *relationship_list[5][6] = {
		{"B", "C"}, 
		{"C"},
		{"A","D"}
	};

	/* test directed matrix conversion */ 
	adj_list_t *output = to_list(g, m, true);

	/* iterate through list and match relationships */ 
	for(int i = 0; i < g->v; i++) {
		node_t *head = g->items[i]->head; 
		int node_index = 0; 
		while(head) {
			int condition = strcmp(head->node_type->node->label, relationship_list[i][node_index]);
			assert(condition == 0); 
			head = head->next;
		   	node_index += 1; 
		}	
	}

	/* validate results */ 
	printf("%s::%s... \e[0;32mPASSED\e[0m\n", __FILE__, __FUNCTION__);
}


void test_to_directed_weighted_list() {

	/* vertices and equality status */ 
	int vertices = 8; 
	int equality_status = TRUE;

	/* test first example of weighted matrix */ 
	adj_list_t *g = init_adj_list(vertices, vertices, true);
	adj_mat_t *m = init_adj_mat(vertices, vertices, true);

	/* build matrix */ 
	add_node_mat(m, 0, "A", 1, "B", 0);  
	add_node_mat(m, 0, "A", 2, "C", 0);  
	add_node_mat(m, 1, "B", 2, "C", 0);  
	add_node_mat(m, 2, "C", 0, "A", 0);  
	add_node_mat(m, 2, "C", 3, "D", 0);  

	/* expected relationships from adjacency list */ 
	char *relationship_list[5][5] = {
		{"B", "C"}, 
		{"C"},
		{"A","D"}
	};

	/* test directed matrix conversion */ 
	adj_list_t *output = to_list(g, m, true);

	/* iterate through list and match relationships */ 
	for(int i = 0; i < g->v; i++) {
		node_t *head = g->items[i]->head; 
		int node_index = 0; 
		while(head) {
			int condition = strcmp(head->node_type->node->label, relationship_list[i][node_index]); 
			assert(condition == 0);
			head = head->next;
		   	node_index += 1; 
		}	
	}

	/* validate results */ 
	printf("%s::%s... \e[0;32mPASSED\e[0m\n", __FILE__, __FUNCTION__);
}


void test_to_matrix() {

	/* test transpose of adjacency list */
    int vertices = 8; 
	int equality_status = TRUE;

	/* expected result after directed matrix conversion */
	int expected_output[8][8] = {
		{-1,1,-1,3,-1,-1,-1,-1},
		{0,-1,2,-1,-1,-1,-1,-1},
		{-1,1,-1,3,4,-1,-1,-1},
		{0,-1,2,-1,-1,-1,-1,-1},
		{-1,-1,2,-1,-1,5,6,-1},
		{-1,-1,-1,-1,4,-1,6,-1},
		{-1,-1,-1,-1,4,5,-1,7},
		{-1,-1,-1,-1,-1,-1,6,7}
	};	

	/* create adjacency list */ 
	adj_list_t *g = init_adj_list(vertices, vertices, false);
	adj_mat_t *result = init_adj_mat(vertices, vertices, false); 

	/* first community */ 
	add_node(g, 0, "A", 1, "B", 0);
	add_node(g, 1, "B", 2, "C", 0);
	add_node(g, 2, "C", 3, "D", 0);
	add_node(g, 3, "D", 0, "A", 0);

	/* bridge */ 
	add_node(g, 2, "C", 4, "E", 0);

	/* second community */ 
	add_node(g, 4, "E", 5, "F", 0);
	add_node(g, 5, "F", 6, "G", 0);
	add_node(g, 6, "G", 4, "E", 0);
	add_node(g, 6, "G", 7, "H", 0);
	add_node(g, 7, "H", 7, "H", 0);

	/* test to regular matrix conversion */ 
	adj_mat_t *output = to_matrix(result, g, false);
	int v = output->v;

	/* check output */ 
	for(int i = 0; i < vertices; i++) {
		for(int j = 0; j < vertices; j++) {
			assert(output->items[i*v+j]->id == expected_output[i][j]);
		}
	}

	printf("%s::%s... \e[0;32mPASSED\e[0m\n", __FILE__, __FUNCTION__);
}


void test_to_directed_matrix() {

	
	/* test transpose of adjacency list */
    int vertices = 8; 
	int equality_status = TRUE;

	/* expected result after directed matrix conversion */
	int expected_output[8][8] = {
		{-1,1,-1,-1,-1,-1,-1,-1},
		{-1,-1,2,-1,-1,-1,-1,-1},
		{-1,-1,-1,3,4,-1,-1,-1},
		{0,-1,-1,-1,-1,-1,-1,-1},
		{-1,-1,-1,-1,-1,5,-1,-1},
		{-1,-1,-1,-1,-1,-1,6,-1},
		{-1,-1,-1,-1,4,-1,-1,7},
		{-1,-1,-1,-1,-1,-1,-1,7}
	};	

	/* create adjacency list */ 
	adj_list_t *g = init_adj_list(vertices, vertices, true);
	adj_mat_t *result = init_adj_mat(vertices, vertices, true); 

	/* first community */ 
	add_node(g, 0, "A", 1, "B", 0);
	add_node(g, 1, "B", 2, "C", 0);
	add_node(g, 2, "C", 3, "D", 0);
	add_node(g, 3, "D", 0, "A", 0);

	/* bridge */ 
	add_node(g, 2, "C", 4, "E", 0);

	/* second community */ 
	add_node(g, 4, "E", 5, "F", 0);
	add_node(g, 5, "F", 6, "G", 0);
	add_node(g, 6, "G", 4, "E", 0);
	add_node(g, 6, "G", 7, "H", 0);
	add_node(g, 7, "H", 7, "H", 0);

	/* test directed matrix conversion */ 
	adj_mat_t *output = to_matrix(result, g, true);
	int v = output->v; 


	/* check output */ 
	for(int i = 0; i < vertices; i++) {
		for(int j = 0; j < vertices; j++) {
			assert(output->items[i*v+j]->id == expected_output[i][j]);
		}
	}

	printf("%s::%s... \e[0;32mPASSED\e[0m\n", __FILE__, __FUNCTION__);
}


void test_to_weighted_matrix() {

	/* vertices and equality status */ 
	int vertices = 5;
	int equality_status = TRUE;

	/* expected result after directed matrix conversion */
	int expected_output[5][5] = {
		{-1,1,2,3,-1},
		{1,-1,4,-1,-1},
		{2,4,-1,-1,5},
		{3,-1,-1,-1,-1},
		{-1,-1,5,-1,-1},
	};	

	/* create adj lists */ 
	adj_list_t *g = init_adj_list(vertices, vertices, false);
	adj_mat_t *result = init_adj_mat(vertices, vertices, false);


	/* build graph */ 
	add_node(g, 0, "A", 1, "B", 1);
	add_node(g, 0, "A", 2, "C", 2); 
	add_node(g, 0, "A", 3, "D", 3); 
	add_node(g, 1, "B", 2, "C", 4);
	add_node(g, 4, "E", 2, "C", 5);


	/* test directed matrix conversion */ 
	adj_mat_t *output = to_matrix(result, g, false);
	int v = output->v; 

	/* check output */ 
	for(int i = 0; i < vertices; i++) {
		for(int j = 0; j < vertices; j++) {
			if(output->items[i*v+j]->node_type->node->weight != expected_output[i][j]) {
				assert(output->items[i*v+j]->id == expected_output[i][j]);
			}
		}
	}

	/* validate results */ 
	if(!equality_status) {
		printf("%s::%s... FAILED\n", __FILE__, __FUNCTION__); 
	} else {
		printf("%s::%s... \e[0;32mPASSED\e[0m\n", __FILE__, __FUNCTION__);
	}
}


void test_to_directed_weighted_matrix() {

	/* vertices and equality status */ 
	int vertices = 8; 
	int equality_status = TRUE;

	/* expected result after directed matrix conversion */
	int expected_output[8][8] = {
		{-1,1,-1,-1,-1,-1,-1,-1},
		{-1,-1,2,-1,-1,-1,-1,-1},
		{-1,-1,-1,3,5,-1,-1,-1},
		{4,-1,-1,-1,-1,-1,-1,-1},
		{-1,-1,-1,-1,-1,6,-1,-1},
		{-1,-1,-1,-1,-1,-1,7,-1},
		{-1,-1,-1,-1,8,-1,-1,9},
		{-1,-1,-1,-1,-1,-1,-1,10}
	};	

	/* test first example of weighted matrix */ 
	adj_list_t *g = init_adj_list(vertices, vertices, true);
	adj_mat_t *result = init_adj_mat(vertices, vertices, true); 

	/* first community */ 
	add_node(g, 0, "A", 1, "B", 1);
	add_node(g, 1, "B", 2, "C", 2);
	add_node(g, 2, "C", 3, "D", 3);
	add_node(g, 3, "D", 0, "A", 4);

	/* bridge */ 
	add_node(g, 2, "C", 4, "E", 5);

	/* second community */ 
	add_node(g, 4, "E", 5, "F", 6);
	add_node(g, 5, "F", 6, "G", 7);
	add_node(g, 6, "G", 4, "E", 8);
	add_node(g, 6, "G", 7, "H", 9);
	add_node(g, 7, "H", 7, "H", 10);

	/* test directed matrix conversion */ 
	adj_mat_t *output = to_matrix(result, g, true);
	int v = output->v; 

	/* check output */ 
	for(int i = 0; i < vertices; i++) {
		for(int j = 0; j < vertices; j++) {
			assert(output->items[i*v+j]->id == expected_output[i][j]);
		}
	}

	printf("%s::%s... \e[0;32mPASSED\e[0m\n", __FILE__, __FUNCTION__);
}


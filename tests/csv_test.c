#include "includes/csv_test.h"


void test_populate_headers() {

	/* test these */
	int equality_status = TRUE; 
	csv_t *file = csv_init("../examples/data/test.csv", FILE_BUFFER_SIZE, 4);
	if(!file->status) {
		exit(0); 
	}

	/* expected results */ 
	char csv_cols[4][100] = {
		"src_id", "src_label", "dest_id", "dest_label"	
	}; 

	for(int i = 0; i < file->col_count; i++) {
	   	int condition = strcmp(csv_cols[i], file->cols[i]->name) == 0;
		if(!condition) {
			equality_status = FALSE; 
		}	
	}


 	/* validate results */
    if(!equality_status) {
        printf("%s::%s... FAILED\n", __FILE__, __FUNCTION__);
    }
    printf("%s::%s... \e[0;32mPASSED\e[0m\n", __FILE__, __FUNCTION__);
}



void test_populate_headers_two() {

	/* test these */
	int equality_status = TRUE; 
	csv_t *file = csv_init("../examples/data/movies.csv", FILE_BUFFER_SIZE, 10);
	if(!file->status) {
		exit(0); 
	}

	/* expected results */ 
	char csv_cols[8][100] = {
		"index", "movie_name", "year_of_release", "category",
		"run_time", "genre", "imdb_rating", "votes"	
	}; 

	for(int i = 0; i < file->col_count; i++) {

	   	int condition = strcmp(csv_cols[i], file->cols[i]->name) == 0;
		if(!condition) {
			equality_status = FALSE; 
		}	
	}

 	/* validate results */
    if(!equality_status) {
        printf("%s::%s... FAILED\n", __FILE__, __FUNCTION__);
    }
    printf("%s::%s... \e[0;32mPASSED\e[0m\n", __FILE__, __FUNCTION__);
}



void test_populate_headers_three() {

	/* test these */
	int equality_status = TRUE; 
	csv_t *file = csv_init("../examples/data/store_orders.csv", FILE_BUFFER_SIZE, 10);
	if(!file->status) {
		exit(0); 
	}

	/* expected results */ 
	char csv_cols[20][100] = {
		"order_id", "order_date", "ship_date", "ship_mode",
		"customer_name", "segment", "state", "country",
		"market", "region", "product_id", "category",
		"sub_category", "product_name", "sales", "quantity",
		"discount", "profit", "shipping_cost", "order_priority"	
	}; 

	/* starting at 1 because order_id is messed up */ 
	for(int i = 1; i < file->col_count; i++) {
	   	int condition = strcmp(csv_cols[i], file->cols[i]->name) == 0;
		if(!condition) {
			equality_status = FALSE; 
		}
	}

 	/* validate results */
    if(!equality_status) {
        printf("%s::%s... FAILED\n", __FILE__, __FUNCTION__);
    }
    printf("%s::%s... \e[0;32mPASSED\e[0m\n", __FILE__, __FUNCTION__);
}



void test_populate_headers_four() {

	/* test these */
	int equality_status = TRUE; 
	csv_t *file = csv_init("../examples/data/power_generation.csv", FILE_BUFFER_SIZE, 10);
	if(!file->status) {
		exit(0); 
	}

	/* expected results */ 
	char csv_cols[10][100] = {
		"Dates", "Power Station", "Monitored Cap.(MW)", "Total Cap. Under Maintenace (MW)",
		"Planned Maintanence (MW)", "Forced Maintanence(MW)", "Other Reasons (MW)",
		"Programme or Expected(MU)", "Actual(MU)", "Excess(+) / Shortfall (-)"
	}; 

	/* starting at 1 because order_id is messed up */ 
	for(int i = 0; i < file->col_count; i++) {
	   	int condition = strcmp(csv_cols[i], file->cols[i]->name) == 0;
		if(!condition) {
			equality_status = FALSE; 
		}
	}

 	/* validate results */
    if(!equality_status) {
        printf("%s::%s... FAILED\n", __FILE__, __FUNCTION__);
    }
    printf("%s::%s... \e[0;32mPASSED\e[0m\n", __FILE__, __FUNCTION__);
}


void test_populate_rows() {

	/* test this */ 
	int equality_status = TRUE; 
	csv_t *csv = csv_init("../examples/data/test.csv", FILE_BUFFER_SIZE, 4);
	if(!csv->status) {
		exit(0); 
	}

	/* expected results */ 
	char rows[4][4][10] = {
		{"0", "0", "0", "0"},
		{"0", "A", "1", "B"},
		{"0", "A", "2", "C"},
		{"0", "A", "3", "D"},
	};

	/* iterate through rows and confirm equality */ 
	for(int i = 0; i < csv->row_limit; i++) {
		if(i != 0) {
			for(int j = 0; j < csv->rows[i]->value_count; j++) {
				int condition = strcmp(csv->rows[i]->line[j], rows[i][j]) == 0; 
				if(!condition) {
					equality_status = FALSE; 
				}
        	}
		}
    }


 	/* validate results */
    if(!equality_status) {
        printf("%s::%s... FAILED\n", __FILE__, __FUNCTION__);
    }
    printf("%s::%s... \e[0;32mPASSED\e[0m\n", __FILE__, __FUNCTION__);
}


void test_invalid_file() {

	int equality_status = FALSE; 
	csv_t *file = csv_init("../examples/data/random.csv", FILE_BUFFER_SIZE, 4);
	if(!file->status) {
		equality_status = TRUE; 
	}

 	/* validate results */
    if(!equality_status) {
        printf("%s::%s... FAILED\n", __FILE__, __FUNCTION__);
    }
    printf("%s::%s... \e[0;32mPASSED\e[0m\n", __FILE__, __FUNCTION__);



}

void test_csv_structure() {

	int equality_status = TRUE; 
	int row_limit = 4;  
	char filepath[100] = "../examples/data/test.csv"; 

	csv_t *file = csv_init(filepath, FILE_BUFFER_SIZE, row_limit);
	if(!file->status) {
		equality_status = TRUE; 
	}

	/* check attributes */ 
	int buffer_check = FILE_BUFFER_SIZE == file->buffer_size; 
	int row_check = file->row_limit == row_limit; 
	int filename_check = strcmp(filepath, file->filename) == 0;

	if(!buffer_check || !row_check) {
		equality_status = FALSE;
	}

	if(!filename_check) {
		equality_status = FALSE; 
	}

 	/* validate results */
    if(equality_status == FALSE) {
        printf("%s::%s... FAILED\n", __FILE__, __FUNCTION__);
    }
    printf("%s::%s... \e[0;32mPASSED\e[0m\n", __FILE__, __FUNCTION__);
}



void test_csv_to_graph() {

	/* variables */ 
	int equality_status = TRUE; 
	int row_limit = 4;  
	int indices[2] = {1, 3}; 
	char filepath[100] = "../examples/data/test.csv"; 

	/* csv structure */ 
	csv_t *file = csv_init(filepath, FILE_BUFFER_SIZE, row_limit);
	if(!file->status) {
		equality_status = TRUE; 
	}

	/* convert to graph */ 
	graph_t *g = csv_to_unweighted_graph(file, indices, 2, false);

	char *relationship_list[8][5] = {
		{"src_label"}, 
		{"B", "C", "D"}, 
		{"A"},
		{"A"},
		{"A"},
		{},
		{},
		{}
	}; 

	for(int i = 0; i < g->v; i++) {
		node_t *head = g->items[i].head; 
		int node_index = 0; 
		while(head) {
			int condition = strcmp(head->label, relationship_list[i][node_index]);
			if(condition != 0) {
				equality_status = FALSE; 
			}
			head = head->next;
		   	node_index += 1; 
		}
	} 

 	/* validate results */
    if(equality_status == FALSE) {
        printf("%s::%s... FAILED\n", __FILE__, __FUNCTION__);
    }
    printf("%s::%s... \e[0;32mPASSED\e[0m\n", __FILE__, __FUNCTION__);
}

void test_csv_to_graph_two() {

	/* variables */ 
	int equality_status = TRUE; 
	int row_limit = 5;  
	int indices[2] = {1, 3}; 
	char filepath[100] = "../examples/data/power_generation.csv"; 

	/* expected relationships */ 
	char *relationship_list[10][10] = {
		{"Power Station"}, 
		{"135.0"}, 
		{"Delhi"},
		{"2470.0"},
		{"Haryana"},
		{"379.0"},
		{"Himachal Pradesh"},
		{"150.0"},
		{"Jammu and Kashmir"},
		{}
	}; 


	/* csv structure */ 
	csv_t *file = csv_init(filepath, FILE_BUFFER_SIZE, row_limit);
	if(!file->status) {
		equality_status = TRUE; 
	}

	/* convert to graph */
	int vertex_count = file->row_limit * 2; 
	graph_t *g = csv_to_unweighted_graph(file, indices, 2, false);

	/* check graph against relationships */ 
	for(int i = 0; i < g->v; i++) {
		node_t *head = g->items[i].head; 
		int node_index = 0; 
		while(head) {
			int condition = strcmp(head->label, relationship_list[i][node_index]);
			if(condition != 0) {
				equality_status = FALSE; 
			}
			head = head->next;
		   	node_index += 1; 
		}
	} 

 	/* validate results */
    if(equality_status == FALSE) {
        printf("%s::%s... FAILED\n", __FILE__, __FUNCTION__);
    }
    printf("%s::%s... \e[0;32mPASSED\e[0m\n", __FILE__, __FUNCTION__);

}


void test_csv_to_graph_three() {

	/* variables */ 
	int equality_status = TRUE; 
	int row_limit = 5;  
	int indices[2] = {1, 5}; 
	char filepath[100] = "../examples/data/movies.csv";

	/* expected relationships */ 
	char *relationship_list[10][10] = {
		{"movie_name"}, 
		{"\"Crime"}, 
		{"The Godfather", "The Silence of the Lambs"},
		{"\"Crime"},
		{"\"Action"},
		{"Star Wars: Episode V - The Empire Strikes Back"},
		{"Drama"},
		{"The Shawshank Redemption"},
		{}
	}; 

	/* csv structure */ 
	csv_t *file = csv_init(filepath, FILE_BUFFER_SIZE, row_limit);
	if(!file->status) {
		equality_status = TRUE; 
	}

	/* convert to graph */ 
	graph_t *g = csv_to_unweighted_graph(file, indices, 2, false);

	/* check graph against relationships */ 
	for(int i = 0; i < g->v; i++) {
		node_t *head = g->items[i].head; 
		int node_index = 0; 
		while(head) {
			int condition = strcmp(head->label, relationship_list[i][node_index]);
			if(condition != 0) {
				equality_status = FALSE; 
			}
			head = head->next;
		   	node_index += 1; 
		}
	} 

 	/* validate results */
    if(equality_status == FALSE) {
        printf("%s::%s... FAILED\n", __FILE__, __FUNCTION__);
    }
    printf("%s::%s... \e[0;32mPASSED\e[0m\n", __FILE__, __FUNCTION__);
}


void test_even_pair_feature_pass() {

	/* variables */ 
	int equality_status = TRUE; 
	int row_limit = 5;  
	int indices[4] = {4, 6, 7, 8}; // should be pairs of 2
	char filepath[100] = "../examples/data/store_orders.csv";

	/* expected relationships */ 
	char *relationship_list[20][20] = {
		{"customer_name"}, 
		{"Constantine"}, 
		{"Toby Braunhardt"},
		{"New South Wales"},
		{"Joseph Holt"},
		{"Budapest"},
		{"Annie Thurman"},
		{"Stockholm"},
		{"Eugene Moren"},
		{"Africa"},
		{"Algeria"},
		{"APAC"},
		{"Australia"},
		{"EMEA"},
		{"Hungary"},
		{"EU"},
		{"Sweden"},
		{},
		{},
		{}
	}; 

	/* csv structure */ 
	csv_t *file = csv_init(filepath, FILE_BUFFER_SIZE, row_limit);
	if(!file->status) {
		equality_status = TRUE; 
	}

	/* convert to graph */ 
	graph_t *g = csv_to_unweighted_graph(file, indices, 4, false);


	/* check graph against relationships */ 
	for(int i = 0; i < g->v; i++) {
		node_t *head = g->items[i].head; 
		int node_index = 0; 
		while(head) {
			int condition = strcmp(head->label, relationship_list[i][node_index]);
			if(condition != 0) {
				equality_status = FALSE; 
			}
			head = head->next;
		   	node_index += 1; 
		}
	}


 	/* validate results */
    if(equality_status == FALSE) {
        printf("%s::%s... FAILED\n", __FILE__, __FUNCTION__);
    }
    printf("%s::%s... \e[0;32mPASSED\e[0m\n", __FILE__, __FUNCTION__);
}


void test_even_pair_feature_fail() {

	/* variables */ 
	int equality_status = TRUE; 
	int row_limit = 5;
	int indices[3] = {4, 6, 7}; // should fail since it's not in pairs of 2
	char filepath[100] = "../examples/data/store_orders.csv";

	/* csv structure */ 
	csv_t *file = csv_init(filepath, FILE_BUFFER_SIZE, row_limit);
	if(!file->status) {
		equality_status = TRUE; 
	}

	/* convert to graph */ 
	graph_t *g = csv_to_unweighted_graph(file, indices, 3, false);
   	if(!g->err) {
		equality_status = FALSE; 
	}

 	/* validate results */
    if(equality_status == FALSE) {
        printf("%s::%s... FAILED\n", __FILE__, __FUNCTION__);
    }
    printf("%s::%s... \e[0;32mPASSED\e[0m\n", __FILE__, __FUNCTION__);


}


void test_odd_pair_feature_pass() {

	/* variables */ 
	int equality_status = TRUE; 
	int row_limit = 5;
	int indices[3] = {4, 6, 15}; // should fail since it's not in pairs of 2
	char filepath[100] = "../examples/data/store_orders.csv";

	/* csv structure */ 
	csv_t *file = csv_init(filepath, FILE_BUFFER_SIZE, row_limit);
	if(!file->status) {
		equality_status = TRUE; 
	}

	/* convert to graph */ 
	graph_t *g = csv_to_weighted_graph(file, indices, 3, false);
	printf("Graph status: %d\n", g->err);
   	if(!g->err) {
		equality_status = FALSE; 
	}


}

/**
 * Test Multi feature select (More than 2 features)
 * Test if the pairs are not correct (not 2 or 3)
 * Create the same set of test cases for the weighted graph
 */



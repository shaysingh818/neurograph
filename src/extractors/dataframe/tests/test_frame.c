#include "includes/test_frame.h"


void test_create_frame() {


    bool equality_status = true; 
    int row_limit = 5, buffer_size = 2048; 
    char *filepath = "../../../examples/data/movies.csv"; 

    frame_t *frame = create_frame(filepath, buffer_size, row_limit, NULL);
    assert(frame->status); 
    assert(strcmp(filepath, frame->filename) == 0);
    assert(frame->row_limit == row_limit);
    assert(frame->buffer_size == buffer_size); 
    assert(frame->frame->size == 1); 

    /* confirm we're using a compare character function for hash */
    bool compare_value = frame->frame->key_cmp("test", "test"); 
    assert(compare_value);  

    printf("%s::%s... \e[0;32mPASSED\e[0m\n", __FILE__, __FUNCTION__);
}


void test_extract_frame_headers() {

    bool equality_status = true; 

    /* test frame with movies.csv */
	char movie_cols[9][100] = {
		"index", "movie_name", "year_of_release", "category",
        "run_time", "genre", "imdb_rating", "votes", "gross_total"	
	};

	/* columns from power_generation.csv */ 
	char power_gen_cols[11][100] = {
		"Dates", "Power Station", "Monitored Cap.(MW)", "Total Cap. Under Maintenace (MW)",
		"Planned Maintanence (MW)", "Forced Maintanence(MW)", "Other Reasons (MW)",
		"Programme or Expected(MU)", "Actual(MU)", "Excess(+) / Shortfall (-)", "Deviation"
	}; 


    /* frame for movies.csv*/
    frame_t *frame = create_frame("../../../examples/data/movies.csv", 1024, 100, NULL);
    assert(frame->status);
 
    extract_headers(frame);
    assert(frame->status); 

    for(int i = 0; i < frame->headers->item_count; i++){
        bool condition = strcmp(frame->headers->items[i]->node_type->node->label, movie_cols[i]) == 0; 
        assert(condition); 
    }

    frame_t *frame2 = create_frame(
        "../../../examples/data/power_generation.csv", 
        1024, 
        100,
        NULL
    );
    assert(frame2->status);
 
    extract_headers(frame2);
    assert(frame2->status); 

    for(int i = 0; i < frame2->headers->item_count; i++){
        bool condition = strcmp(frame2->headers->items[i]->node_type->node->label, power_gen_cols[i]) == 0; 
        assert(condition); 
    }
    printf("%s::%s... \e[0;32mPASSED\e[0m\n", __FILE__, __FUNCTION__);
}


void test_init_rows() {

    bool equality_status = true; 
    char *filepath = "../../../examples/data/movies.csv"; 

    frame_t *frame = create_frame(filepath, 2048, 5, NULL);
    assert(frame->status); 

    extract_headers(frame);
    assert(frame->status); 

    init_rows(frame);
    assert(frame->status);

   char *expected_years[100] = {"(1972)", "(1991)", "(1980)", "(1994)", "(1980)"}; 
   char *expected_ratings[100] = {"9.2", "8.6", "8.7", "9.3", "8.4"}; 
   char *expected_categories[100] = {"R", "R", "PG", "R", "R"};
   char *expected_runtimes[100] = {"175 min", "118 min", "124 min", "142 min", "146 min"}; 
   char *expected_names[100] = {
        "The Godfather", 
        "The Silence of the Lambs",
        "Star Wars: Episode V - The Empire Strikes Back",
        "The Shawshank Redemption",
        "The Shining"
    }; 

    row_value_t **year_values = lookup_table_key(frame->frame, "year_of_release");  
    row_value_t **ratings_values = lookup_table_key(frame->frame, "imdb_rating");
    row_value_t **category_values = lookup_table_key(frame->frame, "category");
    row_value_t **name_values = lookup_table_key(frame->frame, "movie_name");
    row_value_t **runtime_values = lookup_table_key(frame->frame, "run_time");

    for(int j = 0; j < frame->row_limit; j++){

        bool year_compare = strcmp(year_values[j]->value, expected_years[j]) == 0; 
        bool ratings_compare = strcmp(ratings_values[j]->value, expected_ratings[j]) == 0;  
        bool category_compare = strcmp(category_values[j]->value, expected_categories[j]) == 0; 
        bool name_compare = strcmp(name_values[j]->value, expected_names[j]) == 0; 
        bool runtime_compare = strcmp(runtime_values[j]->value, expected_runtimes[j]) == 0; 

        assert(year_compare); 
        assert(ratings_compare); 
        assert(category_compare); 
        assert(name_compare); 
        assert(runtime_compare); 

    }

    printf("%s::%s... \e[0;32mPASSED\e[0m\n", __FILE__, __FUNCTION__);

}


void test_dataframe() {

    char *filepath = "../../../examples/data/movies.csv"; 
    frame_t *frame = dataframe(filepath, 2048, 5, NULL);
    assert(frame->status);
    assert(frame->headers->item_count == 9);
    assert(frame->row_limit == 5); 
    assert(frame->curr_row == 5); 

	char expected_headers[9][100] = {
		"index", "movie_name", "year_of_release", "category",
        "run_time", "genre", "imdb_rating", "votes", "gross_total"	
	};

    for(int i = 0; i < frame->headers->item_count; i++){
        bool compare = strcmp(
            expected_headers[i], 
            frame->headers->items[i]->node_type->node->label
        ); 
        assert(compare == 0); 
    }

    /* check all files */
    char *files[100] = {
        "../../../examples/data/city_population_density.csv",
        "../../../examples/data/iris.csv",
        "../../../examples/data/public_transport.csv",
        "../../../examples/data/movies.csv",
        "../../../examples/data/ms_prediction.csv",
        "../../../examples/data/online_retail.csv",
        "../../../examples/data/power_generation.csv"
    }; 

    for(int i = 0; i < 7; i++){
        char *filepath = files[i]; 
        frame_t *data_frame = dataframe(filepath, 1024, 5, NULL);
        assert(data_frame->status);
        assert(data_frame->headers->item_count >= 1);
        assert(data_frame->row_limit == 5);         
    }

 
    printf("%s::%s... \e[0;32mPASSED\e[0m\n", __FILE__, __FUNCTION__);
} 


void test_frame_to_matrix() {

    char *filepath = "../../../examples/data/rice.csv"; 
    frame_t *frame = dataframe(filepath, 2048, 5, NULL);
    assert(frame->status);

    /* get cols here */
    array_t *selected_cols = init_array(); 
    insert_char(selected_cols, "Area"); 
    insert_char(selected_cols, "MajorAxisLength");
    insert_char(selected_cols, "MinorAxisLength"); 

    mat_t *result = frame_to_matrix(frame, selected_cols);
    assert(result->rows == 5); 
    assert(result->cols == 3);

    /* validate row contents */
    double result_vals[5][3] = {
        {4537,92.23,64.01},
        {2872,74.69,51.40},
        {3048,76.29,52.04},
        {3073,77.03,51.93},
        {3693,85.12,56.37}
    }; 

    mat_t *result_mat = copy_arr_to_matrix(5, 3, result_vals);
    assert(compare_matrix(result_mat, result)); 

    /* movies dataset */
    frame_t *movie_frame = dataframe("../../../examples/data/movies.csv", 1024, 5, NULL);
    assert(movie_frame->status); 

    array_t *movie_cols = init_array(); 
    insert_char(movie_cols, "imdb_rating");

    mat_t *movie_matrix = frame_to_matrix(movie_frame, movie_cols);
    assert(movie_matrix->rows == 5); 
    assert(movie_matrix->cols == 1);  

    double result_vals2[5][1] = {{9.2},{8.6},{8.7},{9.3}, {8.4}}; 
    result_mat = copy_arr_to_matrix(5, 1, result_vals2); 
    assert(compare_matrix(movie_matrix, result_mat));


    printf("%s::%s... \e[0;32mPASSED\e[0m\n", __FILE__, __FUNCTION__);

}


void test_drop_cols() {

    char *filepath = "../../../examples/data/rice.csv"; 
    frame_t *frame = dataframe(filepath, 2048, 5, NULL);
    assert(frame->status);

    /* columns to drop  */
    array_t *selected_cols = init_array(); 
    insert_char(selected_cols, "Area"); 
    insert_char(selected_cols, "MajorAxisLength");
    insert_char(selected_cols, "MinorAxisLength");

    /* confirm cols are dropped */
    assert(frame->headers->item_count == 12);  
    drop_cols(frame, selected_cols); 
    assert(frame->headers->item_count == 9);  

    printf("%s::%s... \e[0;32mPASSED\e[0m\n", __FILE__, __FUNCTION__);
} 
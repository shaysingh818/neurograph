#include "includes/test_frame.h"
#include "../includes/re.h"


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
    frame_t *f = init_frame("../../examples/data/movies.csv", 1024, 100);
    assert(f->status == true);

    for(int i = 0; i < f->header_count; i++){
        int name_compare = strcmp(f->headers[i]->name, movie_cols[i]) == 0;
        assert(name_compare == true); 
    }


    /* frame for movies.csv*/
    frame_t *power_gen = init_frame(
        "../../examples/data/power_generation.csv", 
        1024, 1000
    );      
    assert(power_gen->status == true);  

    for(int i = 0; i < power_gen->header_count; i++){
        int name_compare = strcmp(power_gen->headers[i]->name, power_gen_cols[i]) == 0;
        assert(name_compare == true); 
    }

    /* frame for movies.csv*/
    frame_t *iris = init_frame(
        "../../examples/data/iris.csv", 
        1024, 100
    );      

    for(int i = 0; i < iris->header_count; i++){
        printf("%s", iris->headers[i]->name);
    }


 	/* validate results */
    if(!equality_status) {
        printf("%s::%s... FAILED\n", __FILE__, __FUNCTION__);
    }
    printf("%s::%s... \e[0;32mPASSED\e[0m\n", __FILE__, __FUNCTION__);
}


void test_init_frame_rows() {

    /* create dummy instance of frame */
    bool equality_status = true; 
    char *filename = "../../examples/data/movies.csv"; 
	size_t name_size = strlen(filename) + 1; 
	frame_t *frame = malloc(sizeof(frame_t));
   	frame->filename = (char*)malloc(name_size * sizeof(char)); 
	frame->buffer_size = 1024;
	frame->file_buffer = malloc(1024 * sizeof(char)); 
    frame->row_count = 100; 
	
   	strcpy(frame->filename, filename);

	/* check if file exists */
	if(access(filename, F_OK) == -1) {
   		strcpy(frame->filename, "");
		printf("File does not exist\n");
		frame->status = false; 
	}

    extract_frame_headers(frame);
    init_frame_rows_regex(frame); 

    /* check that values for headers are allocated with row count */
    for(int i = 0; i < frame->header_count; i++){
        header_t *header = frame->headers[i]; 
        int curr_count = 0; 
        for(int j = 0; j < header->values_amount; j++){
            row_value_t *value = header->values[j];
            curr_count += 1; 
        }
 
        /* check if rows are populated */
        assert(curr_count == frame->row_count);  
    } 

 	/* validate results */
    if(!equality_status) {
        printf("%s::%s... FAILED\n", __FILE__, __FUNCTION__);
    }
    printf("%s::%s... \e[0;32mPASSED\e[0m\n", __FILE__, __FUNCTION__);
}


void test_init_frame_structure() {

    bool equality_status = true; 
    frame_t *frame = init_frame("../../examples/data/online_retail.csv", 1024, 500); 

    /* put in expected values */
    int header_count = 8, row_count = 500, buffer_size=1024;
    bool header_condition = frame->header_count == header_count; 
    bool row_condition = frame->row_limit == row_count;
    bool buffer_condition = frame->buffer_size == buffer_size;

    assert(header_condition == true && row_condition == true); 
    assert(buffer_condition == true); 

 	/* validate results */
    if(!equality_status) {
        printf("%s::%s... FAILED\n", __FILE__, __FUNCTION__);
    }
    printf("%s::%s... \e[0;32mPASSED\e[0m\n", __FILE__, __FUNCTION__);

}


void test_hash_map_frame() {

    bool equality_status = true; 
    frame_t *frame = init_frame("../../examples/data/movies.csv", 2048, 100);
    assert(frame->status == true); 
    init_frame_map(frame);

    char *keys[100] = {
        "index", "movie_name", "year_of_release", "category", "run_time", "genre",
        "imdb_rating", "votes", "gross_total"
    };

    for(int j = 0; j < frame->header_count; j++){
        void *results = lookup_key(frame->map, frame->headers[j]->name); 
        bool condition = strcmp(frame->headers[j]->name, keys[j]) == 0;
        assert(condition == true); 

        row_value_t **values = (row_value_t**)results; 
        for(int i = 0; i < frame->row_count; i++){
            assert(values[i]->value != NULL); 
        }
    }

 	/* validate results */
    if(!equality_status) {
        printf("%s::%s... FAILED\n", __FILE__, __FUNCTION__);
    }
    printf("%s::%s... \e[0;32mPASSED\e[0m\n", __FILE__, __FUNCTION__);


}


void test_frame_to_matrix() {

    frame_t *frame = init_frame("../../examples/data/ms_prediction.csv", 1024, 5);
    if(frame->status != true){
        printf("Error in loading frame data\n");
    }

    array_t *selected_cols = init_array(); 
    insert_char(selected_cols, "Schooling"); 
    insert_char(selected_cols, "LLSSEP"); 
    insert_char(selected_cols, "ULSSEP"); 
    insert_char(selected_cols, "VEP"); 
    insert_char(selected_cols, "BAEP"); 

    mat_t *result = frame_to_mat(frame, selected_cols); 
    assert(result->rows == 5); 
    assert(result->cols == 5); 

    /* validate row contents */
    double result_vals[5][5] = {
        {0,0,0,0,0},
        {20,1,1,0,0},
        {25,1,0,1,0},
        {20,0,0,0,0},
        {15,0,1,1,0}
    }; 

    mat_t *result_mat = copy_arr_to_matrix(5, 5, result_vals); 
    assert(compare_matrix(result_mat, result)); 

    /* movies dataset */
    frame_t *movie_frame = init_frame("../../examples/data/movies.csv", 1024, 5);
    if(movie_frame->status != true){
        printf("Error in loading frame data\n");
    }

    array_t *movie_cols = init_array(); 
    insert_char(movie_cols, "imdb_rating");


    mat_t *movie_matrix = frame_to_mat(movie_frame, movie_cols);
    assert(movie_matrix->rows == 5); 
    assert(movie_matrix->cols == 1);  

    double result_vals2[5][1] = {{0},{9.2},{8.6},{8.7},{9.3}}; 
    result_mat = copy_arr_to_matrix(5, 1, result_vals2); 
    assert(compare_matrix(movie_matrix, result_mat)); 

    printf("%s::%s... \e[0;32mPASSED\e[0m\n", __FILE__, __FUNCTION__);

}


void test_match_frame_delimiter_file() {

    char *line = "125,2,\"36\",9,1,1,1,1,1,0,0,0,0,1,1,0,0,,,2";
    char *semi_line = "536365;WHITE HANGING HEART T-LIGHT HOLDER;6;01.12.2010 08:26;2,55;17850;United Kingdom";
    char *one = "IHHC583D5N89GD,2290319488646018,dki,Edison Kusmawati,F,2004,M1H,Tanah Abang - St. Gondangdia,0.0,P00056,Explorer Tanah Abang,-6.184305,106.81158,13,2023-04-03 05:15:51,B01787P,JPO Blok G,-6.188861,106.81135,16.0,2023-04-03 05:53:52,"; 
    char *two = "1,two,three"; 

    /* parse each */
    array_t *results = match_delimeter_file(line, ",");
    array_t *semi_results = match_delimeter_file(semi_line, ";");
    array_t *res = match_delimeter_file(one, ",");
    array_t *res2 = match_delimeter_file(two, ",");

    char *expected_results[100] = {
        "125", "2", "\"36\"", "9", "1", "1", "1",
        "1", "1", "0", "0", "0", "0", "1", "1", 
        "0", "0", "", "", "2"
    };

    char *expected_semicolon[100] = {
        "536365", "WHITE HANGING HEART T-LIGHT HOLDER", 
        "6", "01.12.2010 08:26", "2,55", "17850", "United Kingdom",
    };

    for(int i = 0; i < results->item_count; i++){
        int condition = strcmp(results->items[i]->label, expected_results[i]) == 0;
        assert(condition == true);  
    }

    for(int i = 0; i < results->item_count; i++){
        int condition = strcmp(results->items[i]->label, expected_results[i]) == 0;
        assert(condition == true);  
    }
    assert(res->item_count == 22);  

    printf("%s::%s... \e[0;32mPASSED\e[0m\n", __FILE__, __FUNCTION__);

} 


void test_match_header() {

    frame_t *frame = create_frame("../../examples/data/iris.csv", 1024, 5);
    if(frame->status != true){
        printf("Error in loading frame data\n");
    }

    extract_frame_headers(frame);
    // printf("Header count: %d\n", frame->header_count); 

    // for(int i = 0; i < frame->header_count; i++){
    //     printf("Header: %s\n", frame->headers[i]->name); ;
    // }

    int res = match_header(frame, "f5"); 
    printf("Res: %d\n", res); 





}
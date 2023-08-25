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
    frame_t *f = init_frame("../../examples/data/movies.csv", 1024);
    assert(f->status == true); 

    for(int i = 0; i < f->header_count; i++){
        int name_compare = strcmp(f->headers[i]->name, movie_cols[i]) == 0;
        assert(name_compare == true); 
    }

    /* frame for movies.csv*/
    frame_t *power_gen = init_frame("../../examples/data/power_generation.csv", 1024);  
    assert(power_gen->status == true);  

    for(int i = 0; i < power_gen->header_count; i++){
        int name_compare = strcmp(power_gen->headers[i]->name, power_gen_cols[i]) == 0;
        assert(name_compare == true); 
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
	
   	strcpy(frame->filename, filename);

	/* check if file exists */
	if(access(filename, F_OK) == -1) {
   		strcpy(frame->filename, "");
		printf("File does not exist\n");
		frame->status = false; 
	}
    
    extract_frame_headers(frame);
    init_frame_rows(frame); 

    /* check that values for headers are allocated with row count */
    for(int i = 0; i < frame->header_count; i++){
        header_t *header = frame->headers[i]; 
        int curr_count = 0; 
        for(int j = 0; j < header->values_amount; j++){
            value_t *value = header->values[j];
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
    frame_t *frame = init_frame("../../examples/data/movies.csv", 1024); 

    /* put in expected values */
    int header_count = 9, row_count = 100, buffer_size=1024;
    bool header_condition = frame->header_count == header_count; 
    bool row_condition = frame->row_count == row_count;
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
    frame_t *frame = init_frame("../../examples/data/city_population_density.csv", 1024);
    assert(frame->status == true); 

    init_frame_map(frame);

    char *keys[100] = {
        "Rank", "City", "Population", "Area KM2", "Area M2", "Density KM2",
        "Density  M2", "Country", "Year"
    };

    for(int j = 0; j < frame->header_count; j++){
        void *results = lookup_key(frame->map, frame->headers[j]->name); 
        bool condition = strcmp(frame->headers[j]->name, keys[j]) == 0;
        assert(condition == true); 

        value_t **values = (value_t**)results; 
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
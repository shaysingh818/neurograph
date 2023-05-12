#include "includes/test_frame.h"
#include "../includes/re.h"


void test_extract_frame_headers() {

    bool equality_status = true; 
	char movie_cols[9][100] = {
		"index", "movie_name", "year_of_release", "category",
        "run_time", "genre", "imdb_rating", "votes", "gross_total"	
	};

    frame_t *f = init_frame("../../examples/data/movies.csv", 1024);
    extract_frame_headers(f);
    for(int i = 0; i < f->header_count; i++){
        int name_compare = strcmp(f->headers[i]->name, movie_cols[i]) == 0;
        if(!name_compare) { equality_status = false; }
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
        if(curr_count != frame->row_count){
            equality_status = false; 
        }    
    } 

 	/* validate results */
    if(!equality_status) {
        printf("%s::%s... FAILED\n", __FILE__, __FUNCTION__);
    }
    printf("%s::%s... \e[0;32mPASSED\e[0m\n", __FILE__, __FUNCTION__);
}


void test_init_frame_structure() {

    bool equality_status = false; 
    frame_t *frame = init_frame("../../examples/data/movies.csv", 1024); 

    /* put in expected values */
    int header_count = 9, row_count = 100, buffer_size=1024;
    bool header_condition = frame->header_count == header_count; 
    bool row_condition = frame->row_count == row_count;
    bool buffer_condition = frame->buffer_size == buffer_size; 

    if(header_condition && row_condition && buffer_condition){
        equality_status = true; 
    } 

 	/* validate results */
    if(!equality_status) {
        printf("%s::%s... FAILED\n", __FILE__, __FUNCTION__);
    }
    printf("%s::%s... \e[0;32mPASSED\e[0m\n", __FILE__, __FUNCTION__);

}
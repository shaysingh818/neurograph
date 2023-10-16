#include "includes/test_frame_memory.h"


void test_match_delimeter_file() {

    char buffer[1024]; 
	FILE* fp = fopen("../../examples/data/iris.csv", "r");
   	int row_count = 0;
    int sizes[5] = {2,2,2,2,2}; 
    char *values[100] = {"f1", "f2", "f3", "f4", "f5"}; 

	while(fgets(buffer, 1024, fp)) {

		/* print out values */
		if(row_count > 0){
            break;  
		}

		/* null terminate the buffer */
        buffer[strcspn(buffer, "\n")-1] = 0;

		/* extract tokens from regular expression */
    	array_t *semi_results = match_delimeter_file(buffer, ",");
		int size = semi_results->item_count;
        assert(size == 5); 

        /* validate expected lengths of each string */
        for(int i = 0; i < size; i++){
            size_t result_size = strlen(semi_results->items[i]->label);
            bool compare = strcmp(semi_results->items[i]->label, values[i]) == 0;
            assert(result_size == sizes[i]); 
            assert(compare == true); 
        }

		row_count += 1;
	}

    printf("%s::%s... \e[0;32mPASSED\e[0m\n", __FILE__, __FUNCTION__);
}


void test_allocate_frame_headers() {

    char *filename = "../../examples/data/movies.csv"; 
    size_t name_size = strlen(filename) + 1;
    int buffer_size = 1024, row_limit = 100;
    array_t *headers; 
    frame_t *frame = create_frame(filename, buffer_size, 100); 

	FILE* fp = fopen(frame->filename, "r");


    /* read in file buffer and allocate headers  */
	while(fgets(frame->file_buffer, frame->buffer_size, fp)) {
        frame->file_buffer[strcspn(frame->file_buffer, "\n")] = 0;
        if(frame->row_count == 0){
    	    headers = match_delimeter_file(frame->file_buffer, ",");
		    int size = headers->item_count;
            assert(size == 9); 
            allocate_frame_headers(frame, headers);
            break;  
        } 

	}

    /* validate allocated values */
    assert(frame->header_count == 9);
    for(int i = 0; i < frame->header_count; i++){
        char *header_val = frame->headers[i]->name;
        char *array_header = headers->items[i]->label;  
        assert(frame->headers[i]->index == i);  
        assert(strcmp(header_val, array_header) == 0);
        assert(frame->headers[i]->name_size == strlen(array_header)+1); 
    } 

    printf("%s::%s... \e[0;32mPASSED\e[0m\n", __FILE__, __FUNCTION__);
}


void test_copy_row_values() {

    char *filename = "../../examples/data/movies.csv"; 
    size_t name_size = strlen(filename) + 1;
    int buffer_size = 1024, row_limit = 3, row_count = 0;
    frame_t *frame = create_frame(filename, buffer_size, row_limit);
    frame->curr_row = 0; 

	FILE* fp = fopen(frame->filename, "r");

    char *expected_rows[9][100] = {
        {"1.", "The Godfather", "(1972)", "R", "175 min", "\"Crime, Drama\"", "9.2", "\"1,860,471\"", "$134.97M"},
        {"2.", "The Silence of the Lambs", "(1991)", "R", "118 min", "\"Crime, Drama, Thriller\"", "8.6", "\"1,435,344\"", "$130.74M"}
    };


    /* read in file buffer and allocate headers  */
	while(fgets(frame->file_buffer, frame->buffer_size, fp)) {

        if(frame->curr_row == frame->row_limit){
            break; 
        }

        frame->file_buffer[strcspn(frame->file_buffer, "\n")] = 0;

        if(frame->curr_row == 0){
            
    	    array_t *headers = match_delimeter_file(frame->file_buffer, ",");
            allocate_frame_headers(frame, headers);
            allocate_header_rows(frame);  

        } else {

    	    array_t *row_vals = match_delimeter_file(frame->file_buffer, ",");
            copy_row_values(frame, row_vals);
            for(int i = 0; i < row_vals->item_count; i++){
                int index = frame->curr_row; 
                char *row_val = frame->headers[i]->values[index]->value; 
                size_t row_size = frame->headers[i]->values[index]->value_size; 
                int set_index = frame->headers[i]->values[index]->index; 
                assert(strcmp(expected_rows[row_count][i], row_val) == 0); 
                assert(set_index == frame->curr_row);  
                assert(strlen(row_val)+1 == row_size); 
            }
            row_count += 1; 
        }
        frame->curr_row += 1;  
	}

    printf("%s::%s... \e[0;32mPASSED\e[0m\n", __FILE__, __FUNCTION__);
} 
#include "includes/test_frame_lib.h"

void test_frame(test_t *t, array_t *args, array_t *outputs) {

    char *file_arg = args->items[0]->label; 
    int buffer_size = atoi(args->items[1]->label); 
    int row_limit = atoi(args->items[2]->label);

    /* call method here */
    frame_t *f = init_frame(
        file_arg, 
        buffer_size, 
        row_limit
    ); 

    int row_output = atoi(outputs->items[0]->label); 
    assert(f->row_count == row_output); 
    assert(f->status == true);      
}


void test_frame_matrix(test_t *t, array_t *args, array_t *outputs) {

    char *file_arg = args->items[0]->label; 
    int buffer_size = atoi(args->items[1]->label); 
    int row_limit = atoi(args->items[2]->label);
    array_t *results = match_delimeter_file(args->items[3]->label, ";");
    char **cols = convert_input_file_char_array(results);  

    /* call method here */
    frame_t *f = init_frame(
        file_arg, 
        buffer_size, 
        row_limit
    ); 

    mat_t *result = frame_to_mat(f, cols, results->item_count); 
    print_vec(result);
    printf("\n");  

}
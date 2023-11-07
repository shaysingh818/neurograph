#include "includes/test_ops.h"


void test_add_frame_cols() {

    char *expected_vals[100] = {"8.60", "7.90", "7.90", "7.70", "8.60"}; 
    char *iris = "../../../examples/data/iris.csv"; 
    char *filepath = "../../../examples/data/rice.csv"; 
    frame_t *frame = dataframe(filepath, 2048, 5, NULL);
    assert(frame->status);

    /* call add method */
    assert(frame->headers->item_count == 12);  
    frame_t *result = add_frame_cols(frame, "id", "Area"); 
    assert(frame->status);
    assert(frame->headers->item_count == 13);  

    frame_t *iris_frame = dataframe(iris, 2048, 5, NULL);
    assert(iris_frame->status);

    frame_t *iris_add = add_frame_cols(iris_frame, "f1", "f2"); 
    assert(iris_add->status);

    /* validate results */
    row_value_t **results = lookup_table_key(iris_add->frame, "result"); 
    for(int i = 0; i < 5; i++){
        bool compare = strcmp(results[i]->value, expected_vals[i]) == 0;  
        assert(compare); 
    }

    printf("%s::%s... \e[0;32mPASSED\e[0m\n", __FILE__, __FUNCTION__);
}


void test_subtract_frame_cols() {

    char *expected_vals[100] = {"1.60", "1.90", "1.50", "1.50", "1.40"}; 
    char *iris = "../../../examples/data/iris.csv"; 
    char *filepath = "../../../examples/data/rice.csv"; 
    frame_t *frame = dataframe(filepath, 2048, 5, NULL);
    assert(frame->status);

    /* call add method */
    assert(frame->headers->item_count == 12);  
    frame_t *result = subtract_frame_cols(frame, "id", "Area"); 
    assert(frame->status);
    assert(frame->headers->item_count == 13);  

    frame_t *iris_frame = dataframe(iris, 2048, 5, NULL);
    assert(iris_frame->status);

    frame_t *iris_add = subtract_frame_cols(iris_frame, "f1", "f2"); 
    assert(iris_add->status);

    /* validate results */
    row_value_t **results = lookup_table_key(iris_add->frame, "result"); 
    for(int i = 0; i < 5; i++){
        bool compare = strcmp(results[i]->value, expected_vals[i]) == 0;  
        assert(compare); 
    }

    printf("%s::%s... \e[0;32mPASSED\e[0m\n", __FILE__, __FUNCTION__);
}
#include "includes/operations.h"


void add_frame_cols(frame_t *frame, char *col1, char *col2, char *result_col) {

    void *col1_ptr = (void*)col1; 
    void *col2_ptr = (void*)col2; 

    /* look up values and allocate where results are stored */
    row_value_t **r1 = lookup_table_key(frame->frame, col1_ptr); 
    row_value_t **r2 = lookup_table_key(frame->frame, col2_ptr);
    row_value_t **result = malloc(frame->row_limit * sizeof(row_value_t*)); 
    insert_char(frame->headers, result_col);
    frame->header_count += 1; 

    /* allocate space for key size (C didn't catch this but python did ) */
    size_t result_key_size = strlen(result_col)+1; 
    char *key_val = malloc(result_key_size * sizeof(char)); 
    strcpy(key_val, result_col); 


    /* itereate through frame limit */
    for(int i = 0; i < frame->row_limit; i++){

        char *r1_value = r1[i]->value, *err;
        char *r2_value = r2[i]->value;
        double r1_float_value, r2_float_value; 
        r1_float_value = strtod(r1_value, &err);
        r2_float_value = strtod(r2_value, &err);

        /* check if the conversions had an error*/
        if(r1_value == err){
            printf(
                "Cant convert %s column to numeric representation\n",
                (char*)col1
            );
            frame->status = false; 
            exit(0); 
        }

        if(r2_value == err){
            printf(
                "Cant convert %s column to numeric representation\n",
                (char*)col2
            );
            frame->status = false; 
            exit(0); 
        }


        char *convert_result = malloc(20 * sizeof(char)); 
        double add_result = r1_float_value + r2_float_value;
        snprintf(convert_result, sizeof(convert_result), "%.2f", add_result);
        result[i] = init_row_value(i, convert_result);
    } 


    add_table_map(frame->frame, key_val, result);
}


void subtract_frame_cols(frame_t *frame, char *col1, char *col2, char *result_col) {

    /* cast to void pointers */
    void *col1_ptr = (void*)col1; 
    void *col2_ptr = (void*)col2;

    /* look up values and allocate where results are stored */
    row_value_t **r1 = lookup_table_key(frame->frame, col1_ptr); 
    row_value_t **r2 = lookup_table_key(frame->frame, col2_ptr);
    row_value_t **result = malloc(frame->row_limit * sizeof(row_value_t*)); 
    insert_char(frame->headers, result_col);
    frame->header_count += 1;  

    /* allocate space for key size (C didn't catch this but python did ) */
    size_t result_key_size = strlen(result_col)+1; 
    char *key_val = malloc(result_key_size * sizeof(char)); 
    strcpy(key_val, result_col); 

    /* itereate through frame limit */
    for(int i = 0; i < frame->row_limit; i++){

        char *r1_value = r1[i]->value, *err;
        char *r2_value = r2[i]->value;
        double r1_float_value, r2_float_value; 
        r1_float_value = strtod(r1_value, &err);
        r2_float_value = strtod(r2_value, &err);

        /* check if the conversions had an error*/
        if(r1_value == err){
            printf(
                "Cant convert %s column to numeric representation\n",
                (char*)col1
            );
            frame->status = false; 
            exit(0); 
        }

        if(r2_value == err){
            printf(
                "Cant convert %s column to numeric representation\n",
                (char*)col2
            );
            frame->status = false; 
            exit(0); 
        }


        char *convert_result = malloc(20 * sizeof(char)); 
        double add_result = r1_float_value - r2_float_value;
        snprintf(convert_result, sizeof(convert_result), "%.2f", add_result);
        result[i] = init_row_value(i, convert_result);
    } 

    add_table_map(frame->frame, result_col, result);
} 
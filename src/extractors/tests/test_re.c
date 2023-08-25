#include "includes/test_re.h"


void test_match_single() {

    bool equality_status = true; 
    char *expected_results[4] = {
        "shay", "test", "three",
        "\"hello,test,two\""
    }; 

    /* testing for csv pattern */
    char *str = "shay,test,three,\"hello,test,two\"";
    char *csv_pattern = "\"[^\"]*\"|[^,]+";
    tokens_t *results = match_single(str, csv_pattern);  
    for(int i = 0; i < results->result_size; i++){
        char *value = results->tokens[i]; 
        assert(strcmp(value, expected_results[i]) == 0);  
    }

    char *expected_gml_results[2] = {
        "a ", "[b, c]"
    }; 

    /* match GML(graph markup language) pattern */
    char *str_2 = "a ->[b, c]"; 
    char *gml_pattern = "[^->]+"; /* idk what this does */ 
    tokens_t *gml_results = match_single(str_2, gml_pattern); 
    for(int i = 0; i < gml_results->result_size; i++){
        char *value = gml_results->tokens[i]; 
        assert(strcmp(value, expected_gml_results[i]) == 0);  
    }

 	/* validate results */
    if(!equality_status) {
        printf("%s::%s... FAILED\n", __FILE__, __FUNCTION__);
    }
    printf("%s::%s... \e[0;32mPASSED\e[0m\n", __FILE__, __FUNCTION__);


}

void test_match_pattern() {

    /* buffer and pattern */
    char *buffer = "shaydawg,test,three,\"hello,test,two\"";
    char *gml_line = "[0,\"B\"]: ([1,\"A\",0],[2,\"C\",0])";
    char *pattern = "\"[^\"]*\"|[^,]+";
    char *expected_results[4] = {
        "shaydawg", "test", "three",
        "\"hello,test,two\""
    };
    char *expected_neighbors[5] = {"1", "A", "0", "2", "C"};  

    ordered_set_t *values = match_pattern(buffer, pattern);
    assert(values->capacity == 10); 
    assert(values->used == 4);

    for(int i = 0; i < values->used; i++){
        int compare = strcmp(values->items[i]->label, expected_results[i]) == 0; 
        assert(compare == true);  
    }


    ordered_set_t *gml_values = match_pattern(gml_line, RE_GML_NODE);
    int counter = 0;  
    for(int i = 2; i < gml_values->used; i++){
        char *label = gml_values->items[i]->label;
        remove_char(label, '"'); 
        int compare = strcmp(label, expected_neighbors[counter]) == 0; 
        assert(compare == true); 
        counter += 1; 
    }


    printf("%s::%s... \e[0;32mPASSED\e[0m\n", __FILE__, __FUNCTION__); 
}


void test_csv_line() {

    bool equality_status = true; 
    char *expected_results[9] = {
        "4.", "The Shawshank Redemption!", "(1994)", "R", "142 min",
        "Drama", "9.3", "\"2,683,302\"", "$28.34M"
    }; 
    char *line = "4.,The Shawshank Redemption!,(1994),R,142 min,Drama,9.3,\"2,683,302\",$28.34M";
    char *csv_pattern = "\"[^\"]*\"|[^,]+";
    tokens_t *results = match_single(line, csv_pattern);  
    for(int i = 0; i < results->result_size; i++){
        char *value = results->tokens[i];
        int compare = strcmp(value, expected_results[i]) == 0;
        assert(compare == true);  
    }

 	/* validate results */
    if(!equality_status) {
        printf("%s::%s... FAILED\n", __FILE__, __FUNCTION__);
    }
    printf("%s::%s... \e[0;32mPASSED\e[0m\n", __FILE__, __FUNCTION__);
}
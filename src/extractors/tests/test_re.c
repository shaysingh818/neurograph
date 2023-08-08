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
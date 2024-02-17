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

    // /* buffer and pattern */
    char *buffer = "shaydawg,test,three,\"hello,test,two\"";
    char *gml_line = "[0,\"B\"]: ([1,\"A\",0],[2,\"C\",0])";
    char *pattern = "\"[^\"]*\"|[^,]+";
    char *expected_results[4] = {
        "shaydawg", "test", "three",
        "\"hello,test,two\""
    };
    char *expected_neighbors[6] = {"1", "A", "0", "2", "C", "0"};  

    array_t *values = match_pattern_split(buffer, pattern);
    assert(values->item_count == 4);

    for(int i = 0; i < values->item_count; i++){
        int compare = strcmp(values->items[i]->node_type->node->label, expected_results[i]) == 0; 
        assert(compare == true);  
    }

    array_t *gml_values = match_pattern_split(gml_line, RE_GML_NODE);
    int counter = 0;  
    for(int i = 2; i < gml_values->item_count; i++){
        char *label = gml_values->items[i]->node_type->node->label;
        remove_character(label, '"'); 
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

void test_blank_values() {

    char *line = "1,,1,,2,3,53,\"test\"";
    char *line_two = "1,,\"test\",,\"test\",23456,,,"; 
    char *line_three =  "\"TEST,THREE\",,for,1,2,3,\"test\""; 

    /* expected results */
    char *expected_results[8] = {
        "1", "", "1", "", "2", "3", "53", "test"
    }; 

    char *expected_results_two[8] = {
        "1", "", "\"test\"", "", "\"test\"", "23456", "", ","
    }; 

    char *expected_results_three[8] = {
        "\"TEST,THREE\"", "", "for", "1", "2", "3", "\"test\""
    }; 

	array_t *results = match_delimeter_file(line, ",");
	array_t *results_two = match_delimeter_file(line_two, ",");
    array_t *results_three = match_delimeter_file(line_three, ",");

    for(int i = 0; i < results->item_count-1; i++){
        int condition_1 = strcmp(results->items[i]->node_type->node->label, expected_results[i]) == 0;
        int condition_2 = strcmp(results_two->items[i]->node_type->node->label, expected_results_two[i]) == 0; 
        int condition_3 = strcmp(results_three->items[i]->node_type->node->label, expected_results_three[i]) == 0; 
        assert(condition_1 == true); 
        assert(condition_2 == true); 
        assert(condition_3 == true); 

    }

    printf("%s::%s... \e[0;32mPASSED\e[0m\n", __FILE__, __FUNCTION__);
}


void test_match_delimeter_file() {

    char buffer[1024]; 
	FILE* fp = fopen("../../../examples/data/iris.csv", "r");
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
            size_t result_size = strlen(semi_results->items[i]->node_type->node->label);
            bool compare = strcmp(semi_results->items[i]->node_type->node->label, values[i]) == 0;
            assert(result_size == sizes[i]); 
            assert(compare == true); 
        }

		row_count += 1;
	}

    printf("%s::%s... \e[0;32mPASSED\e[0m\n", __FILE__, __FUNCTION__);
}
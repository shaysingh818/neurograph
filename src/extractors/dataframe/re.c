#include "includes/re.h"
#include "../../data_structures/node/includes/node.h"
#include "../../data_structures/list/includes/ll.h"


bool compile_regex(regex_t *regex, char *pattern) {
    int comp_result = regcomp(regex, pattern, REG_EXTENDED);
    if(comp_result != 0){
        char error_buffer[1024];
        regerror(comp_result, regex, error_buffer, sizeof(error_buffer));
        printf("Error compiling regex: %s\n", error_buffer);
        return false;
    }
    return true; 
} 

tokens_t *match_single(char *buffer, char *pattern) {

    int counter = 0;
    regex_t regex;
    regoff_t offset; 
    regmatch_t match;
    node_t *head;


    int comp_result = regcomp(&regex, pattern, REG_EXTENDED);
    if(comp_result != 0){
        char error_buffer[1024];
        regerror(comp_result, &regex, error_buffer, sizeof(error_buffer));
        printf("Error compiling regex: %s\n", error_buffer);
        return NULL;
    }



    int compare = regexec(&regex, buffer, 1, &match, 0);
    while(compare == 0) {

        /* allocate space for token in character array */
        int length = match.rm_eo - match.rm_so; 
        char *token = malloc(length+1 * sizeof(char));

        /* gather results from token string */
        for(int i = match.rm_so, j=0; i < match.rm_eo; i++, j++){
            token[j] = buffer[i]; 
        }
        /* dynamically allocate tokens using linked list */
        token[length] = '\0'; 
        if(counter == 0){ 
            head = create_node(counter, token, 0); 
        } else {
            node_t *item = create_node(counter, token, 0); 
            push_ll(&head, item); 
        }

        buffer += match.rm_eo;
        counter += 1; 

        /* check if regular expression pattern is matched for sub str*/
        compare = regexec(&regex, buffer, 1, &match, 0);
        if(compare == 1){
            break;
        }
    }

    /* error handling */
    if(compare != REG_NOMATCH){
        char error_buf[1024]; 
        regerror(compare, &regex, error_buf, sizeof(error_buf)); 
        printf("Error matching expression: %s\n", error_buf); 
        return NULL; 
    }

    /* allocate results into sized character array */
    int tokens_length = head->id+1; 
    char **tokens = malloc(tokens_length * sizeof(char*)); 

    /* copy results from linked list */
    while(head != NULL) {
        size_t token_length = strlen(head->node_type->node->label); 
        tokens[head->id] = malloc(token_length+1 * sizeof(char)); 
        strcpy(tokens[head->id], head->node_type->node->label);  
        head = head->next; 
    }

    /* return result with array size */
    tokens_t *result = malloc(sizeof(tokens_t)); 
    result->tokens = tokens; 
    result->result_size = tokens_length;
    return result; 

}


void match_tokens_to_pattern(array_t *tokens, char *pattern) {

    regex_t regex;
    regoff_t offset; 
    regmatch_t match;
    char *token; 

    /* check for errors in compilation */
    bool result = compile_regex(&regex, pattern); 
    if(!result){
        exit(0); 
    }

    for(int n = 0; n < tokens->item_count; n++){

        /* iterate through buffer and get tokens */
        int compare = regexec(&regex, tokens->items[n]->node_type->node->label, 1, &match, 0);
        while(compare == 0) {

            /* allocate space for token in character array */
            int length = match.rm_eo - match.rm_so; 
            token = malloc(length+1 * sizeof(char));

            /* gather results from token string */
            for(int i = match.rm_so, j=0; i < match.rm_eo; i++, j++){
                token[j] = tokens->items[n]->node_type->node->label[i];  
            }

            /* add token using array based set */
            token[length] = '\0';
            tokens->items[n]->node_type->node->label += match.rm_eo;

            compare = regexec(&regex, tokens->items[n]->node_type->node->label, 1, &match, 0);
            if(compare == 1){
                break;
            }
        }
        tokens->items[n]->node_type->node->label = token; 
    }

} 


array_t *match_pattern_split(char *buffer, char *pattern) {

    regex_t regex;
    regoff_t offset; 
    regmatch_t match;
    array_t *token_set = init_array(); 
    int token_counter = 0; 

    /* check for errors in compilation */
    bool result = compile_regex(&regex, pattern); 
    if(!result){
        exit(0); 
    }

    /* iterate through buffer and get tokens */
    int compare = regexec(&regex, buffer, 1, &match, 0);
    while(compare == 0) {

        /* allocate space for token in character array */
        int length = match.rm_eo - match.rm_so;
        char *token = malloc(length+1 * sizeof(char));


        /* gather results from token string */
        for(int i = match.rm_so, j=0; i < match.rm_eo; i++, j++){
            token[j] = buffer[i]; 
        }


        /* add token using array based set */
        token[length] = '\0';
        insert(token_set, create_node(token_counter, token, 0));
        buffer += match.rm_eo; 
        token_counter += 1; 

        /* check if regular expression pattern is matched for sub str*/
        compare = regexec(&regex, buffer, 1, &match, 0);
        if(compare == 1){
            break;
        }
    }

    return token_set; 
}


array_t *match_delimeter_file(char *line, char *delimiter) {


	/* format delimiter into regex */
	char *default_pattern = "\"[^\"]*\",|[^,]+|[^,]+,|[,]";
	size_t pattern_size = strlen(default_pattern)+1;
	char *regex_pattern = malloc(pattern_size * sizeof(char)); 

	/* format regex expressions*/
	sprintf(
		regex_pattern, "\"[^\"]*\"%s|[^%s]+|[^%s]+%s|[%s]", 
		delimiter, delimiter, delimiter, delimiter, delimiter
	); 

	/* match pattern with array results */
	array_t *results = match_pattern_split(line, regex_pattern);
    int size = results->item_count;

	/* remove trailing delimiter */
	for(int i = 0; i < results->item_count-1; i++){
		size_t index = strlen(results->items[i]->node_type->node->label); 
		results->items[i]->node_type->node->label[index-1] = '\0';
	}

	/* check for trailing delimiter */
	char *last = results->items[results->item_count-1]->node_type->node->label;
   	char *ret = strchr(last, *delimiter);
	if(ret != NULL){
		int index = results->item_count-1; 
		size_t size = strlen(results->items[index]->node_type->node->label);
		results->items[index]->node_type->node->label[size-1] = '\0';
		insert(results, create_node(results->item_count, "", 0)); 
	}	


	return results; 
} 


void remove_character(char *test_string, char char_to_remove){
    char *d = test_string;
    do {
        while (*d == char_to_remove){
            ++d;
        }
    } while(*test_string++ = *d++);
}
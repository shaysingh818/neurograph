#include "includes/re.h"
#include "../data_structures/includes/node.h"
#include "../data_structures/includes/ll.h"


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
        size_t token_length = strlen(head->label); 
        tokens[head->id] = malloc(token_length+1 * sizeof(char)); 
        strcpy(tokens[head->id], head->label);  
        head = head->next; 
    }

    /* return result with array size */
    tokens_t *result = malloc(sizeof(tokens_t)); 
    result->tokens = tokens; 
    result->result_size = tokens_length;
    return result; 

}


array_t *match_pattern(char *buffer, char *pattern) {

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


void remove_char(char *test_string, char char_to_remove){
    char *d = test_string;
    do {
        while (*d == char_to_remove){
            ++d;
        }
    } while(*test_string++ = *d++);
}

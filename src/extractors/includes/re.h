#ifndef RE_H
#define RE_H

#include <stdio.h>
#include <unistd.h>
#include <stdbool.h>
#include <string.h> 
#include <stdlib.h>
#include <regex.h>

/* data structures import */
#include "../../data_structures/includes/array.h"

struct Tokens {
    char **tokens; 
    int result_size; 
};

typedef struct Tokens tokens_t; 

/* compile regex expression */
bool compile_regex(regex_t *regex, char *pattern); 

/* match expression */
tokens_t *match_single(char *buffer, char *pattern);

/* using set instead */
array_t *match_pattern(char *buffer, char *pattern); 

/* replace sub string with pattern */ 
void remove_char(char *test_string, char char_to_remove);


#endif
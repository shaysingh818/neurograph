#ifndef RE_H
#define RE_H

#include <stdio.h>
#include <unistd.h>
#include <stdbool.h>
#include <string.h> 
#include <stdlib.h>
#include <regex.h>

/* data structures import */
#include "../../data_structures/includes/set.h"

struct Tokens {
    char **tokens; 
    int result_size; 
};

typedef struct Tokens tokens_t; 

tokens_t *match_single(char *buffer, char *pattern);

/* using set instead */
ordered_set_t *match_pattern(char *buffer, char *pattern); 

/* replace sub string with pattern */ 
void remove_char(char *test_string, char char_to_remove);


#endif
#ifndef RE_H
#define RE_H

#include <stdio.h>
#include <unistd.h>
#include <stdbool.h>
#include <string.h> 
#include <stdlib.h>
#include <regex.h>

/* data structures import */
#include <data_structures/list/includes/array.h>

/*******************************************************
    common regular expression macros defined here 
*******************************************************/

/* file formats */
#define CSV "\"[^\"]*\"|[^,]+|[^,]+,|[,]"
#define JSON "None Yet"
#define YAML "Yaml"
#define GML "\"[a-zA-Z]+\":|\"[a-zA-Z]+\""
#define RE_NODE "\"[^\"]*\"|[^:]+"
#define RE_GML "\"[a-zA-Z]+\":|\"[a-zA-Z]+\""
#define REMOVE_QUOTES "[a-zA-Z]+"
#define GET_QUOTES "(['\"])"
#define RE_GML_NODE "[0-9]+|\"[^\"]*\""

/* dates */
#define YYYYMMDD "[0-9]{4}-[0-9]{2}-[0-9]{2}"
#define YYYYMMDDHH "[0-9]{4}-[0-9]{2}-[0-9]{2}-[0-9]{2}"
#define YYYYMMDDHHSS "[0-9]{4}-[0-9]{2}-[0-9]{2}-[0-9]{2}-[0-9]{2}"
#define MONTHDDYYY "[a-zA-z]+ [0-9]{2}, [0-9]{4}"

struct Tokens {
    char **tokens; 
    int result_size; 
};

typedef struct Tokens tokens_t; 

/* compile regex expression */
bool compile_regex(regex_t *regex, char *pattern); 

/* match expression against single char */
void match_tokens_to_pattern(array_t *tokens, char *pattern); 

/* match expression */
tokens_t *match_single(char *buffer, char *pattern);

/* using set instead */
array_t *match_pattern_split(char *buffer, char *pattern);

/* match pattern for delimiter files */
array_t *match_delimeter_file(char *line, char *delimiter); 

/* replace sub string with pattern */ 
void remove_character(char *test_string, char char_to_remove);

#endif
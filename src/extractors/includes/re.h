#ifndef RE_H
#define RE_H

#include <stdio.h>
#include <unistd.h>
#include <stdbool.h>
#include <string.h> 
#include <stdlib.h>
#include <regex.h> 

struct Tokens {
    char **tokens; 
    int result_size; 
};

typedef struct Tokens tokens_t; 

tokens_t *match_single(char *buffer, char *pattern); 
tokens_t *match_multi_single(char **buffers, char *pattern); 
tokens_t *match_multi(char **buffers, char **patterns); 
tokens_t *match_file(char *file_path, char *pattern); 

#endif
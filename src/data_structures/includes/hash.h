#ifndef HASH_H
#define HASH_H

#include <stdlib.h>
#include <string.h> 
#include <stdio.h>
#include <unistd.h>
#include <stdbool.h>
#include "node.h" 

/* not sure what these do yet */
typedef void (*destructor_func)(void*); 
typedef bool (*compare_func)(void*, void*);
typedef int (*hash_func)(int, char*, size_t); 

int additive_hash(int state, char *input, size_t len); 
int jenkins_hash(int state, char *input, size_t len); 

/* comparison functions */
bool compare_char(void *key1, void *key2);
void free_char(void *value);
char *str(char *key_value); 

/* probing function */
int probe(int k, int i, int m);

#endif
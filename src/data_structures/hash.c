#include "includes/hash.h"


int additive_hash(int state, char *input, size_t len) {
	int hash = state; 
	for(int i = 0; i < len; i++){
		hash += input[i];
	}
	return hash;
} 

bool compare_char(void *key1, void *key2) {

	char *key1_ptr = (char*)key1; 
	char *key2_ptr = (char*)key2; 

	if(strcmp(key1_ptr, key2_ptr) == 0){
		return true; 
	}
	return false; 
}

char *str(char *key_value) {
	size_t key_value_size = strlen(key_value) + 1; 
	char *key = malloc(key_value_size * sizeof(char)); 
	strcpy(key, key_value); 
	return key; 
}

void free_char(void *value) {
	if(value != NULL){
		free(value); 
	} 
}

int probe(int k, int i, int m){
    int h1 = k; 
    int h2 = (k << 1) | 1; 
    return (h1 + i*h2) & (m-1); 
}
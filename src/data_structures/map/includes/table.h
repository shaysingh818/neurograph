#ifndef TABLE_H
#define TABLE_H

#include <stdlib.h>
#include <string.h> 
#include <stdio.h>
#include <unistd.h>
#include <stdbool.h>
#include "hash.h"


/* open addressing for creating a hash set */
struct Bin {
	bool is_free;
    bool is_deleted;  
	int hash_key;
	void *key;  
	void *value; 
}; 

typedef struct Bin bin_t; 


struct BinTable {
	bin_t *table; 
	int size;
	int used; 
	int active;
	double load_factor;  
	compare_func key_cmp; 
	destructor_func key_destructor; 
	destructor_func val_destructor; 
	hash_func hash_function; 
};

typedef struct BinTable hash_table_t; 


/* open addressing methods */
hash_table_t *hash_table(
	int size, 
	double load_factor,
	compare_func key_cmp, 
	destructor_func key_destructor,
	destructor_func val_destructor,
	hash_func hash_function
); 

void delete_hash_table(hash_table_t *table);
void add_table_map(hash_table_t *table, void *key, void *value); 
void delete_table_key(hash_table_t *table, void *key); 
void *lookup_table_key(hash_table_t *table, void *key); 
void table_resize(hash_table_t *table, int new_size); 

/* probing functions */
int probe(int k, int i, int m);
void print_table(hash_table_t *table); 



#endif
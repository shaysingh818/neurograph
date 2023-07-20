#ifndef MAP_H
#define MAP_H

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


struct hash_linked_list {
	int hash_key;
	void *key;
	void *value;  
	struct hash_linked_list *next; 
}; 

typedef struct hash_linked_list h_ll_t; 


struct HashTable {
	h_ll_t **table;  
	int size, used, active; 
	compare_func key_cmp; 
	destructor_func key_destructor;
	destructor_func val_destructor;  
	hash_func hash_function; 
}; 

typedef struct HashTable map_t;


/* hash table util methods */ 
map_t *init_table(
	int size, 
	compare_func key_cmp, 
	destructor_func key_destructor, 
	destructor_func val_destructor,
	hash_func hash_function
);


/* hash map methods */ 
void delete_table(map_t *table); 
void *lookup_key(map_t *table, void *key); 
void insert_key(map_t *table, void* key); 
void delete_key(map_t *table, void* key);
void add_map(map_t *table, void *key, void *value); 
void resize(map_t *table, int new_size);  
bool contains_key(map_t *table, void* key); 


/* linked list hash table methods */
h_ll_t *new_hash_ll();
h_ll_t *get_prev_link(h_ll_t *list, int hash_key, void *key, compare_func key_cmp);
h_ll_t *lookup_key_list(h_ll_t *list, int hash_key, void *key, compare_func key_cmp);  
bool contains_key_list(h_ll_t *list, int hash_key, void *key, compare_func key_cmp); 
bool delete_key_list(h_ll_t *list, int hash_key, void *key, compare_func key_cmp, destructor_func key_destructor, destructor_func val_destructor); 
void add_map_list(h_ll_t *list, int hash_key, void *key, void *value);
void insert_key_list(h_ll_t *list, int hash_key, void *key, compare_func key_cmp); 
void delete_hash_ll(h_ll_t *list, destructor_func key_destructor, destructor_func val_destructor, bool free_resources);


/* hashing functions for bytes */
int additive_hash(int state, char *input, size_t len); 
int jenkins_hash(int state, char *input, size_t len); 

/* comparison functions */
bool compare_char(void *key1, void *key2); 


/* open addressing for creating a hash set */
struct Bin {
	bool is_free: true;
	bool is_deleted: true;
	int hash_key; 
	void *key; 
	void *value; 
}; 

typedef struct Bin bin_t; 


struct BinTable {
	bin_t *table; 
	int size, used, active; 
	compare_func key_cmp; 
	destructor_func key_destructor; 
	destructor_func val_destructor;
	hash_func hash_function; 
};

typedef struct BinTable hash_set_t; 


/* open addressing methods */
hash_set_t *empty_bin_table(int size, compare_func key_cmp, destructor_func key_destructor, destructor_func val_destructor); 
void delete_bin_table(hash_set_t *table); 
void add_bin_map(hash_set_t *table, void *key, void *value); 
void resize_bin_table(hash_set_t *table, int new_size);
void insert_bin_key(hash_set_t *table, int hash_key, void *key); 
bool contains_bin_key(hash_set_t *table, int hash_key, void *key);
void delete_bin_key(hash_set_t *table, int hash_key, void *key);
void *lookup_bin_key(hash_set_t *table, int hash_key, void *key); 
void print_bin_table(hash_set_t *table); 
int p(int k, int i, int m);



#endif
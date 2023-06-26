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

#endif
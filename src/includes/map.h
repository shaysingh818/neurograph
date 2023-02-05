#ifndef MAP_H
#define MAP_H

#include <stdlib.h>
#include <string.h> 
#include <stdio.h>
#include <unistd.h>
#include <stdbool.h> 

/* 
 * This library is meant to handle unique character values with associated indexes
 * Ideally a Hashing Data structure would be useful to solve this
 * Temporarily, we'll create a "hacky" version of a set list. 
 * Instead of falling down a rabbit, pick this back up in later versions
 */


struct UniqueLinkedList {
	char *value; 
	int index; 
	struct UniqueLinkedList *next; 
}; 

typedef struct UniqueLinkedList u_ll_t; 


struct MapList {
	int key; 
	struct MapList *next; 
}; 

typedef struct MapList ll_t; 


struct Bin {
	int is_free; 
	int key;
}; 

typedef struct Bin bin_t; 


struct HashTable {
	bin_t *table;  
	int size;
}; 

typedef struct HashTable map_t; 


/* unique linked list  methods */
u_ll_t *create_ull(char *set_key); 
int append(u_ll_t **head, char *set_key);
int pop_node(u_ll_t *head); 
int contains_value(u_ll_t *head, char *key); 

void print_u_ll_t(u_ll_t *head); 

/* hash table util methods */ 
map_t *init(int size); 
void delete_table(map_t *table); 

/* key methods */ 
void insert_key(map_t *table, int key); 
bool contains_key(map_t *table, int key); 
void delete_key(map_t *table, int key); 

#endif


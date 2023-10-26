#include "includes/map.h"


map_t *init_table(
	int size, 
	compare_func key_cmp, 
	destructor_func key_destructor, 
	destructor_func val_destructor, 
	hash_func hash_function) {

	map_t *table = (map_t*)malloc(sizeof(map_t));
	table->table = malloc(size * sizeof(h_ll_t*));  
	for(int i = 0; i < size; i++){
		table->table[i] = new_hash_ll();
	}
	table->size = size;
	table->used = 0; 
	table->key_cmp = key_cmp;
	table->key_destructor = key_destructor;   
	table->val_destructor = val_destructor;
	table->hash_function = hash_function;   
	return table; 
}

void delete_table(map_t *table) {
	for(int i = 0; i < table->size; i++){
		delete_hash_ll(
			table->table[i], 
			table->key_destructor,
			table->val_destructor, 
			true
		);
	}
	free(table->table); 
	free(table); 
}


void *lookup_key(map_t *table, void *key){
	int mask = table->size - 1; 
	int hash_key = table->hash_function(0, (char*)key, strlen(key)+1); 
	int index = hash_key & mask;
	h_ll_t *list = table->table[index]; 
	h_ll_t *link = lookup_key_list(list, hash_key, key, table->key_cmp);
	if(link == 0){
		printf("Key does not exist: %s\n", (char*)key); 
		exit(1); 
	}
	return link ? link->value : 0; 
}


void insert_key(map_t *table, void *key) {

	int mask = table->size - 1;
	int hash_key = table->hash_function(0, (char*)key, strlen(key)+1); 
	int index = hash_key & mask; 

	if(contains_key_list(table->table[index], hash_key, key, table->key_cmp)) {
		delete_key_list(
			table->table[index], 
			hash_key, key, 
			table->key_cmp, table->key_destructor, table->val_destructor
		);
		insert_key_list(table->table[index], hash_key, key, table->key_cmp); 
	} else {
		insert_key_list(table->table[index], hash_key, key, table->key_cmp); 
		table->used++; 
	}	

	if(table->used > table->size / 2){
		resize(table, table->size * 2); 
	}
}


bool contains_key(map_t *table, void *key) {
	int mask = table->size - 1;
	int hash_key = table->hash_function(0, (char*)key, strlen(key)+1); 
	int index = hash_key & mask;
	return contains_key_list(table->table[index], hash_key, key, table->key_cmp); 
}



void add_map(map_t *table, void *key, void *value) {

	int mask = table->size - 1; 
	int hash_key = table->hash_function(0, (char*)key, strlen(key)+1); 
	int index = hash_key & mask;
	h_ll_t *list = table->table[index]; 
	h_ll_t *link = lookup_key_list(list, hash_key, key, table->key_cmp);  


	if(link != 0) {
		/* if key exists in table, replace value */
		if(table->key_destructor){
			table->key_destructor(link->key); 
		}

		if(table->val_destructor){
			table->val_destructor(link->value); 			
		}
		link->key = key; 
		link->value = value; 
	} else {
		add_map_list(list, hash_key, key, value); 
		table->used++; 
	}

} 


void delete_key(map_t *table, void *key) {

	int mask = table->size - 1; 
	int hash_key = table->hash_function(0, (char*)key, strlen(key)+1); 
	int index = hash_key & mask;

	h_ll_t *list = table->table[index]; 
	bool deleted = delete_key_list(
		list, 
		hash_key, key, table->key_cmp,
		table->key_destructor, table->val_destructor
	);

	if(deleted) table->used--; 

	if(table->used < table->size / 8){
		resize(table, table->size / 2); 
	}
}


void resize(map_t *table, int new_size) {

	int old_size = table->size; 
	h_ll_t **old_bins = table->table; 
	table->table = malloc(new_size * sizeof(h_ll_t*)); 
	
	/* create new table */
	for(int i = 0; i < new_size; i++){
		table->table[i] = new_hash_ll(); 
	}
	table->size = new_size; 
	table->used = 0; 

	/* copy maps */
	for(int i = 0; i < old_size; i++){
		h_ll_t *list = old_bins[i]; 
		while(list = list->next){
			add_map(table, list->key, list->value); 
		}
	}

	/* delete old table */
	for(int i = 0; i < old_size; i++){
		delete_hash_ll(
			old_bins[i], 
			table->key_destructor,
			table->val_destructor, 
			false
		); 
	}
	free(old_bins); 
}  


h_ll_t *new_hash_ll() {
	h_ll_t *sentinel = malloc(sizeof(h_ll_t));
	sentinel->hash_key = 0; 
	sentinel->key = 0; 
	sentinel->next = 0; 
	return sentinel; 
}


h_ll_t *get_prev_link(h_ll_t *list, int hash_key, void *key, compare_func cmp) {
	while(list->next){
		if(list->next->hash_key == hash_key && cmp(list->next->key, key)){
			return list;
		}
		list = list->next; 
	}
	return 0; 
} 


h_ll_t *lookup_key_list(h_ll_t *list, int hash_key, void *key, compare_func key_cmp) {
	h_ll_t *link = get_prev_link(list, hash_key, key, key_cmp); 
	return link ? link->next : 0; 
}  


bool contains_key_list(h_ll_t *list, int hash_key, void *key, compare_func cmp) {
	return get_prev_link(list, hash_key, key, cmp) != 0; 
} 

void add_map_list(h_ll_t *list, int hash_key, void *key, void *value) {
	h_ll_t *link = malloc(sizeof(h_ll_t));
	link->hash_key = hash_key; 
	link->key = key; 
	link->value = value; 
	link->next = list->next; 
	list->next = link; 	 
} 

void insert_key_list(h_ll_t *list, int hash_key, void *key, compare_func cmp) {
	h_ll_t *link = malloc(sizeof(h_ll_t)); 
	link->hash_key = hash_key;
	link->key = key;  
	link->next = list->next;
	list->next = link;  
}


bool delete_key_list(
	h_ll_t *list, int hash_key, void *key, 
	compare_func cmp, destructor_func destructor, destructor_func destructor_value) {

	h_ll_t *link = get_prev_link(list, hash_key, key, cmp); 
	if(!link) return false; 

	h_ll_t *to_delete = link->next; 
	link->next = to_delete->next; 
	if(destructor) destructor(to_delete->key);
	if(destructor_value) destructor_value(to_delete->value);  
	free(to_delete);
	return true; 
}  


void delete_hash_ll(
	h_ll_t *list, 
	destructor_func destructor, destructor_func destructor_val, 
	bool free_resources){

	while(list != 0){
		h_ll_t *next = list->next; 
		if(free_resources && destructor && list->key){
			destructor_val(list->value); 
		}
		free(list); 
		list = next; 
	}
}


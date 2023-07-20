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


hash_set_t *empty_bin_table(int size, compare_func cmp, destructor_func key_destructor, destructor_func val_destructor) {
	hash_set_t *table = malloc(sizeof(hash_set_t));
	table->table = malloc(size * sizeof(bin_t)); 
	bin_t *end = table->table + size; 
	for(bin_t *bin = table->table; bin != end; ++bin) {
		bin->is_free = true; 
		bin->is_deleted = false; 
	}
	table->size = size; 
	table->active = table->used = 0; 
	table->key_cmp = cmp; 
	table->key_destructor = key_destructor;
	table->val_destructor = val_destructor; 
	return table; 
} 


void delete_bin_table(hash_set_t *table) {
	if(table->val_destructor){
		bin_t *end = table->table + table->size; 
		for(bin_t *bin = table->table; bin != end; ++bin) {
			if(bin->is_free || bin->is_deleted) continue;
			if(table->key_destructor) table->key_destructor(bin->key);
			if(table->val_destructor) table->val_destructor(bin->value); 
		}
	}
	free(table->table);
	free(table); 
} 


void add_bin_map(hash_set_t *table, void *key, void *value) {

	int index; 
	int hash_key = table->hash_function(0, (char*)key, strlen(key)+1); 
	bool contains = (bool)lookup_bin_key(table, hash_key, key);
	for(int i = 0; i < table->size; i++){
		index = p(hash_key, i, table->size); 
		bin_t *bin = &table->table[index]; 

		if(bin->is_free){
			bin->is_free = bin->is_deleted = false; 
			bin->hash_key = hash_key; 
			bin->key = key; 
			bin->value = value; 
			table->active++; table->used++; 
			break; 
		}

		if(bin->is_deleted && !contains) {
			bin->is_free = bin->is_deleted = false; 
			bin->hash_key = hash_key; 
			bin->key = key; 
			bin->value = value; 
			table->active++;
			break; 
		}

		if(bin->hash_key == hash_key) {
			if(table->key_cmp(bin->key, key)) {
				delete_bin_key(table, hash_key, key); 
				add_bin_map(table, key, value); 
				return; 
			}
		} else {
			continue; 
		}
	}

	if(table->used > table->size / 2){
		resize_bin_table(table, table->size * 2); 
	}

} 


void resize_bin_table(hash_set_t *table, int new_size) {
	bin_t *old_bins = table->table; 
	int old_size = table->size; 

	/* update table so it has new bins */
	table->table = malloc(new_size * sizeof(bin_t));
	bin_t *end = table->table + new_size; 

	for(bin_t *bin = table->table; bin != end; ++bin) {
		bin->is_free = true; 
		bin->is_deleted = false; 
	}
	table->size = new_size; 
	table->active = table->used = 0; 

	end = old_bins + old_size;
	for(bin_t *bin = old_bins; bin != end; ++bin) {
		if(bin->is_free || bin->is_deleted) continue;
		insert_bin_key(table, bin->hash_key, bin->key); 		
	}

	free(old_bins);
}


void insert_bin_key(hash_set_t *table, int hash_key, void *key) {

	int index; 
	bool contains = contains_bin_key(table, hash_key, key); 
	for(int i = 0; i < table->size; i++){
		index = p(hash_key, i, table->size); 
		bin_t *bin = &table->table[index]; 

		if(bin->is_free) {
			bin->hash_key = hash_key; bin->key = key; 
			bin->is_free = bin->is_deleted = false; 

			table->active++; table->used++; 
			break; 
		}

		if(bin->is_deleted && !contains){
			bin->hash_key = hash_key; bin->key = key; 
			bin->is_free = bin->is_deleted = false; 
			table->active++;
			break; 
		}

		if(bin->hash_key == hash_key){
			if(table->key_cmp(bin->key, key)){
				delete_bin_key(table, hash_key, key);
				insert_bin_key(table, hash_key, key); 
				return; 
			}
		} else {
			continue; 
		}
	}

	if(table->used > table->size / 2){
		resize_bin_table(table, table->size * 2); 
	}
} 


bool contains_bin_key(hash_set_t *table, int hash_key, void *key) {

	for(int i = 0; i < table->size; i++){
		int index = p(hash_key, i, table->size);
		bin_t *bin = &table->table[index]; 

		if(bin->is_free){
			return false; 
		}

		if(!bin->is_deleted && bin->hash_key == hash_key &&
		table->key_cmp(bin->key, key)){
			return true; 
		}
	}
	return false; 
}


void delete_bin_key(hash_set_t *table, int hash_key, void *key) {

	for(int i = 0; i < table->size; i++){

		int index = p(hash_key, i, table->size);
		bin_t *bin = &table->table[index]; 

		if(bin->is_free) return; 
		
		if(!bin->is_deleted && bin->hash_key == hash_key && table->key_cmp(bin->key, key)){
			bin->is_deleted = true; 

			if(table->key_destructor){
				table->key_destructor(table->table[index].key);
				table->active--;
				if(table->key_destructor) table->key_destructor(bin->key);
				if(table->val_destructor) table->val_destructor(bin->value); 
				break;
			}
		}
	}

	if(table->active < table->size / 8){
		resize_bin_table(table, table->size / 2); 
	}
}

void *lookup_bin_key(hash_set_t *table, int hash_key, void *key) {
	
	for(int i = 0; i < table->size; i++){

		int index = p(hash_key, i, table->size);
		bin_t *bin = &table->table[index]; 

		if(bin->is_free) return 0;

		if(!bin->is_deleted && bin->hash_key == hash_key && table->key_cmp(bin->key, key)){
			return bin->value; 
		}			
	}

	return 0; 
}

int p(int k, int i, int m) {
	return (k+i) & (m-1);	
} 


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
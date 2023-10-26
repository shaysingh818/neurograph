#include "includes/table.h"


hash_table_t *hash_table(
    int size, 
    double load_factor,
    compare_func key_cmp, 
    destructor_func key_destructor, 
    destructor_func val_destructor,
	hash_func hash_function) {

	hash_table_t *table = malloc(sizeof(hash_table_t)); 
	table->table = malloc(size * sizeof(bin_t)); 
    bin_t *end = table->table + size; 
	for(bin_t *bin = table->table; bin != end; bin++){
		bin->is_free = true;
        bin->is_deleted = false;  
	}
	table->size = size; 
    table->active = table->used = 0; 
    table->load_factor = load_factor; 
    table->key_cmp = key_cmp; 
    table->key_destructor = key_destructor; 
    table->val_destructor = val_destructor; 
    table->hash_function = hash_function; 
	return table; 
}


void delete_hash_table(hash_table_t *table){

    if(table->key_destructor || table->val_destructor) {
        bin_t *end = table->table + table->size; 
        for(bin_t *bin = table->table; bin != end; bin++){
            if(bin->is_free || bin->is_deleted) continue; 
            if(table->key_destructor) table->key_destructor(bin->key); 
            if(table->val_destructor) table->val_destructor(bin->value); 
        }
    }

	free(table->table); 
	free(table); 
}


void add_table_map(hash_table_t *table, void *key, void *value) {

    int index; 
    bool contains = (bool)lookup_table_key(table, key);  
	int hash_key = table->hash_function(0, (char*)key, strlen(key)+1);

    for(int i = 0; i < table->size; i++){
        index = probe(hash_key, i, table->size);
        bin_t *bin = &table->table[index];

        if(bin->is_free) {
            bin->hash_key = hash_key;  
            bin->key = key;
            bin->value = value; 
            bin->is_free = bin->is_deleted = false;
            table->active++; table->used++; 
            break;  
        }

        if(bin->is_deleted && !contains){
            bin->hash_key = hash_key;
            bin->key = key;
            bin->value = value; 
            bin->is_free = bin->is_deleted = false; 
            table->active++; 
            break; 
        }

        if(bin->hash_key == hash_key){
            if(table->key_cmp(bin->key, key)){
                delete_table_key(table, key); 
                add_table_map(table, key, value); 
                return; 
            } else {
                continue; 
            }
        }
    }  


    if(table->used > table->size / 2){
        table_resize(table, table->size * 2); 
    }
}


void delete_table_key(hash_table_t *table, void *key) {

	int hash_key = table->hash_function(0, (char*)key, strlen(key)+1); 
    for(int i = 0; i < table->size; i++){
        int index = probe(hash_key, i, table->size); 
        bin_t *bin = &table->table[index]; 
        if(bin->is_free) return; 

        if(!bin->is_deleted && 
            bin->hash_key == hash_key &&
            table->key_cmp(bin->key, key)) { 
            bin->is_deleted = true;
            if(table->key_destructor) table->key_destructor(bin->key);
            if(table->val_destructor) table->val_destructor(bin->value); 
            table->active--;
            return; 
        }

    }   

    if(table->active < table->size / 8){
        table_resize(table, table->size / 2); 
    }
} 

void *lookup_table_key(hash_table_t *table, void *key) {

	int hash_key = table->hash_function(0, (char*)key, strlen(key)+1);
    for(int i = 0; i < table->size; i++){
        int index = probe(hash_key, i, table->size);
        bin_t *bin = &table->table[index];
        if(bin->is_free){
            return 0; 
        }

        if(
            !bin->is_deleted && 
            bin->hash_key == hash_key && 
            table->key_cmp(bin->key, key)){

            return bin->value; 
        }
    } 
    return 0; 
}


void table_resize(hash_table_t *table, int new_size) {

    bin_t *old_bins = table->table; 
    int old_size = table->size; 
    table->table = malloc(new_size * sizeof(bin_t)); 
    bin_t *end = table->table + new_size; 
    for(bin_t *bin = table->table; bin != end; bin++){
        bin->is_free = true; 
        bin->is_deleted = false; 
    }
    table->size = new_size; 
    table->active = table->used = 0; 

    end = old_bins + old_size; 
    for(bin_t *bin = old_bins; bin != end; bin++){
        if(bin->is_free || bin->is_deleted) continue; 
        add_table_map(table, bin->key, bin->value); 
    }

    free(old_bins); 
}

void print_table(hash_table_t *table){
    int index = 0; 
    bin_t *end = table->table + table->size; 
    for(bin_t *bin = table->table; bin != end; bin++){
        printf("Index: %d, Key: %s\n", index, (char*)bin->key); 
        index += 1; 
    }
}
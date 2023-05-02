#include "includes/map.h"


u_ll_t *create_ull(char *set_key) {

	size_t key_size = strlen(set_key) + 1; 

	u_ll_t *new_node = (u_ll_t*)malloc(sizeof(u_ll_t));
	new_node->value = (char*)malloc(key_size * sizeof(char)); 
	strcpy(new_node->value, set_key);
	new_node->index = 0;
   	new_node->next = NULL;
	return new_node; 
}


int append(u_ll_t **head, char *set_key) {

	size_t key_size = strlen(set_key) + 1; 
	
	u_ll_t *last = *head;
	u_ll_t *new_node = (u_ll_t*)malloc(sizeof(u_ll_t)); 
	new_node->value = (char*)malloc(key_size * sizeof(char)); 
	strcpy(new_node->value, set_key);
   	new_node->next = NULL;

	/* traverse till last node (This method will scale terribly) */
   	int counter = 0; 	
	while(last->next != NULL) {

		/* check if existing key is in list */ 
		int condition = strcmp(last->value, set_key) == 0; 
		if(condition) {
			return false; 
		}

		last = last->next; 
		counter += 1; 
	}

	/* adjust indices */ 
	new_node->index = counter + 1; 
	last->index = counter; 
	last->next = new_node;	

	if(*head == NULL) {
		*head = new_node; 
		return true; 
	}

	return true; 
}


int get_id(u_ll_t *head, char *key) {
	while(head != NULL) {
		int condition = strcmp(head->value, key) == 0; 
		if(condition) {
			return head->index; 
		}
		head = head->next; 
	}
	return false; 
}


void print_u_ll_t(u_ll_t *head) {
	while(head != NULL) {
		printf("[%d] -> %s\n", head->index, head->value); 
		head = head->next; 
	}
}


map_t *init(int size) {
	map_t *table = (map_t*)malloc(sizeof(map_t)); 
	table->table = (bin_t*)malloc(size * sizeof(bin_t));
   	for(int i = 0; i < size; i++) {
		bin_t *bin = &table->table[i]; 
		bin->is_free = true; 
	}	
	table->size = size; 
	return table; 
}


void delete_table(map_t *table) {
	free(table->table); 
	free(table); 
}


void insert_key(map_t *table, int key) {

	int index = key % table->size; 
	bin_t *b = &table->table[index]; 
	if(b->is_free) {
		b->key = key; 
		b->is_free = false; 
	} else {
		// Handle this later (collision)
	}
}


bool contains_key(map_t *table, int key) {

	int index = key % table->size; 
	bin_t *b = &table->table[index]; 
	if(!b->is_free && b->key == key) {
		return true;
	}
	return false; 	

}


void delete_key(map_t *table, int key) {

	int index = key % table->size; 
	bin_t *b = &table->table[index]; 
	if(b->key == key) {
		b->is_free = true; 
	}
}
#include "includes/test_map.h"


void test_hash_table() {

	/* create instance of hash table */
	bool equality_status = true; 
	int initial_size = 2;

	// create table
	map_t *hash_table = init_table(
		initial_size, compare_char, 
		NULL, NULL,
		additive_hash
	);

	add_map(hash_table, "testing", "my_value"); 
	add_map(hash_table, "testing2", "my_value2"); 
	add_map(hash_table, "testing3", "my_value3");

	/* lookup key value pair */
	void *results = lookup_key(hash_table, "testing2"); 
	char *value = (char*)results; 

	if(strcmp(value, "my_value2") != 0) {
		equality_status = false; 
	}


	if(hash_table->size != 2 && hash_table->used != 3){
		equality_status = false;
	}

	/* test using a char key with struct as value */
	map_t *struct_table = init_table(
		initial_size, 
		compare_char, 
		NULL, NULL,
		additive_hash
	);

	/* create dummy node values */
	node_t *n = create_node(1, "testing1", 0); 
	node_t *n1 = create_node(2, "testing2", 1); 
	node_t *n2 = create_node(3, "testing3", 0); 
	node_t *n3 = create_node(4, "testing4", 2);

	add_map(struct_table, "node_0", n); 
	add_map(struct_table, "node_1", n1); 
	add_map(struct_table, "node_2", n2); 
	add_map(struct_table, "node_3", n3);

	/* keys */
	char *keys[10] = {"node_0", "node_1", "node_2", "node_3"}; 
	char *expected_values[10] = {"testing1", "testing2", "testing3", "testing4"};
	int ids[4] = {1,2,3,4}; 
	int weights[4] = {0,1,0,2};


	/* iterate through key results */
	for(int i = 0; i < 4; i++){

		void *results = lookup_key(struct_table, keys[i]);
		node_t *value = (node_t*)results; 
		bool id_condition = value->id == ids[i]; 
		bool weight_condition = value->weight == weights[i]; 
		bool label_condition = strcmp(expected_values[i], value->label) == 0;  

		if(!id_condition || !weight_condition || !label_condition) {
			equality_status = false; 
		}
	}
	
    if(!equality_status) {
        printf("%s::%s... FAILED\n", __FILE__, __FUNCTION__);
    } else {
        printf("%s::%s... \e[0;32mPASSED\e[0m\n", __FILE__, __FUNCTION__);
    } 


}


void test_additive_hash() {

	bool equality_status = true; 

	char *key = "testing"; 
	int index = additive_hash(0, key, strlen(key)+1);

	char *key1 = "Testing";
	int index2 = additive_hash(0, key1, strlen(key)+1); 

	if(index != 766 && index2 != 734){
		equality_status = false; 
	}

    if(!equality_status) {
        printf("%s::%s... FAILED\n", __FILE__, __FUNCTION__);
    } else {
        printf("%s::%s... \e[0;32mPASSED\e[0m\n", __FILE__, __FUNCTION__);
    } 

}


void test_compare_char() {

	bool equality_status = true; 

	bool result = compare_char("test", "test");
	if(!result) equality_status = false; 

	bool result1 = compare_char("test1", "test");
	if(result1) equality_status = false; 

	bool result2 = compare_char("test1", "test1"); 
	if(result2 != true) equality_status = false; 

	bool result3 = compare_char("test2", "test");
	if(result3 != false) equality_status = false; 

	bool result4 = compare_char("test2", "test2"); 
	if(!result4) equality_status = false;

    if(!equality_status) {
        printf("%s::%s... FAILED\n", __FILE__, __FUNCTION__);
    } else {
        printf("%s::%s... \e[0;32mPASSED\e[0m\n", __FILE__, __FUNCTION__);
    } 

}


void test_hash_linked_list() {

	/* this test case is to understand how the LL stores keys*/
	bool equality_status = true; 

	h_ll_t *ll = new_hash_ll();
	add_map_list(ll, 1, "key1", "value1");
	add_map_list(ll, 2, "key2", "value2");
	add_map_list(ll, 3, "key3", "value3");
	add_map_list(ll, 4, "key4", "value4");
	add_map_list(ll, 5, "key5", "value5");
	add_map_list(ll, 6, "key6", "value6");

	h_ll_t *prev = get_prev_link(ll, 1, "key1", compare_char); 
	if(strcmp("key2", (char*)prev->key) != 0){
		equality_status = false; 
	}

	h_ll_t *key = lookup_key_list(ll, 1, "key1", compare_char);
	if(strcmp("key1", (char*)key->key) != 0){
		equality_status = false; 
	}

	char *expected_keys[10] = {NULL, "key4", "key3", "key2"};

	/* delete 2 keys and compare results */
	delete_key_list(ll, 5, "key5", compare_char, NULL, NULL); 
	delete_key_list(ll, 6, "key6", compare_char, NULL, NULL); 

	int counter = 0; 
	while(ll->next){
		if(counter > 0){ /* skipping the null value */
			if(strcmp((char*)ll->key, expected_keys[counter]) != 0){
				equality_status = false; 
			}
		}
		ll = ll->next; 
		counter += 1; 
	} 

    if(!equality_status) {
        printf("%s::%s... FAILED\n", __FILE__, __FUNCTION__);
    } else {
        printf("%s::%s... \e[0;32mPASSED\e[0m\n", __FILE__, __FUNCTION__);
    } 
}


void test_duplicates() {

	bool equality_status = true; 
	int initial_size = 1;

	/* create table */
	map_t *hash_table = init_table(
		initial_size, compare_char, 
		NULL, NULL,
		additive_hash
	);

	/* add keys with duplicates */
	add_map(hash_table, "testing", "my_value"); 
	add_map(hash_table, "testing2", "my_value2"); 
	add_map(hash_table, "testing3", "my_value3");
	add_map(hash_table, "testing3", "Duplicate");
	add_map(hash_table, "testing4", "my_value3");
	add_map(hash_table, "testing5", "my_value3");
	add_map(hash_table, "testing6", "my_value7");
	add_map(hash_table, "testing6", "Duplicate");
	add_map(hash_table, "testing67", "Duplicate");

	/* lookup keys */
	void *item = lookup_key(hash_table, "testing3"); 
	void *item2 = lookup_key(hash_table, "testing6"); 
	void *head = lookup_key(hash_table, "testing");
	char *value = (char*)head; 

	if(strcmp((char*)item2, "Duplicate") != 0){
		equality_status = false; 
	}

	if(strcmp((char*)item, "Duplicate") != 0){
		equality_status = false; 
	}

	if(strcmp((char*)head, "my_value") != 0){
		equality_status = false; 
	}

	char *expected_keys[20] = {
		"testing67", "testing6", "testing5", 
		"testing4", "testing3", "testing2"
	};

	char *expected_values[20] = {
		"Duplicate", "Duplicate", "my_value3", 
		"my_value3", "Duplicate", "my_value2"
	};

	/* get keys and values in hash map */
	for(int i = 0; i < initial_size; i++){
		h_ll_t *head = hash_table->table[i];

		int counter = 0;
		while(head->next){
			if((char*)head->key != NULL){
				if(strcmp((char*)head->key, expected_keys[counter]) != 0){
					equality_status = false; 
				}

				if(strcmp((char*)head->value, expected_values[counter]) != 0){
					equality_status = false; 
				}
				counter += 1; 
			}
			head = head->next; 
		}
	}

    if(!equality_status) {
        printf("%s::%s... FAILED\n", __FILE__, __FUNCTION__);
    } else {
        printf("%s::%s... \e[0;32mPASSED\e[0m\n", __FILE__, __FUNCTION__);
    } 
}


#include "includes/test_set.h"


void test_set_ordered() {

    int expected_items[5] = {5, 4, 3, 2, 1};  
    bool equality_status = true; 


    set_t *s = init_set(true);
    insert_ordered(s, 5, NULL, 0);  
    insert_ordered(s, 4, NULL, 0);  
    insert_ordered(s, 3, NULL, 0);  
    insert_ordered(s, 2, NULL, 0); 
    insert_ordered(s, 1, NULL, 0);  

    int counter = 0; 
    while(s->root != NULL) {
        assert(s->root->id == expected_items[counter]); 
        counter += 1; 
        s->root = s->root->next; 
    }

	if(!equality_status) {
		printf("%s::%s... FAILED\n", __FILE__, __FUNCTION__); 
	} else {
		printf("%s::%s... \e[0;32mPASSED\e[0m\n", __FILE__, __FUNCTION__);
	}

}


void test_unique_entries_ordered() {


    char *expected_items[3] = {"aaa", "bbb", "ccc"};  
    bool equality_status = true; 

    set_t *s = init_set(true);
    insert_ordered(s, 5, "aaa", 0);  
    insert_ordered(s, 5, "aaa", 0);  
    insert_ordered(s, 5, "aaa", 0);  
    insert_ordered(s, 2, "bbb", 0);
    insert_ordered(s, 2, "bbb", 0); 
    insert_ordered(s, 1, "ccc", 0); 

    int counter = 0; 
    while(s->root != NULL) {
        assert(strcmp(s->root->label, expected_items[counter]) == 0); 
        counter += 1; 
        s->root = s->root->next; 
    }

	if(!equality_status) {
		printf("%s::%s... FAILED\n", __FILE__, __FUNCTION__); 
	} else {
		printf("%s::%s... \e[0;32mPASSED\e[0m\n", __FILE__, __FUNCTION__);
	}
    
}

void test_index_lookup_ordered() {

    char *expected_items[3] = {"aaa", "bbb", "ccc"};  
    bool equality_status = true; 

    set_t *s = init_set(true);
    insert_ordered(s, 5, "aaa", 0);  
    insert_ordered(s, 5, "aaa", 0);  
    insert_ordered(s, 5, "aaa", 0);  
    insert_ordered(s, 2, "bbb", 0); 
    insert_ordered(s, 1, "ccc", 0); 

    int index_one = get_value_ordered(s, "aaa");
    int index_two = get_value_ordered(s, "bbb");
    int index_three = get_value_ordered(s, "ccc");

    int condition_one = index_one == 0; 
    int condition_two = index_two == 1; 
    int condition_three = index_three == 2; 

    assert(condition_one == true || condition_two == true); 
    assert(condition_three == true); 

	if(!equality_status) {
		printf("%s::%s... FAILED\n", __FILE__, __FUNCTION__); 
	} else {
		printf("%s::%s... \e[0;32mPASSED\e[0m\n", __FILE__, __FUNCTION__);
	}

} 


void test_insert_count_lookup() {

    char *expected_items[3] = {"aaa", "bbb", "ccc"};  
    bool equality_status = true; 

    set_t *s = init_set(true);
    insert_ordered(s, 1, NULL, 0);  
    insert_ordered(s, 2, NULL, 0);  
    insert_ordered(s, 3, NULL, 0);  
    insert_ordered(s, 4, NULL, 0); 
    insert_ordered(s, 5, NULL, 0); 
    insert_ordered(s, 5, NULL, 0); 
    insert_ordered(s, 5, NULL, 0); 
    insert_ordered(s, 5, NULL, 0); 
    insert_ordered(s, 5, NULL, 0); 

    print_items_ordered(s);     

}  


void test_get_items_ordered() {

    set_t *s = init_set(true);
    insert_ordered(s, 5, "aaa", 0);  
    insert_ordered(s, 5, "aaa", 0);  
    insert_ordered(s, 5, "aaa", 0);  
    insert_ordered(s, 2, "bbb", 0); 
    insert_ordered(s, 1, "ccc", 0);


    char *expected_items[3] = {"aaa", "bbb", "ccc"};  
    bool equality_status = true;

    queue_t *q = init_queue(10); 
    get_items_ordered(s, q); 

	for(int i = q->front_index; i <= q->rear_index; i++) {
        int condition = strcmp(q->items[i]->string, expected_items[i]) == 0; 
        assert(condition == true); 
    }

	if(!equality_status) {
		printf("%s::%s... FAILED\n", __FILE__, __FUNCTION__); 
	} else {
		printf("%s::%s... \e[0;32mPASSED\e[0m\n", __FILE__, __FUNCTION__);
	}

}


void test_set_sorted() {

    /* expected behavior */
    int expected_items[4] = {1, 2, 3, 4};  
    bool equality_status = true; 

    /* init instance of set */
    set_t *s = init_set(true);
    insert_sorted(s, 1, NULL, 0);  
    insert_sorted(s, 2, NULL, 0);  
    insert_sorted(s, 3, NULL, 0);  
    insert_sorted(s, 4, NULL, 0);  
    insert_sorted(s, 1, NULL, 0); 

    /* retrieve values and store in queue  */
    queue_t *q = init_queue(s->count); 
    get_items_sorted(s->root, q);

	for(int i = q->front_index; i <= q->rear_index; i++) {
        assert(q->items[i]->integer == expected_items[i]);        
    }

	if(!equality_status) {
		printf("%s::%s... FAILED\n", __FILE__, __FUNCTION__); 
	} else {
		printf("%s::%s... \e[0;32mPASSED\e[0m\n", __FILE__, __FUNCTION__);
	}

}

void test_unique_entries_sorted() {

    bool equality_status = true;
    int expected_items[6] = {5,10,11,12,13,14};  

    /* init instance of set */
    set_t *s = init_set(true);
    insert_sorted(s, 10, NULL, 0);  
    insert_sorted(s, 11, NULL, 0);  
    insert_sorted(s, 12, NULL, 0);  
    insert_sorted(s, 13, NULL, 0);  
    insert_sorted(s, 14, NULL, 0); 
    insert_sorted(s, 5, NULL, 0); 
    insert_sorted(s, 5, NULL, 0); 

    /* retrieve values and store in queue  */
    queue_t *q = init_queue(s->count); 
    get_items_sorted(s->root, q);

    /* check that ordering works */
	for(int i = q->front_index; i <= q->rear_index; i++) {
        assert(q->items[i]->integer == expected_items[i]);      
    }

	if(!equality_status) {
		printf("%s::%s... FAILED\n", __FILE__, __FUNCTION__); 
	} else {
		printf("%s::%s... \e[0;32mPASSED\e[0m\n", __FILE__, __FUNCTION__);
	}

}


void test_lexographic_ordering_sorted() {

    bool equality_status = true;
    char *expected_items[8] = {
        "c","b","a","Over","Jumped","Fox","E","D"
    };  

    /* init instance of set */
    set_t *s = init_set(true);
    insert_sorted(s, 0, "a", 0); 
    insert_sorted(s, 0, "b", 0); 
    insert_sorted(s, 0, "c", 0); 
    insert_sorted(s, 0, "D", 0); 
    insert_sorted(s, 0, "E", 0);
    insert_sorted(s, 0, "Fox", 0);
    insert_sorted(s, 0, "Jumped", 0);
    insert_sorted(s, 0, "Over", 0);

    /* retrieve values and store in queue  */
    queue_t *q = init_queue(s->count); 
    get_items_sorted(s->root, q);

    /* check that ordering works */
	for(int i = q->front_index; i <= q->rear_index; i++) {
        assert(strcmp(q->items[i]->string, expected_items[i]) == 0);       
    }

	if(!equality_status) {
		printf("%s::%s... FAILED\n", __FILE__, __FUNCTION__); 
	} else {
		printf("%s::%s... \e[0;32mPASSED\e[0m\n", __FILE__, __FUNCTION__);
	}
	
}


void test_index_lookup_sorted() {

    bool equality_status = true;

    /* init instance of set */
    set_t *s = init_set(true);
    insert_sorted(s, 0, "a", 0); 
    insert_sorted(s, 0, "b", 0); 
    insert_sorted(s, 0, "c", 0); 
    insert_sorted(s, 0, "D", 0); 
    insert_sorted(s, 0, "E", 0);

    int first_index = get_item_sorted(s, "a");
    int second_index = get_item_sorted(s, "b");
    int third_index = get_item_sorted(s, "C");

    assert(first_index == 2 && second_index == 1);
    assert(third_index == 0);  


	if(!equality_status) {
		printf("%s::%s... FAILED\n", __FILE__, __FUNCTION__); 
	} else {
		printf("%s::%s... \e[0;32mPASSED\e[0m\n", __FILE__, __FUNCTION__);
	}

} 
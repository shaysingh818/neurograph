#include "includes/test_set.h"


void test_set_ordered() {

    int expected_items[6] = {5, 4, 3, 2, 1, 8};  

    ordered_set_t *s = init_array_set(5);
    insert_ordered(s, 5, NULL, 0);  
    insert_ordered(s, 4, NULL, 0);  
    insert_ordered(s, 3, NULL, 0);  
    insert_ordered(s, 2, NULL, 0); 
    insert_ordered(s, 1, NULL, 0); 

    /* validate that size changes */
    assert(s->capacity == 5);
    insert_ordered(s, 8, NULL, 0);
    assert(s->capacity == 10); 
    assert(s->used == 6); 

    /* check that items are unique */
    for(int i = 0; i < s->used; i++){
        assert(s->items[i]->id == expected_items[i]); 
    } 

	printf("%s::%s... \e[0;32mPASSED\e[0m\n", __FILE__, __FUNCTION__);
}


void test_unique_entries_ordered() {

    char *expected_items[3] = {"aaa", "bbb", "ccc"};  

    ordered_set_t *s = init_array_set(5);
    insert_ordered(s, 5, "aaa", 0);  
    insert_ordered(s, 5, "aaa", 0);  
    insert_ordered(s, 5, "aaa", 0);  
    insert_ordered(s, 2, "bbb", 0);
    insert_ordered(s, 2, "bbb", 0); 
    insert_ordered(s, 1, "ccc", 0);

    assert(s->capacity == 5); 
    assert(s->used == 3);

    for(int i = 0; i < s->used; i++){
        int compare = strcmp(s->items[i]->label, expected_items[i]) == 0; 
        assert(compare == true); 
    } 

	printf("%s::%s... \e[0;32mPASSED\e[0m\n", __FILE__, __FUNCTION__);
    
}

void test_index_lookup_ordered() {

    char *expected_items[3] = {"aaa", "bbb", "ccc"};  
    bool equality_status = true; 

    ordered_set_t *s = init_array_set(6);
    insert_ordered(s, 5, "aaa", 0);  
    insert_ordered(s, 5, "aaa", 0);  
    insert_ordered(s, 5, "aaa", 0);  
    insert_ordered(s, 2, "bbb", 0); 
    insert_ordered(s, 1, "ccc", 0); 

    int index_one = get_value_key(s, "aaa");
    int index_two = get_value_key(s, "bbb");
    int index_three = get_value_key(s, "ccc");

    /* asserts for get value key */
    assert(index_one == 0); 
    assert(index_two == 1); 
    assert(index_three == 2); 

    int id_one = get_value_id(s, 2); 
    int id_two = get_value_id(s, 5);
    int id_three = get_value_id(s, 1);  
    int id_fail = get_value_id(s, 0);

    assert(id_three == 2);
    assert (id_two == 0); 
    assert(id_one == 1);
    assert(id_fail == -1);   

	printf("%s::%s... \e[0;32mPASSED\e[0m\n", __FILE__, __FUNCTION__);
} 


void test_insert_count_lookup() {

    char *expected_items[3] = {"aaa", "bbb", "ccc"};  
    bool equality_status = true; 

    ordered_set_t *s = init_array_set(10);
    insert_ordered(s, 1, NULL, 0);  
    insert_ordered(s, 2, NULL, 0);  
    insert_ordered(s, 3, NULL, 0);  
    insert_ordered(s, 4, NULL, 0);
    insert_ordered(s, 4, NULL, 0); 
    insert_ordered(s, 5, NULL, 0); 
    insert_ordered(s, 5, NULL, 0); 
    insert_ordered(s, 5, NULL, 0); 
    insert_ordered(s, 5, NULL, 0); 
    insert_ordered(s, 5, NULL, 0);

    int highest_index = get_value_id(s, 5);
    int index_one = get_value_id(s, 4);
    int index_two = get_value_id(s, 3);
    int index_three = get_value_id(s, 2);
    int index_four = get_value_id(s, 1);

    node_t *highest_item = s->items[highest_index]; 
    node_t *item_one = s->items[index_one]; 
    node_t *item_two = s->items[index_two]; 
    node_t *item_three = s->items[index_three]; 
    node_t *item_four = s->items[index_four]; 

    int highest_insert_count = get_insert_count(s, highest_item);  

    assert(highest_insert_count == 4);
    assert(get_insert_count(s, item_one) == 1); 
    assert(get_insert_count(s, item_two) == 0);
    assert(get_insert_count(s, item_three) == 0);
    assert(get_insert_count(s, item_four) == 0);

	printf("%s::%s... \e[0;32mPASSED\e[0m\n", __FILE__, __FUNCTION__);

}  


void test_get_items_ordered() {

    ordered_set_t *s = init_array_set(10);
    insert_ordered(s, 5, "aaa", 0);  
    insert_ordered(s, 5, "aaa", 0);  
    insert_ordered(s, 5, "aaa", 0);  
    insert_ordered(s, 2, "bbb", 0); 
    insert_ordered(s, 1, "ccc", 0);



	printf("%s::%s... \e[0;32mPASSED\e[0m\n", __FILE__, __FUNCTION__);

}


void test_set_sorted() {

    /* expected behavior */
    int expected_items[4] = {4, 3, 2, 1};  
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
        assert(q->items[i]->id == expected_items[i]);
    }

	printf("%s::%s... \e[0;32mPASSED\e[0m\n", __FILE__, __FUNCTION__);

}

void test_unique_entries_sorted() {

    bool equality_status = true;
    int expected_items[6] = {14,13,12,11,10,5};  

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
        assert(q->items[i]->id == expected_items[i]);
    }

	printf("%s::%s... \e[0;32mPASSED\e[0m\n", __FILE__, __FUNCTION__);

}


void test_lexographic_ordering_sorted() {

    bool equality_status = true;
    char *expected_items[8] = {
        "D", "E", "Fox", "Jumped", "Over", "a", "b", "c"
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
        int condition = strcmp(q->items[i]->label, expected_items[i]) == 0; 
        assert(condition == true); 
    }

	printf("%s::%s... \e[0;32mPASSED\e[0m\n", __FILE__, __FUNCTION__);
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

    assert(first_index == 2); 
    assert(second_index == 3); 
    assert(third_index == 0); 

	printf("%s::%s... \e[0;32mPASSED\e[0m\n", __FILE__, __FUNCTION__);
} 

#include "includes/test_ll.h"


void test_push_ll() {

    /* a simple test */
    bool equality_status = true;  
	char *values[5] = {
        "testing", "testing1",
        "testing2", "testing3",
        "testing4" 
	};

    node_t *head = create_node(0, "testing", 0);
    for(int i = 1; i < 5; i++){
        node_t *temp = create_node(i, values[i], 0); 
        push_ll(&head, temp); 
    }

    while(head != NULL) {
        int compare = strcmp(head->node_type->node->label, values[head->id]) == 0;
        assert(compare == true);  
        head = head->next; 
    } 

	if(!equality_status) {
		printf("%s::%s... FAILED\n", __FILE__, __FUNCTION__); 
	}
	printf("%s::%s... \e[0;32mPASSED\e[0m\n", __FILE__, __FUNCTION__);

}

void test_insert_after_ll() {

    /* a simple test */
    bool equality_status = true;  
	char *values[6] = {
        "testing", "testing1", "testing2",
        "testing3", "testing4",
        "testing5" 
	};

    node_t *head = create_node(0, "testing", 0);
    for(int i = 1; i < 6; i++){
        node_t *temp = create_node(i, values[i], 0);
        push_ll(&head, temp); 
    }


    /* test insert after method */
    node_t *temp_node = create_node(6, "insert_after", 0); 
    insert_after_ll(head, temp_node); 

    int counter = 0;  
    while(head != NULL) {
        int compare = strcmp(head->node_type->node->label, values[head->id]) == 0;
        if(counter == 1) {
            compare = strcmp(head->node_type->node->label, "insert_after") == 0; 
        }
        assert(compare == true); 
        head = head->next;
        counter += 1;  
    }

	if(!equality_status) {
		printf("%s::%s... FAILED\n", __FILE__, __FUNCTION__); 
	}
	printf("%s::%s... \e[0;32mPASSED\e[0m\n", __FILE__, __FUNCTION__);

}

void test_append_ll() {

    bool equality_status = true;  
	char *values[6] = {
        "testing", "testing1", "testing2",
        "testing3", "testing4",
        "testing5" 
	};

    node_t *head = create_node(0, "testing", 0);
    for(int i = 1; i < 6; i++){
        node_t *temp = create_node(i, values[i], 0);
        append_ll(&head, temp); 
    }

    /* get list results */
    while(head != NULL) {
        int compare = strcmp(head->node_type->node->label, values[head->id]) == 0;
        assert(compare == true);  
        head = head->next;
    }

	if(!equality_status) {
		printf("%s::%s... FAILED\n", __FILE__, __FUNCTION__); 
	}
	printf("%s::%s... \e[0;32mPASSED\e[0m\n", __FILE__, __FUNCTION__);

}


void test_ull() {
	
	/* test unique linked list */ 
	int equality_status = true; 
	u_ll_t *n = create_ull("value");
	append(&n, "value2"); 	
	append(&n, "value3");
	append(&n, "value6");
	append(&n, "value4"); 
	append(&n, "value5"); 
	append(&n, "value6");

	char expected_output[6][100] = {
		"value", "value2", "value3", 
		"value6", "value4", "value5"
	};

	while(n != NULL) {
		int condition = strcmp(n->value, expected_output[n->index]) == 0;
        assert(condition == true);  
		n = n->next; 
	}

	if(!equality_status) {
		printf("%s::%s... FAILED\n", __FILE__, __FUNCTION__); 
	}
	printf("%s::%s... \e[0;32mPASSED\e[0m\n", __FILE__, __FUNCTION__);
}


void test_init_array() {

    array_t *array = init_array();
    assert(array->capacity == 2);
    assert(array->item_count == 0);

    /* validate nodes are allocated */ 
    for(int i = 0; i < array->capacity; i++){
        array->items[i] = create_node(0, "test", 0); 
    }


	printf("%s::%s... \e[0;32mPASSED\e[0m\n", __FILE__, __FUNCTION__);

}


void test_insert_array() {

    array_t *array = init_array();
    assert(array->capacity == 2);
    assert(array->item_count == 0);

    char *expected_items[100] = {"test", "test1", "test2", "test3"}; 
    char *expected_items_removed[100] = {"test"}; 

    insert(array, create_node(0, "test", 0));  
    insert(array, create_node(1, "test1", 0));  
    insert(array, create_node(2, "test2", 0));  
    insert(array, create_node(3, "test3", 0)); 


    for(int i = 0; i < array->item_count; i++){
        int condition = strcmp(array->items[i]->node_type->node->label, expected_items[i]) == 0; 
        assert(condition == true); 
    }

    pop_array(array); 
    pop_array(array); 
    pop_array(array);


    for(int i = 0; i < array->item_count; i++){
        int condition = strcmp(array->items[i]->node_type->node->label, expected_items_removed[i]) == 0; 
        assert(condition == true); 
    }

    /* insert a million entries */
    array_t *benchmark_array = init_array();
    for(int i = 0; i < 1000000; i++){
        insert(benchmark_array, create_node(i, "test3", 0)); 
    }

	printf("%s::%s... \e[0;32mPASSED\e[0m\n", __FILE__, __FUNCTION__);

}


void test_insert_char() {

    array_t *array = init_array();
    assert(array->capacity == 2);
    assert(array->item_count == 0);

    char *expected_items[100] = {"test", "test1", "test2", "test3"}; 
    char *expected_items_removed[100] = {"test"}; 

    insert_char(array, "test");  
    insert_char(array, "test1");  
    insert_char(array, "test2");  
    insert_char(array, "test3");


    for(int i = 0; i < array->item_count; i++){
        int condition = strcmp(array->items[i]->node_type->node->label, expected_items[i]) == 0; 
        assert(condition == true);
        assert(array->items[i]->id == i);  
    }

	printf("%s::%s... \e[0;32mPASSED\e[0m\n", __FILE__, __FUNCTION__);

}


void test_remove_char() {

    array_t *array = init_array();
    assert(array->capacity == 2);
    assert(array->item_count == 0);

    insert_char(array, "test");  
    insert_char(array, "test1");  
    insert_char(array, "test2");  
    insert_char(array, "test3");
    insert_char(array, "test4");

    remove_char(array, "test2");
    assert(array->item_count == 4);  

    remove_char(array, "test");
    assert(array->item_count == 3);  

    remove_char(array, "test2");
    assert(array->item_count == 2); 

	printf("%s::%s... \e[0;32mPASSED\e[0m\n", __FILE__, __FUNCTION__);

} 
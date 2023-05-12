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
        int compare = strcmp(head->label, values[head->id]) == 0; 
        if(!compare) {
            equality_status = false; 
        }
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
        int compare = strcmp(head->label, values[head->id]) == 0;
        if(counter == 1) {
            compare = strcmp(head->label, "insert_after") == 0; 
        }

        if(!compare) {
            equality_status = false; 
        }
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
        int compare = strcmp(head->label, values[head->id]) == 0; 
        if(!compare) {
            equality_status = false; 
        }
        head = head->next;
    }

	if(!equality_status) {
		printf("%s::%s... FAILED\n", __FILE__, __FUNCTION__); 
	}
	printf("%s::%s... \e[0;32mPASSED\e[0m\n", __FILE__, __FUNCTION__);

}
#include "includes/map_test.h"


void test_ull() {
	
	/* test unique linked list */ 
	int equality_status = TRUE; 
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
		if(!condition) {
			equality_status = FALSE; 
		}
		n = n->next; 
	}

	if(!equality_status) {
		printf("%s::%s... FAILED\n", __FILE__, __FUNCTION__); 
	}
	printf("%s::%s... \e[0;32mPASSED\e[0m\n", __FILE__, __FUNCTION__);



}

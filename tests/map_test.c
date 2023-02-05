#include "includes/map_test.h"


void test_ull() {
	

	u_ll_t *n = create_ull("value");
	append(&n, "value2"); 	
	append(&n, "value3");
	append(&n, "value6");
	append(&n, "value4"); 
	append(&n, "value5"); 
	append(&n, "value6");


	print_u_ll_t(n); 


}

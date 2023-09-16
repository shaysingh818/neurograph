#include "includes/test_value.h"

void test_value_init(){

    /* create single values (without ops) */
    value_t *a = input_node(2.00); 
    value_t *b = input_node(1.00);

    assert(a->output == 2.00);
    assert(a->left == NULL); 
    assert(a->right == NULL); 
    assert(b->output == 1.00); 
    assert(b->left == NULL); 
    assert(b->right == NULL); 

    printf("%s::%s... \e[0;32mPASSED\e[0m\n", __FILE__, __FUNCTION__);

}
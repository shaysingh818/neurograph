#include "includes/test_node.h"

void test_create_node() {

    node_t *node = create_node(1, "test", 2); 
    assert(node->id == 1); 
    assert(node->node_type->node->weight == 2);

    printf("%s::%s... \e[0;32mPASSED\e[0m\n", __FILE__, __FUNCTION__);

}
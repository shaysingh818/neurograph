#include "includes/test_adj_list.h"
#include "includes/test_ll.h"

int main(int argc, char **argv) {


    /* test list library methods */
    test_push_ll();
    test_insert_after_ll(); 
    test_append_ll(); 
    test_init_array(); 
    test_insert_array(); 
    test_insert_char();  

    /* test adjacency list representation */ 
    test_graph();
    test_weighted_graph(); 
    test_transpose_graph();
    test_get_node_by_id();
    test_resize_adj_list();

}
#include "includes/test_map.h"
#include "includes/test_table.h"

int main(int argc, char **argv) {

    /* test hash map */
    test_hash_table(); 
    test_additive_hash(); 
    test_compare_char();
    test_hash_linked_list(); 
    test_duplicates();

    /* open address hash map tests */
    test_create_hash_map();
    test_insert_table_key();
    test_delete_table_key(); 
    test_table_resize(); 

}
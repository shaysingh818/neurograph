#include "includes/test_set.h"

int main(int argc, char **argv) {

    /* test set data structure */
    test_set_ordered();
    test_unique_entries_ordered(); 
    test_index_lookup_ordered();
    test_insert_count_lookup();
    test_set_sorted(); 
    test_unique_entries_sorted();
    test_lexographic_ordering_sorted(); 
    test_index_lookup_sorted();
    // test_get_items_sorted();   

    //test_get_items_ordered();   

}

#ifndef TEST_SET_H
#define TEST_SET_H

#include "../../includes/set.h"
#include <assert.h>

/* ordered insert methods */
void test_set_ordered();
void test_unique_entries_ordered();
void test_lexographic_ordering_ordered(); 
void test_index_lookup_ordered();
void test_insert_count_lookup();   
void test_get_items_ordered(); 

/* sorted methods */
void test_set_sorted();
void test_unique_entries_sorted();
void test_lexographic_ordering_sorted(); 
void test_index_lookup_sorted();
void test_get_items_sorted();   

#endif
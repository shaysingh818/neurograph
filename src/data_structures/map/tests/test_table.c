#include "includes/test_table.h"

void test_create_hash_map() {

    int size = 10; 
    hash_table_t *table = hash_table(
        size, 
        0.5, 
        compare_char,
        NULL,
        NULL,
        additive_hash
    );

    assert(table->size == size);
    assert(table->used == 0); 
    assert(table->active == 0);

    bin_t *end = table->table + table->size; 
    for(bin_t *bin = table->table; bin != end; bin++){
        assert(bin->is_free == true); 
        assert(bin->is_deleted == false); 
    }

	printf("%s::%s... \e[0;32mPASSED\e[0m\n", __FILE__, __FUNCTION__);
}


void test_insert_table_key() {

    int size = 10; 
    hash_table_t *table = hash_table(
        size, 
        0.5, 
        compare_char,
        NULL,
        NULL,
        additive_hash
    );

    /* string keys and values */
    char *char_keys[100] = {"key", "key2", "key3"}; 
    char *char_values[100] = {"value", "value2", "value3"}; 

    /* str allocator used here to avoid memory leaks during UT*/
    add_table_map(table, str("key"), str("value")); 
    add_table_map(table, str("key2"), str("value2")); 
    add_table_map(table, str("key3"), str("value3"));

    for(int i = 0; i < 3; i++){
        char *expected_value = lookup_table_key(table, char_keys[i]); 
        bool condition = strcmp(expected_value, char_values[i]) == 0; 
        assert(condition); 
    }


    size = 1; /* doesn't work with sizes greater than 5 ? */ 
    hash_table_t *table2 = hash_table(
        size, 
        0.5, 
        compare_char,
        NULL,
        NULL,
        additive_hash
    );


    add_table_map(table2, str("A"), create_node(1, "B", 0)); 
    add_table_map(table2, str("B"), create_node(2, "C", 0)); 
    add_table_map(table2, str("C"), create_node(3, "D", 0));
    add_table_map(table2, str("movie_rating"), create_node(3, "D", 0));
    add_table_map(table2, str("genre"), create_node(4, "D", 0));


    char *char_node_keys[100] = {"A", "B", "C", "movie_rating", "genre"}; 
    char *char_node_values[100] = {"B", "C", "D", "D", "D"};


    for(int i = 0; i < 5; i++){
        node_t *node = lookup_table_key(table2, char_node_keys[i]); 
        char *expected_value = node->node_type->node->label; 
        bool condition = strcmp(expected_value, char_node_values[i]) == 0; 
        assert(condition); 
    }


    size = 1; /* doesn't work with sizes greater than 5 ? */ 
    hash_table_t *header_table = hash_table(
        size, 
        0.5, 
        compare_char,
        NULL,
        NULL,
        additive_hash
    );

    char *header_names[100][100] = {
        "Rank", "City", "Population", "Area KM2", "Area M2", "Density KM2", "Density  M2",
        "age", "sex", "cp", "trestbps", "chol", "fbs", "restecg", "thalach", "exang",
        "index", "movie_name", "year_of_release", "category", "run_time", "genre", "imdb_rating"
    }; 

    int header_count = 23; 
    for(int i = 0; i < header_count; i++) {
        add_table_map(header_table, header_names[i], create_node(1, "B", 0)); 
    }


	printf("%s::%s... \e[0;32mPASSED\e[0m\n", __FILE__, __FUNCTION__);

} 


void test_delete_table_key() {

    int size = 1; /* doesn't work with sizes greater than 5 ? */ 
    hash_table_t *header_table = hash_table(
        size, 
        0.5, 
        compare_char,
        free_char,
        NULL,
        additive_hash
    );

    char *header_names[100] = {
        "Rank", "City", "Population", "Area KM2", "Area M2", "Density KM2", "Density  M2",
        "age", "sex", "cp", "trestbps", "chol", "fbs", "restecg", "thalach", "exang",
        "index", "movie_name", "year_of_release", "category", "run_time", "genre", "imdb_rating"
    }; 

    /* in practice, the character values will already be allocated */
    int header_count = 23; 
    for(int i = 0; i < header_count; i++) {
        add_table_map(header_table, str(header_names[i]), create_node(1, "B", 0)); 
    }

    delete_table_key(header_table, "imdb_rating");
    assert(lookup_table_key(header_table, "imdb_rating") == 0);

    delete_table_key(header_table, "Rank");
    assert(lookup_table_key(header_table, "Rank") == 0);

    delete_table_key(header_table, "Area M2");
    assert(lookup_table_key(header_table, "Area M2") == 0);

    delete_table_key(header_table, "Area");
    delete_table_key(header_table, "Area 878");

    delete_hash_table(header_table); 

	printf("%s::%s... \e[0;32mPASSED\e[0m\n", __FILE__, __FUNCTION__);

} 


void test_table_resize() {

    int size = 1; /* doesn't work with sizes greater than 5 ? */ 
    hash_table_t *header_table = hash_table(
        size, 
        0.5, 
        compare_char,
        free_char,
        free_char,
        additive_hash
    );

    assert(header_table->size == 1); 

    add_table_map(header_table, str("moving_rating"), str("value")); 
    assert(header_table->size == 2); 

    add_table_map(header_table, str("genre"), str("value2")); 
    assert(header_table->size == 4); 

    add_table_map(header_table, str("height"), str("5ft 3 inches")); 
    assert(header_table->size == 8);

    delete_hash_table(header_table);  

	printf("%s::%s... \e[0;32mPASSED\e[0m\n", __FILE__, __FUNCTION__);
} 


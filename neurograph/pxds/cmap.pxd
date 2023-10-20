cimport pxds.cnode

cdef extern from "../src/data_structures/includes/map.h":

    ctypedef void (*destructor_func)(void*)
    ctypedef bint (*compare_func)(void*, void*)
    ctypedef int (*hash_func)(int, char* size_t)

    struct hash_linked_list:
        int hash_key
        void *key
        void *value
        hash_linked_list *next

    struct HashTable:
        hash_linked_list **table
        int size
        int used
        int active
        compare_func key_cmp
        destructor_func key_destructor
        destructor_func val_destructor
        hash_func hash_function

    HashTable *init_table(
        int size,
        compare_func key_cmp,
        destructor_func key_destructor,
        destructor_func val_destructor,
        hash_func hash_function
    )

    void add_map(HashTable *table, void *key, void *value);
    int additive_hash(int state, char *input, size_t len); 
    int jenkins_hash(int state, char *input, size_t len); 




cdef extern from "../src/data_structures/map/includes/hash.h":
    
    ctypedef void (*destructor_func)(void*) 
    ctypedef bint (*compare_func)(void*, void*)
    ctypedef int (*hash_func)(int, char*, size_t)

    int additive_hash(int state, char *input, size_t len)
    int jenkins_hash(int state, char *input, size_t len)

    bint compare_char(void *key1, void *key2)
    void free_char(void *value)
    char *str(char *key_value) 

    int probe(int k, int i, int m)


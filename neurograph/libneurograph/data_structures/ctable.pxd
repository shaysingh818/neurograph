cimport libneurograph.data_structures.chash as hash

cdef extern from "<neurograph/data_structures/map/includes/table.h>":

    struct Bin:
        bint is_free
        bint is_deleted
        int hash_key
        void *key
        void *value

    struct BinTable:
        Bin *table
        int size
        int used
        int active
        double load_factor
        hash.compare_func key_cmp
        hash.destructor_func key_destructor
        hash.hash_func hash_function

    BinTable *hash_table(
        int size, 
        double load_factor,
        hash.compare_func key_cmp, 
        hash.destructor_func key_destructor,
        hash.destructor_func val_destructor,
        hash.hash_func hash_function
    )

    void delete_hash_table(BinTable *table)
    void add_table_map(BinTable *table, void *key, void *value)
    void delete_table_key(BinTable *table, void *key)
    void *lookup_table_key(BinTable *table, void *key) 
    void table_resize(BinTable *table, int new_size)

    int probe(int k, int i, int m)
    void print_table(BinTable *table) 


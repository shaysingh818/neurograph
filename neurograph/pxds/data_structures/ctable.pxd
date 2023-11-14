cimport pxds.data_structures.chash as hash

cdef extern from "../src/data_structures/map/includes/table.h":
    
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
        compare_func key_cmp
        destructor_func key_destructor
        hash_func hash_function

    BinTable *hash_table(
	int size, 
	double load_factor,
	compare_func key_cmp, 
	destructor_func key_destructor,
	destructor_func val_destructor,
	hash_func hash_function
    )

    void delete_hash_table(BinTable *table);
    void add_table_map(BinTable *table, void *key, void *value); 
    void delete_table_key(BinTable *table, void *key); 
    void *lookup_table_key(BinTable *table, void *key); 
    void table_resize(BinTable *table, int new_size); 

    int probe(int k, int i, int m);
    void print_table(BinTable *table); 


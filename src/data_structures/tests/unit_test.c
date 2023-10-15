#include "includes/test_queue.h"
#include "includes/test_map.h"
#include "includes/test_matrix.h"
#include "includes/test_adj_list.h"
#include "includes/test_adj_mat.h"
#include "includes/test_ll.h"
#include "includes/test_set.h"

int main(int argc, char **argv) {


    /* test list library methods */
    test_push_ll();
    test_insert_after_ll(); 
    test_append_ll(); 
    test_init_array(); 
    test_insert_array(); 
    test_insert_char();  

	/* queue methods */ 
	test_init_queue();
	test_is_full();
	test_is_empty(); 
	test_front_rear();

    /* test matrice utility methods */
    test_init_vec(); 
    test_scalar_multiply(); 
    test_vector_multiplication();
    test_matrix_power(); 
    test_to_rows_cols();
    test_batch_rows();
    test_batch_even_matrix(); 
    test_batch_odd_matrix();  
    test_uniform_distribution();
    test_load_and_save_matrix();

    /* test matrice operations */ 
    test_dot_product();
    test_dot_unequal_dimensions();
    test_backprop_dot_product(); 
    test_add_mat();
    test_scale_add();  
    test_transpose_mat();
    test_scale_multiply();
    test_elementwise_multiply(); 
    test_add_matrix(); 
    test_matrix_difference();
    test_im2col(); 

    /* test adjacency list representation */ 
    test_graph();
    test_weighted_graph(); 
    test_transpose_graph();
    test_get_node_by_id();
    test_resize_adj_list();

    /* test adjacency matrix representation */
    test_init_adj_mat();
    test_add_node_mat_undirected();
    test_add_node_mat_directed();  
    test_search_by_id_mat(); 
    test_transpose_items_mat();  

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

    /* test hash map */
    test_hash_table(); 
    test_additive_hash(); 
    test_compare_char();
    test_hash_linked_list(); 
    test_duplicates();

}
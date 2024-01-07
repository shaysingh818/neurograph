#include "tests/includes/test_matrix.h"
#include "tests/includes/test_adj_mat.h"

int main(int argc, char **argv) {

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

    /* test adjacency matrix representation */
    test_init_adj_mat();
    test_add_node_mat_undirected();
    test_add_node_mat_directed();  
    test_search_by_id_mat(); 
    test_transpose_items_mat(); 
 
}

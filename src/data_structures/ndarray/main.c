#include "tests/includes/test_tensor.h"
#include "tests/includes/test_ops.h"

int main(int argc, char **argv) {

    /* test tensor method */
    test_ndimensional_index();
    test_get_tensor_indices();  
    test_set_tensor(); 
    test_reshape();
    test_save_tensor();

    /* ops */
    test_add_tensor(); 
    test_subtract_tensor();
    test_scale_add_tensor(); 
    test_tensor_dot_product(); 
    test_tensor_transpose();
    test_tensor_permute(); 

} 
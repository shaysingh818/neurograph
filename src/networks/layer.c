#include "includes/layer.h"


loss_value_t *loss_val(double(*loss)(double val), mat_t*(*loss_prime)(mat_t *val)) {
    loss_value_t *val = malloc(sizeof(loss_value_t)); 
    val->loss = loss; 
    val->loss_prime = loss_prime; 
    return val; 
} 


hash_table_t *loss_map() {

    hash_table_t *loss_table = hash_table(
        1, 0.5, 
        compare_char,
        NULL, 
        free_char, 
        additive_hash
    ); 

    add_table_map(
        loss_table, 
        str("tanh"), 
        loss_val(tanh_activation, tanh_prime)
    ); 

    add_table_map(
        loss_table, 
        str("sigmoid"), 
        loss_val(sigmoid, sigmoid_prime)
    ); 

    return loss_table; 
}


hash_table_t *layer_map() {

    hash_table_t *layer_table = hash_table(
        1, 0.5, 
        compare_char,
        NULL, 
        free_char, 
        additive_hash
    );

    add_table_map(
        layer_table, 
        str("linear"), 
        load_linear
    ); 

    add_table_map(
        layer_table, 
        str("loss"), 
        load_activation
    ); 

    return layer_table; 
} 

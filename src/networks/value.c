#include "includes/value.h"


value_t *value(double set_data, char *set_alias) {
    value_t *val = malloc(sizeof(value_t)); 
    int alias_size = strlen(set_alias) + 1; 
    val->alias = malloc(alias_size * sizeof(char)); 
}


value_t *add_value(value_t *v1, value_t *v2) {
    value_t *val = malloc(sizeof(value_t));
    val->data = v1->data + v2->data;  
    return val; 
} 

// value_t *subtract(value_t *v1, value_t *v2); 
// value_t *multiply(value_t *v1, value_t *v2); 
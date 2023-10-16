#include "includes/value.h"


value_t *value(mat_t *set_value) {
    value_t *val = malloc(sizeof(value_t));
    val->val = set_value; 
    val->right = NULL; 
    val->left = NULL;
    return val;  
} 


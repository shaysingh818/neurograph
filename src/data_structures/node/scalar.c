#include "includes/scalar.h"


scalar_t *_int(int value) {
    scalar_t *val = malloc(sizeof(scalar_t));
    val->value = malloc(sizeof(scalar_type_t));
    val->value->_int = value; 
    return val; 
}

scalar_t *_float(float value) {
    scalar_t *val = malloc(sizeof(scalar_t));
    val->value = malloc(sizeof(scalar_type_t));
    val->value->_float = value; 
    return val; 
}

scalar_t *_double(double value) {
    scalar_t *val = malloc(sizeof(scalar_t));
    val->value = malloc(sizeof(scalar_type_t));
    val->value->_double = value; 
    return val; 
}

scalar_t *_str(char *value) {
    scalar_t *val = malloc(sizeof(scalar_t));
    val->value = malloc(sizeof(scalar_type_t));
    size_t value_size = strlen(value)+1; 
    val->value->_char = malloc(value_size * sizeof(char)); 
    strcpy(val->value->_char, value);
    return val; 
} 
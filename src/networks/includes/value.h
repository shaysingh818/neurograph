#ifndef VALUE_H
#define VALUE_H


#include "../../data_structures/includes/matrix.h"

struct Value {
    double data;
    double grad;
    char *alias; 
    struct Value **children;  
};

typedef struct Value value_t; 


/* init value structure */
value_t *value(double set_data, char *set_alias);

/* Regular value (not matrices)*/
value_t *add_value(value_t *v1, value_t *v2); 
value_t *subtract_value(value_t *v1, value_t *v2); 
value_t *multiply_value(value_t *v1, value_t *v2); 

/* matrix operations */
value_t *add_mat(value_t *v1, value_t *v2); 
value_t *subtract_mat(value_t *v1, value_t *v2); 
value_t *multiply_mat(value_t *v1, value_t *v2); 


#endif
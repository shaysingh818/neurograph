#ifndef GENERICS_H
#define GENERICS_H

#include <stdlib.h> 
#include <stdio.h> 
#include <string.h>


union ScalarType {
    int _int;
    float _float;
    double _double;
    char *_char;
};

typedef union ScalarType scalar_type_t; 


struct ScalarValue { scalar_type_t *value; }; 
typedef struct ScalarValue scalar_t; 

scalar_t *_int(int value);
scalar_t *_float(float value);
scalar_t *_double(double value);
scalar_t *_str(char *value); 



#endif
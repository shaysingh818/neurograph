#ifndef OPS_H
#define OPS_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>
#include <time.h> 
#include <immintrin.h>
#include "ndarray.h"
 
/* ops for neural net  */
ndarray_t *ndot(ndarray_t *a, ndarray_t *b); 
ndarray_t *nadd(ndarray_t *t, ndarray_t *val);
ndarray_t *nsubtract(ndarray_t *t1, ndarray_t *t2);
ndarray_t *nscale_add(ndarray_t *a, ndarray_t *b); 
ndarray_t *ntranspose(ndarray_t *t);
ndarray_t *permute(ndarray_t *t, int *indice_order);

#endif
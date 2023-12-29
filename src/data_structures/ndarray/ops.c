#include "includes/ops.h"


ndarray_t *ndot(ndarray_t *a, ndarray_t *b) {

    if(a->rank != b->rank){
        printf("Tensors are not of the same dimension\n");
        exit(0);
    }

    if(a->shape[a->rank-1] != b->shape[0]){
        printf("Shape mismatch: %d != %d\n", a->shape[0], b->shape[a->rank-1]);
        exit(0); 
    }

    /* create temp result */
    ndarray_t *result_value = ndarray(a->rank, a->shape);

    for(int i = 0; i < a->size; i+=4){

        int remainder = a->size-i;
        if(remainder < 4){

            int index = i;
            for(int n = 0; n < remainder; n++){
                __m256d a1 = _mm256_set1_pd(a->values[index]);
                __m256d b1 = _mm256_set1_pd(b->values[index]);
                __m256d result = _mm256_mul_pd(a1, b1);
                result_value->values[index] = result[0];
                index += 1; 
            }

        } else {

            __m256d a1 = _mm256_set_pd(
                a->values[i],
                a->values[i+1],
                a->values[i+2],
                a->values[i+3]
            );

            __m256d b1 = _mm256_set_pd(
                b->values[i],
                b->values[i+1],
                b->values[i+2],
                b->values[i+3]
            );

            /* mult vecs */
            __m256d result = _mm256_mul_pd(a1, b1);

            /* copy result segment to tensor */
            result_value->values[i] = result[3];
            result_value->values[i+1] = result[2];
            result_value->values[i+2] = result[1];
            result_value->values[i+3] = result[0];

        }

    }

    return result_value;

} 


ndarray_t *nadd(ndarray_t *t, ndarray_t *val) {

    /* validate tensor sizes */
    if(t->size != val->size){
        printf("Tensor size mismatch: %d != %d\n", t->size, val->size); 
        exit(0); 
    }

    /* create temp result */
    ndarray_t *result_value = ndarray(t->rank, t->shape);

    for(int i = 0; i < t->size; i+=4){

        int remainder = t->size-i;
        if(remainder < 4){

            int index = i;
            for(int n = 0; n < remainder; n++){
                __m256d a = _mm256_set1_pd(t->values[index]);
                __m256d b = _mm256_set1_pd(val->values[index]);
                __m256d result = _mm256_add_pd(a, b);
                result_value->values[index] = result[0];
                index += 1; 
            }

        } else {

            __m256d a = _mm256_set_pd(
                t->values[i],
                t->values[i+1],
                t->values[i+2],
                t->values[i+3]
            );

            __m256d b = _mm256_set_pd(
                val->values[i],
                val->values[i+1],
                val->values[i+2],
                val->values[i+3]
            );

            /* add vecs */
            __m256d result = _mm256_add_pd(a, b);

            /* copy result segment to tensor */
            result_value->values[i] = result[3];
            result_value->values[i+1] = result[2];
            result_value->values[i+2] = result[1];
            result_value->values[i+3] = result[0];
        }
    }

    return result_value;
} 


ndarray_t *nsubtract(ndarray_t *t1, ndarray_t *t2) {

    /* validate tensor sizes */
    if(t1->size != t2->size){
        printf("Tensor size mismatch: %d != %d\n", t1->size, t2->size); 
        exit(0); 
    }

    /* create temp result */
    ndarray_t *result_value = ndarray(t1->rank, t1->shape);

    for(int i = 0; i < t1->size; i+=4){

        int remainder = t1->size-i;
        if(remainder < 4){

            int index = i;
            for(int n = 0; n < remainder; n++){
                __m256d a = _mm256_set1_pd(t1->values[index]);
                __m256d b = _mm256_set1_pd(t2->values[index]);
                __m256d result = _mm256_sub_pd(a, b);
                result_value->values[index] = result[0];
                index += 1; 
            }

        } else {

            __m256d a = _mm256_set_pd(
                t1->values[i],
                t1->values[i+1],
                t1->values[i+2],
                t1->values[i+3]
            );

            __m256d b = _mm256_set_pd(
                t2->values[i],
                t2->values[i+1],
                t2->values[i+2],
                t2->values[i+3]
            );

            /* add vecs */
            __m256d result = _mm256_sub_pd(a, b);

            /* copy result segment to tensor */
            result_value->values[i] = result[3];
            result_value->values[i+1] = result[2];
            result_value->values[i+2] = result[1];
            result_value->values[i+3] = result[0];
        }
    }

    return result_value;
}


ndarray_t *nscale_add(ndarray_t *a, ndarray_t *b) {

    if(a->size % b->size != 0){
        printf(
            "Tensor size mismatch, %d % %d != 0",
            a->size, b->size
        );
    }

    /* create temp result */
    ndarray_t *result_value = ndarray(a->rank, a->shape);

    int counter = 0; 
    for(int i = 0; i < a->size; i++){

        if(counter == b->size){
            counter = 0; 
        }

        __m256d a1 = _mm256_set1_pd(a->values[i]);
        __m256d b1 = _mm256_set1_pd(b->values[counter]);
        __m256d result = _mm256_add_pd(a1, b1);
        result_value->values[i] = result[0]; 
        counter += 1; 
    }

    return result_value;
}


ndarray_t *ntranspose(ndarray_t *t) {

    /* vector list to keep track of which indices have been modifed */
    int *check = malloc(t->size * sizeof(int));
    int *new_shape = malloc(t->rank * sizeof(int));

    /* change shape of n dim array */
    int counter = 0; 
    for(int i = t->rank-1; i >= 0; i--){
        new_shape[counter] = t->shape[i];
        counter += 1; 
    }

    ndarray_t *result = ndarray(t->rank, new_shape);  

    /* generate indices for our current dimension + shape */
    int index = 0;
    for(int i = 0; i < t->size; i++){
        int *idxs = indices(t, index);
        int *reversed = malloc(t->rank * sizeof(int)); 
        int counter = 0; 

        /* generate reversed indices */
        for(int j = t->rank-1; j >= 0; j--){
            reversed[counter] = idxs[j];
            counter += 1; 
        } 

        double val = nidx(t, idxs);
        nset(result, reversed, val);
        index += 1; 
    }

    return result; 
}
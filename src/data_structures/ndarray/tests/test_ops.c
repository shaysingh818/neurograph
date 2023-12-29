#include "includes/test_ops.h"


void test_add_tensor() {

    ndarray_t *t1 = ndarray(2, (int[]){3, 3}); 
    ndarray_t *t2 = ndarray(2, (int[]){3, 3}); 

    double vals[] = {
        1.0, 2.0, 3.0,
        4.0, 5.0, 6.0,
        7.0, 8.0, 9.0
    };

    double expected[] = {
        2.00, 4.00, 6.00,
        8.00, 10.00, 12.00,
        14.00, 16.00, 18.00
    };

    int index = 0;
    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++){
            nset(t1, (int[]){i, j}, vals[index]);
            nset(t2, (int[]){i, j}, vals[index]);
            index += 1;  
        }
    }

    /* call add operation */
    ndarray_t *result = nadd(t1, t2);
    for(int i = 0; i < t1->size; i++){
        assert(result->values[i] == expected[i]); 
    }

    printf("%s::%s... \e[0;32mPASSED\e[0m\n", __FILE__, __FUNCTION__);
} 


void test_subtract_tensor() {

    ndarray_t *m1 = ndarray(2, (int[]){3, 3}); 
    ndarray_t *m2 = ndarray(2, (int[]){3, 3}); 

    double m1_values[] = {
        2, 2, 2, 
        2, 2, 2, 
        4, 4, 4
    };


    double m2_values[] = {
        4, 4, 4, 
        4, 4, 4, 
        5, 5, 5
    };


    double expected_values[] = {
        2.00, 2.00, 2.00, 
        2.00, 2.00, 2.00, 
        1.00, 1.00, 1.00
    };

    /* copy values to matrix */
    int index = 0; 
    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++){
            nset(m1, (int[]){i, j}, m1_values[index]);
            nset(m2, (int[]){i, j}, m2_values[index]);
            index += 1; 
        }
    }

    ndarray_t *result = nsubtract(m2, m1); 

    /* match result */
    index = 0; 
    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++){
            double rounded_value = round(result->values[index]*100)/100; 
            assert(expected_values[index] == rounded_value); 
            index += 1; 

        }
	}

    printf("%s::%s... \e[0;32mPASSED\e[0m\n", __FILE__, __FUNCTION__);

}


void test_scale_add_tensor() {


    double m_values[] = {
        0, 0, 0, 
        2, 2, 2, 
        2, 2, 2, 
        4, 4, 4, 
    };

    double biase_values[] = {
        1, 1, 1, 
    };


    double expected_values[] = {
        1, 1, 1, 
        3, 3, 3, 
        3, 3, 3, 
        5, 5, 5 
    };


    ndarray_t *t1 = ndarray(2, (int[]){4, 3}); 
    ndarray_t *t2 = ndarray(2, (int[]){1, 3});

    /* set values  */
    for(int i = 0; i < t1->size; i++){
        t1->values[i] = m_values[i];
    }

    for(int i = 0; i < t2->size; i++){
        t2->values[i] = biase_values[i];
    }

    ndarray_t *result =  nscale_add(t1, t2); 

    for(int i = 0; i < t1->size; i++){
        assert(result->values[i] == expected_values[i]);
    }


    double mvalues[] = {
        0, 0, 0, 0, 0, 
        2, 2, 2, 2, 2, 
        2, 2, 2, 2, 2, 
        4, 4, 4, 4, 4 
    };

    double b_values[] = {
        1, 1, 1, 1, 1
    };


    double exp_values[] = {
        1, 1, 1, 1, 1, 
        3, 3, 3, 3, 3, 
        3, 3, 3, 3, 3,
        5, 5, 5, 5, 5
    };


    ndarray_t *t3 = ndarray(2, (int[]){4, 5}); 
    ndarray_t *t4 = ndarray(2, (int[]){1, 5});


    /* set values  */
    for(int i = 0; i < t3->size; i++){
        t3->values[i] = mvalues[i];
    }

    for(int i = 0; i < t4->size; i++){
        t4->values[i] = b_values[i];
    }

    ndarray_t *result_two = nscale_add(t3, t4);

    for(int i = 0; i < t1->size; i++){
        assert(result_two->values[i] == exp_values[i]);
    }

    printf("%s::%s... \e[0;32mPASSED\e[0m\n", __FILE__, __FUNCTION__);
}


void test_tensor_dot_product() {

    ndarray_t *t1 = ndarray(2, (int[]){6, 6}); 
    ndarray_t *t2 = ndarray(2, (int[]){6, 6});

    double m_values[] = {
        2, 0, 0, 0, 0, 0, 
        0, 2, 0, 0, 0, 0,
        0, 0, 2, 0, 0, 0,
        0, 0, 0, 2, 0, 0,
        0, 0, 0, 0, 2, 0,
        0, 0, 0, 0, 0, 2
    };

    double m2_values[] = {
        3, 0, 0, 0, 0, 0, 
        0, 3, 0, 0, 0, 0,
        0, 0, 3, 0, 0, 0,
        0, 0, 0, 3, 0, 0,
        0, 0, 0, 0, 3, 0,
        0, 0, 0, 0, 0, 3
    };

    double expected_values[] = {
        6, 0, 0, 0, 0, 0, 
        0, 6, 0, 0, 0, 0,
        0, 0, 6, 0, 0, 0,
        0, 0, 0, 6, 0, 0,
        0, 0, 0, 0, 6, 0,
        0, 0, 0, 0, 0, 6,
    };

    /* set values  */
    for(int i = 0; i < t1->size; i++){
        t1->values[i] = m_values[i];
    }

    for(int i = 0; i < t2->size; i++){
        t2->values[i] = m2_values[i];
    }

    ndarray_t *result =  ndot(t1, t2);
    for(int i = 0; i < t1->size; i++){
        assert(expected_values[i] == result->values[i]);
    }

    /* specific case where matrix returns 0's*/
    double m3_values[] = {
        0.07, 
        0.07, 
        0.07, 
        0.07, 
    };

    double m4_values[] = {
        -0.23, 0.31, -0.42 
    };

    double expected_m3_values[] = {
        -0.02, 0.02, -0.03, 0.00 
    };

    ndarray_t *t3 = ndarray(2, (int[]){4, 1}); 
    ndarray_t *t4 = ndarray(2, (int[]){1, 3});

    /* set values  */
    for(int i = 0; i < t3->size; i++){
        t3->values[i] = m3_values[i];
    }

    for(int i = 0; i < t4->size; i++){
        t4->values[i] = m4_values[i];
    }

    result = ndot(t3, t4);
    for(int i = 0; i < t3->size; i++){
        assert(fabs(result->values[i] == expected_m3_values[i]) < 1e-6);
    }

    printf("%s::%s... \e[0;32mPASSED\e[0m\n", __FILE__, __FUNCTION__);
}


void test_tensor_transpose() {

    double m_values[] = {
        1, 2, 3, 4, 5, 6, 
        1, 2, 3, 4, 5, 6,
        0, 0, 2, 0, 0, 0,
        0, 0, 0, 2, 0, 0,
        0, 0, 0, 0, 2, 0,
        0, 0, 0, 0, 0, 2
    };

    double expected_values[] = {
        1, 1, 0, 0, 0, 0, 
        2, 2, 0, 0, 0, 0,
        3, 3, 2, 0, 0, 0,
        4, 4, 0, 2, 0, 0,
        5, 5, 0, 0, 2, 0,
        6, 6, 0, 0, 0, 2
    };

    ndarray_t *t1 = ndarray(2, (int[]){6, 6}); 
    for(int i = 0; i < t1->size; i++){
        t1->values[i] = m_values[i];
    }


    ndarray_t *result = ntranspose(t1);

    int index = 0; 
    for(int i = 0; i < 6; i++){
        for(int j = 0; j < 6; j++){
            double value = nidx(result, (int[]){i, j}); 
            assert(value == expected_values[index]); 
            index += 1; 
        }
    }

    // non sqaure matrix transpose
    double m2_values[] = {
        1, 2, 3, 
        1, 2, 3,
        0, 0, 2,
        0, 0, 0
    };

    double expected_values_2[] = {
        1, 1, 0, 0,
        2, 2, 0, 0,
        3, 3, 2, 0
    };

    ndarray_t *t2 = ndarray(2, (int[]){4, 3}); 
    for(int i = 0; i < t2->size; i++){
        t2->values[i] = m2_values[i];
    }

    result = ntranspose(t2);
    assert(result->shape[0] == 3 && result->shape[1] == 4);

    index = 0; 
    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 4; j++){
            double value = nidx(result, (int[]){i, j});
            assert(value == expected_values_2[index]);
            index += 1; 
        }
    }

    printf("%s::%s... \e[0;32mPASSED\e[0m\n", __FILE__, __FUNCTION__);
} 
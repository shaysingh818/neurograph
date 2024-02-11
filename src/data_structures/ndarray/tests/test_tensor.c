#include "includes/test_tensor.h" 


void test_ndimensional_index() {

    /* 2 dimensional test case */
    ndarray_t *t = ndarray(2, (int[]){3, 3});

    int index = 0; 
    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++){
            int test_index =  nindex(t, (int[]){i, j});
            assert(test_index == index);    
            index += 1;     
        }
    }

    ndarray_t *t_2d = ndarray(2, (int[]){6, 6});

    index = 0; 
    for(int i = 0; i < 6; i++){
        for(int j = 0; j < 6; j++){
            int test_index =  nindex(t_2d, (int[]){i, j});
            assert(test_index == index);    
            index += 1;     
        }
    }

    /* 3d tensor */
    ndarray_t *t_3d = ndarray(3, (int[]){3, 3, 3});

    index = 0; 
    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++){
            for(int k = 0; k < 3; k++){
                int test_index =  nindex(t_3d, (int[]){i, j, k});
                assert(test_index == index);    
                index += 1;     
            }
        }
    }

    /* lets get crazy with it */
    ndarray_t *t_4d = ndarray(4, (int[]){3, 3, 3, 3});

    index = 0; 
    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++){
            for(int k = 0; k < 3; k++){
                for(int l = 0; l < 3; l++){
                    int test_index =  nindex(t_4d, (int[]){i, j, k, l});
                    assert(test_index == index);    
                    index += 1;     
                }
            }
        }
    }

    printf("%s::%s... \e[0;32mPASSED\e[0m\n", __FILE__, __FUNCTION__);
}


void test_get_tensor_indices(){

    ndarray_t *t = ndarray(2, (int[]){3, 3});

    int index = 0; 
    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++){
            nset(t, (int[]){i, j}, index+1);
            index += 1;     
        }
    }

    /* 2d test case */
    index = 0;
    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++){
            int *idxs = indices(t, index); 
            assert(idxs[0] == i);
            assert(idxs[1] == j);  
            index += 1; 
        }
    }


    /* 3d test case */
    ndarray_t *t3 = ndarray(3, (int[]){3, 3, 3});

    index = 0;
    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++){
            for(int k = 0; k < 3; k++){
                int *idxs = indices(t3, index);
                assert(idxs[0] == i);
                assert(idxs[1] == j); 
                assert(idxs[2] == k);
                index += 1; 
            }
        }
    }

    /* 4d test case */
    ndarray_t *t4 = ndarray(4, (int[]){3, 3, 3, 3});

    index = 0;
    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++){
            for(int k = 0; k < 3; k++){
                for(int l = 0; l < 3; l++){
                    int *idxs = indices(t4, index);
                    assert(idxs[0] == i);
                    assert(idxs[1] == j); 
                    assert(idxs[2] == k); 
                    assert(idxs[3] == l);
                    index += 1; 
                }
            }
        }
    }

    printf("%s::%s... \e[0;32mPASSED\e[0m\n", __FILE__, __FUNCTION__);

}


void test_set_tensor() {

    /* 2 dimensional test case */
    ndarray_t *t = ndarray(2, (int[]){3, 3});

    /* expected values */
    double expected_vals[] = {
        1.00, 2.00, 3.00, 
        4.00, 5.00, 6.00,
        7.00, 8.00, 9.00
    };


    int index = 0; 
    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++){
            nset(t, (int[]){i, j}, index+1);
            double value = nidx(t, (int[]){i, j}); 
            assert(value == expected_vals[index]); 
            index += 1; 
        }
    }

    /* 3d tensor */
    ndarray_t *t2 = ndarray(3, (int[]){3, 3, 3});

    /* expected values */
    double expected_vals_3d[] = {
        1.00, 2.00, 3.00, 
        4.00, 5.00, 6.00,
        7.00, 8.00, 9.00,
        10.00, 11.00, 12.00,
        13.00, 14.00, 15.00,
        16.00, 17.00, 18.00,
        19.00, 20.00, 21.00,
        22.00, 23.00, 24.00,
        25.00, 26.00, 27.00
    };

    index = 0; 
    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++){
            for(int k = 0; k < 3; k++){
                nset(t2, (int[]){i, j, k}, index+1);
                double value = nidx(t2, (int[]){i, j, k}); 
                assert(value == expected_vals_3d[index]); 
                index += 1; 
            }
        }
    }
    printf("%s::%s... \e[0;32mPASSED\e[0m\n", __FILE__, __FUNCTION__);
} 


void test_reshape() {

    /* fill tensor with dummy values */
    int row = 3, col= 4; 
    ndarray_t *t = ndarray(2, (int[]){row, col});
    int expected_vals[] = {6, 2}; 

    int index = 1; 
    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 4; j++){
            double temp_val = index*2; 
            nset(t, (int[]){i, j}, temp_val);
            index +=  1;
        }
    }

    /* grab 24, 14, 8 and 2 with old and new reshaped tensor */ 
    double t1_val_1 = nidx(t, (int[]){0, 0}); 
    double t1_val_2 = nidx(t, (int[]){0, 3});
    double t1_val_3 = nidx(t, (int[]){1, 2});
    double t1_val_4 = nidx(t, (int[]){2, 3}); 

    int *vals = reshape(t, 2, (int[]){6, 2});  
    for(int i = 0; i < t->rank; i++){
        assert(vals[i] == expected_vals[i]); 
    }

    double t2_val_1 = nidx(t, (int[]){0, 0}); 
    assert(t2_val_1 == t1_val_1);  

    double t2_val_2 = nidx(t, (int[]){1, 1});
    assert(t1_val_2 == t2_val_2); 

    double t2_val_3 = nidx(t, (int[]){3, 0});
    assert(t2_val_3 == t1_val_3); 

    double t2_val_4 = nidx(t, (int[]){5, 1});
    assert(t2_val_4 == t1_val_4); 

    printf("%s::%s... \e[0;32mPASSED\e[0m\n", __FILE__, __FUNCTION__);
}


void test_tensor_apply() {

    /* fill tensor with dummy values */
    int row = 3, col= 4; 
    ndarray_t *t = ndarray(2, (int[]){row, col});

    
}


void test_save_tensor() {

    char *filepath = "../../../examples/data/saved_ndarray"; 
    bool equality_status = true; 
    int dims = 3; 
    ndarray_t *m = ndarray(2, (int[]){dims, dims});  

    double m_values[] = {
        1.00,2.00,3.00, 
        1.00,2.00,3.00,
        1.00,2.00,3.00
    };

    /* copy values to matrice */
    int index = 0; 
    for(int i = 0; i < dims; i++){
        for(int j = 0; j < dims; j++){
            m->values[index] = m_values[index];
            index += 1; 
        }
    }

    /* save matrix instance in file */
    save_ndarray(m, filepath);
    ndarray_t *t = load_ndarray(filepath);

    index = 0; 
    for(int i = 0; i < dims; i++){
        for(int j = 0; j < dims; j++){
            assert(t->values[index] == m_values[index]); 
            index += 1; 
        }
    }

    /* remove file */
    system("rm ../../../examples/data/saved_ndarray"); 
    printf("%s::%s... \e[0;32mPASSED\e[0m\n", __FILE__, __FUNCTION__);
}


void test_get_rows() {

    int dims = 3; 
    ndarray_t *m = ndarray(2, (int[]){dims, dims});  

    double m_values[] = {
        1.00,2.00,3.00, 
        1.00,2.00,3.00,
        1.00,2.00,3.00
    };

    /* copy values to matrice */
    int index = 0; 
    for(int i = 0; i < dims; i++){
        for(int j = 0; j < dims; j++){
            m->values[index] = m_values[index];
            index += 1; 
        }
    }

    /* get first row */
    index = 0; 
    double *first_row = rows(m, 0); 
    for(int i = 0; i < dims; i++){
        assert(first_row[i] == m_values[index]);
        index += 1; 
    }

    double *second_row = rows(m, 1); 
    for(int i = 0; i < dims; i++){
        assert(second_row[i] == m_values[index]);
        index += 1; 
    }

    /* get last row */
    double *last_row = rows(m, 2); 
    for(int i = 0; i < dims; i++){
        assert(last_row[i] == m_values[index]);
        index += 1; 
    }

    printf("%s::%s... \e[0;32mPASSED\e[0m\n", __FILE__, __FUNCTION__);
} 



void test_get_cols() {

    int dims = 3; 
    ndarray_t *m = ndarray(2, (int[]){dims, dims});  

    double m_values[] = {
        1.00,2.00,3.00, 
        1.00,2.00,3.00,
        1.00,2.00,3.00
    };

    /* copy values to matrice */
    int index = 0; 
    for(int i = 0; i < dims; i++){
        for(int j = 0; j < dims; j++){
            m->values[index] = m_values[index];
            index += 1; 
        }
    }

    /* get first col */
    double first_expected[] = {1.00, 1.00, 1.00}; 
    double *first_col = cols(m, 0); 
    for(int i = 0; i < dims; i++){
        assert(first_col[i] == first_expected[i]);
    }

    /* get secondd col */
    double second_expected[] = {2.00, 2.00, 2.00}; 
    double *second_col = cols(m, 1); 
    for(int i = 0; i < dims; i++){
        assert(second_col[i] == second_expected[i]);
    }

    /* get third col */    
    double third_expected[] = {3.00, 3.00, 3.00}; 
    double *third_col = cols(m, 2); 
    for(int i = 0; i < dims; i++){
        assert(third_col[i] == third_expected[i]);
    }

    printf("%s::%s... \e[0;32mPASSED\e[0m\n", __FILE__, __FUNCTION__);
}
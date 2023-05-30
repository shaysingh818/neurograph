#include "includes/test_computation_graph.h"


void test_linear() {

    bool equality_status = true; 
    int node_count = 2; 

    /* create linear node */
    int inputs[4][2] = {
        {0,0},
        {0,1},
        {1,0},
        {1,1}
    };

    int outputs[4][1] = {
        {0},
        {1},
        {1},
        {0}
    };

    /* create x input */
    mat_t *x = init_vec(4, 2, false); 
    mat_t *y = init_vec(4, 1, false);
     

    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 2; j++){
            x->arr[i][j] = inputs[i][j]; 
        }

        for(int n = 0; n < 1; n++){
            y->arr[i][n] = outputs[i][n];
        }
    }

    /* first layer */
    linear_t *l1 = linear(x, 2, 3);
    l1->node->forward(l1); 

    loss_t *loss1 = loss(l1->node->outputs, 2, 3, tanh, tanh_prime);
    loss1->node->forward(loss1); 

    /* second layer */
    linear_t *l2 = linear(loss1->node->outputs, 3, 1);
    loss_t *loss2 = loss(l2->node->outputs, 3, 1, tanh, tanh_prime);

    void *nodes[4] = {
        l1, loss1, l2, loss2
    };

    /* forward all of them */





}
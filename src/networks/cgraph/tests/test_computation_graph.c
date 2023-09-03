#include "includes/test_computation_graph.h"
#include "../includes/ops.h"

void test_create_graph() {

    computation_graph_t *graph = create_graph(3, 1.00); 
    assert(graph->curr_index == 0); 
    assert(graph->size == 3); 
    for(int i = 0; i < graph->size; i++){
        assert(graph->operations[i] != NULL); 
    }   

    printf("%s::%s... \e[0;32mPASSED\e[0m\n", __FILE__, __FUNCTION__);

}


void test_append_operation() {

    computation_graph_t *graph = create_graph(2, 1.00);

    /* expression */
    value_t *x = input_node(-2.00); 
    value_t *y = input_node(5.00);
    value_t *z = input_node(-4.00);

    /* e = (a+b)*(b+1) */
    value_t *q = node_op(
        x, y, 
        add_node, 
        backward_add_node
    ); 

    value_t *f = node_op(
        q, z, 
        multiply_node, 
        backward_mult_node
    );

    append_op(graph, q);
    assert(graph->curr_index == 1); 

    append_op(graph, f);
    assert(graph->curr_index == 2);

    double expected_vals[2] = {3.00, -12.00};  

    /* forward */
    for(int i = 0; i < graph->curr_index; i++){
        value_t *op = graph->operations[i];
        op->forward_operation(op);
        assert(op->output == expected_vals[i]); 
    }

    printf("%s::%s... \e[0;32mPASSED\e[0m\n", __FILE__, __FUNCTION__);

}


void test_forward_nodes() {

    computation_graph_t *graph = create_graph(2, 1.00);

    /* expression */
    value_t *x = input_node(-2.00); 
    value_t *y = input_node(5.00);
    value_t *z = input_node(-4.00);

    /* e = (a+b)*(b+1) */
    value_t *q = node_op(
        x, y, 
        add_node, 
        backward_add_node
    );
    assert(q->output == 0.00); 

    value_t *f = node_op(
        q, z, 
        multiply_node, 
        backward_mult_node
    );
    assert(f->output == 0.00); 

    append_op(graph, q); 
    append_op(graph, f);
    forward_nodes(graph); 

    assert(q->output == 3.00); 
    assert(f->output == -12.00);  

    printf("%s::%s... \e[0;32mPASSED\e[0m\n", __FILE__, __FUNCTION__);
}


void test_backward_nodes() {

    computation_graph_t *graph = create_graph(2, 1.00);

    /* expression */
    value_t *x = input_node(-2.00); 
    value_t *y = input_node(5.00);
    value_t *z = input_node(-4.00);

    /* e = (a+b)*(b+1) */
    value_t *q = node_op(
        x, y, 
        add_node, 
        backward_add_node
    );
    assert(q->output == 0.00); 

    value_t *f = node_op(
        q, z, 
        multiply_node, 
        backward_mult_node
    );
    assert(f->output == 0.00); 

    append_op(graph, q); 
    append_op(graph, f);
    forward_nodes(graph); 

    assert(q->output == 3.00); 
    assert(f->output == -12.00); 

    backward_nodes(graph);

    assert(f->x_d_gradient == -4.00);  
    assert(f->y_d_gradient == 3.00); 

    assert(q->x_d_gradient == -4.00);  
    assert(q->y_d_gradient == -4.00);  


    printf("%s::%s... \e[0;32mPASSED\e[0m\n", __FILE__, __FUNCTION__);
}
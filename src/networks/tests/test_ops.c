#include "includes/test_ops.h"

void test_add_operation() {

    node_value_t *a = input_node(2.00); 
    node_value_t *b = input_node(1.00);

    /* e = (a+b)*(b+1) */
    node_value_t *c = node_op(
        a, b, 
        add_node, 
        backward_add_node
    );
    c->forward_operation(c); 

    assert(a->output == 2.00); 
    assert(b->output == 1.00); 
    assert(c->output == 3.00);

    c->upstream_gradient = 1.00; 
    c->backward_operation(c);
    assert(c->x_d_gradient == 1.00); 
    assert(c->y_d_gradient == 1.00); 

    printf("%s::%s... \e[0;32mPASSED\e[0m\n", __FILE__, __FUNCTION__);
}


void test_multiply_operation() {

    node_value_t *a = input_node(3.00); 
    node_value_t *b = input_node(2.00);

    // /* e = (a+b)*(b+1) */
    node_value_t *c = node_op(
        a, b, 
        multiply_node, 
        backward_mult_node
    );
    c->forward_operation(c); 

    assert(a->output == 3.00); 
    assert(b->output == 2.00); 
    assert(c->output == 6.00);

    c->upstream_gradient = 1.00; 
    c->backward_operation(c);
    assert(c->x_d_gradient == 2.00); 
    assert(c->y_d_gradient == 3.00); 

    printf("%s::%s... \e[0;32mPASSED\e[0m\n", __FILE__, __FUNCTION__);
}


void test_expression() {


    computation_graph_t *graph = create_graph(8, 1.00); 

    node_value_t *w0 = input_node(2.00); 
    node_value_t *x0 = input_node(-1.00);

    node_value_t *w1 = input_node(-3.00); 
    node_value_t *x1 = input_node(-2.00);

    node_value_t *w2 = input_node(-3.00); 

    /* e = (a+b)*(b+1) */
    node_value_t *c = node_op(
        w0, x0, 
        multiply_node, 
        backward_mult_node
    );

    node_value_t *d = node_op(
        w1, x1, 
        multiply_node, 
        backward_mult_node
    );

    node_value_t *e = node_op(
        c, d, 
        add_node, 
        backward_add_node
    );

    node_value_t *f = node_op(
        e, w2, 
        add_node, 
        backward_add_node
    );


    node_value_t *g = node_op(
        f, NULL, 
        eulers, 
        backward_mult_node
    );


    node_value_t *h = node_op(
        g, NULL, 
        exponent, 
        backward_mult_node
    );


    append_op(graph, c); 
    append_op(graph, d);
    append_op(graph, e);      
    append_op(graph, f); 
    append_op(graph, g); 
    append_op(graph, h);  
    forward_nodes(graph);     



}
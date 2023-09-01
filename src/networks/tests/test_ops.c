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

    /* expression */
    node_value_t *weights = adder(
        graph,
        adder(
            graph,
            mult(graph, w1, x1),
            mult(graph, w0, x0) 
        ),
        w2
    );

    node_value_t *left_exp = recip(
        graph,
        add_one(
            graph, 
            expnt(
                graph,
                euler(graph, weights)
            )
        )
    );   

    forward_nodes(graph); 
    backward_nodes(graph);  


    node_value_t *one = graph->operations[graph->curr_index-1]; 
    assert(round(one->x_d_gradient * 100) / 100 == -0.53);

    node_value_t *two = graph->operations[graph->curr_index-2]; 
    assert(round(two->x_d_gradient * 100) / 100 == -0.53);  

    node_value_t *three = graph->operations[graph->curr_index-3]; 
    assert(round(three->x_d_gradient * 100) / 100 == -0.20);

    node_value_t *four = graph->operations[graph->curr_index-4]; 
    assert(round(four->x_d_gradient * 100) / 100 == 0.20);

    node_value_t *five = graph->operations[graph->curr_index-5]; 
    assert(round(five->x_d_gradient * 100) / 100 == 0.20); 
    assert(round(five->y_d_gradient * 100) / 100 == 0.20); 

    node_value_t *six = graph->operations[graph->curr_index-6]; 
    assert(round(six->x_d_gradient * 100) / 100 == 0.20); 
    assert(round(six->y_d_gradient * 100) / 100 == 0.20); 

    node_value_t *seven = graph->operations[graph->curr_index-7]; 
    assert(round(seven->x_d_gradient * 100) / 100 == -0.39); 
    assert(round(seven->y_d_gradient * 100) / 100 == -0.59); 

    node_value_t *eight = graph->operations[graph->curr_index-8]; 
    assert(round(eight->x_d_gradient * 100) / 100 == -0.20); 
    assert(round(eight->y_d_gradient * 100) / 100 == 0.39); 

}


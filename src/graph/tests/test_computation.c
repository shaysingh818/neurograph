#include "includes/test_computation.h"


void test_computation_graph() {

    computation_graph_t *g = computation_graph(1.0);
    assert(g->curr_node_count == 3); 
    assert(g->curr_node_id == 0); 
    assert(g->base_derivative == 1.00); 

    /* test node id logic */
    variable(g, _double(1)); 
    variable(g, _double(1)); 
    variable(g, _double(1)); 

    assert(g->curr_node_id == 3);    

    variable(g, _double(1)); 
    variable(g, _double(1)); 

    assert(g->curr_node_id == 5);   

		printf("%s::%s...  \e[0;32mPASSED\e[0m\n", __FILE__, __FUNCTION__); 
} 


void test_add_variable() {

    computation_graph_t *g = computation_graph(1.0);
    assert(g->curr_node_count == 3); 
    assert(g->curr_node_id == 0); 
    assert(g->base_derivative == 1.00);
    assert(g->graph->vertices == 3);
    assert(g->graph->list->v == 3);  

    /* create variables */
    node_t *x = variable(g, _double(1));
    node_t *y = variable(g, _double(1));
    node_t *z = variable(g, _double(1));

    /* children vars */
    node_t *a = variable(g, _double(4)); 
    node_t *b = variable(g, _double(5)); 
    node_t *c = variable(g, _double(6));
    node_t *d = variable(g, _double(6));

    add_variable(g, x, a);
    add_variable(g, x, b);
    add_variable(g, x, c);

    assert(g->curr_node_count == 3);
    assert(g->graph->vertices == 3);
    assert(g->graph->list->v == 3);  

    add_variable(g, a, y);
    add_variable(g, b, y);
    add_variable(g, c, y);
    add_variable(g, d, y);
    add_variable(g, a, z);

    assert(g->curr_node_count == 12);
    assert(g->graph->vertices == 12); 
    assert(g->graph->list->v == 12);
    assert(g->curr_node_id == 7);

		printf("%s::%s...  \e[0;32mPASSED\e[0m\n", __FILE__, __FUNCTION__); 
}



void test_forward_evaluate() {

  	int vertices = 5; // num of vertices
    int edges = 8; // num of edges
    computation_graph_t *g = computation_graph(1.0);

    /* perform operation */
    node_t *a = _add(
      g, 
      (node_t*[]){
        variable(g, _double(3)),
        variable(g, _double(3)),
        variable(g, _double(3)),
      }, 
      3 // amount of inputs we're passing
    );

    node_t *b = _multiply(
      g, 
      (node_t*[]){
        variable(g, _double(3)),
        variable(g, _double(4)),
      }, 
      2 // amount of inputs we're passing
    );

    node_t *c = _add(
      g, 
      (node_t*[]){
        variable(g, _double(5)),
        variable(g, _double(6)),
      }, 
      2 // amount of inputs we're passing
    );

    node_t *d = _multiply(g, (node_t*[]){a, b}, 2);
    node_t *e = _add(g, (node_t*[]){d, c}, 2);
    node_t *f = _tanh(g, (node_t*[]){e}, 1);
    forward_evaluate(g, f);

    scalar_t *a_output = (scalar_t*)a->node_type->variable->output;
    scalar_t *b_output = (scalar_t*)b->node_type->variable->output;
    scalar_t *d_output = (scalar_t*)d->node_type->variable->output;
    scalar_t *e_output = (scalar_t*)e->node_type->variable->output;

    assert(a_output->value->_double == 9.00); 
    assert(b_output->value->_double == 12.00); 
    assert(d_output->value->_double == 108.00); 
    assert(e_output->value->_double == 1.00);

		printf("%s::%s...  \e[0;32mPASSED\e[0m\n", __FILE__, __FUNCTION__); 
}
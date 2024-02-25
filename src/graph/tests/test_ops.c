#include "includes/test_ops.h"


void test_scalar_add() {

    computation_graph_t *g = computation_graph(1.0);
    assert(g->curr_node_count == 3); 
    assert(g->curr_node_id == 0); 
    assert(g->base_derivative == 1.00);
    assert(g->graph->vertices == 3);
    assert(g->graph->list->v == 3);  

    node_t *add_operation = _add(
      g, 
      (node_t*[]){
        variable(g, _double(1)),
        variable(g, _double(2)),
      }, 
      2 
    );

    assert(add_operation->id == 2); 
    assert(strcmp(add_operation->node_type->variable->label, "S_ADD") == 0);

    void *value = add_operation->node_type->variable->forward((void*)g, add_operation->id); 
    add_operation->node_type->variable->output = value;
    scalar_t *output = (scalar_t*)add_operation->node_type->variable->output;  
    assert(output->value->_double == 3.00);


    node_t *add_operation_2 = _add(
      g, 
      (node_t*[]){
        variable(g, _double(1)),
        variable(g, _double(2)),
        variable(g, _double(3)),
        variable(g, _double(4)),
      }, 
      4 
    );

    void *value_2 = add_operation_2->node_type->variable->forward((void*)g, add_operation_2->id); 
    add_operation_2->node_type->variable->output = value_2;
    scalar_t *output_2 = (scalar_t*)add_operation_2->node_type->variable->output;  
    assert(output_2->value->_double == 10.00);
    assert(add_operation_2->id == 7); 
    assert(strcmp(add_operation_2->node_type->variable->label, "S_ADD") == 0);

		printf("%s::%s...  \e[0;32mPASSED\e[0m\n", __FILE__, __FUNCTION__); 
}


void test_scalar_multiply() {

    computation_graph_t *g = computation_graph(1.0);
    assert(g->curr_node_count == 3); 
    assert(g->curr_node_id == 0); 
    assert(g->base_derivative == 1.00);
    assert(g->graph->vertices == 3);
    assert(g->graph->list->v == 3); 

    node_t *mult_operation = _multiply(
      g, 
      (node_t*[]){
        variable(g, _double(1)),
        variable(g, _double(2)),
      }, 
      2 
    );

    void *value = mult_operation->node_type->variable->forward((void*)g, mult_operation->id); 
    mult_operation->node_type->variable->output = value;
    scalar_t *output = (scalar_t*)mult_operation->node_type->variable->output;  
    assert(output->value->_double == 2.00); 

    node_t *mult_operation_2 = _multiply(
      g, 
      (node_t*[]){
        variable(g, _double(1)),
        variable(g, _double(2)),
        variable(g, _double(3)),
      }, 
      3
    );

    assert(g->curr_node_count == 9); 
    assert(g->curr_node_id == 7); 
    assert(g->base_derivative == 1.00);
    assert(g->graph->vertices == 9);
    assert(g->graph->list->v == 9); 


    void *value_2 = mult_operation_2->node_type->variable->forward((void*)g, mult_operation_2->id); 
    mult_operation_2->node_type->variable->output = value_2;
    scalar_t *output_2 = (scalar_t*)mult_operation_2->node_type->variable->output; 
    assert(output_2->value->_double == 6.00); 
		printf("%s::%s...  \e[0;32mPASSED\e[0m\n", __FILE__, __FUNCTION__);  
}


void test_scalar_tanh() {

    computation_graph_t *g = computation_graph(1.0);
    assert(g->curr_node_count == 3); 
    assert(g->curr_node_id == 0); 
    assert(g->base_derivative == 1.00);
    assert(g->graph->vertices == 3);
    assert(g->graph->list->v == 3);  

    node_t *tanh_operation = _tanh(g, 
      (node_t*[]){
        variable(g, _double(0.40)), // unary op
      }, 
      1
    );

    void *value = tanh_operation->node_type->variable->forward((void*)g, tanh_operation->id); 
    tanh_operation->node_type->variable->output = value;
    scalar_t *output = (scalar_t*)tanh_operation->node_type->variable->output; 
    assert(output->value->_double != 0.40); 

		printf("%s::%s...  \e[0;32mPASSED\e[0m\n", __FILE__, __FUNCTION__); 
}


void test_nd_dot() {

    computation_graph_t *g = computation_graph(1.0);
    assert(g->curr_node_count == 3); 
    assert(g->curr_node_id == 0); 
    assert(g->base_derivative == 1.00);
    assert(g->graph->vertices == 3);
    assert(g->graph->list->v == 3);

    /* multidimensional inputs */
    ndarray_t *inputs = ndarray(2, (int[]){4, 2});
    ndarray_t *weights = ndarray(2, (int[]){2, 3});
    fill(inputs, 1); 
    fill(weights, 2); 

    node_t *nd_dot_op = nd_dot(g, 
      (node_t*[]){
        variable(g, inputs),
        variable(g, weights),
      }, 
      2
    );

    assert(g->curr_node_count == 3); 
    assert(g->curr_node_id == 3); 
    assert(g->base_derivative == 1.00);
    assert(g->graph->vertices == 3);
    assert(g->graph->list->v == 3);

    /* forward operation */
    void *value = nd_dot_op->node_type->variable->forward((void*)g, nd_dot_op->id);
    nd_dot_op->node_type->variable->output = value;
    ndarray_t *output = (ndarray_t*)nd_dot_op->node_type->variable->output;
    print_tensor(output);

		printf("%s::%s...  \e[0;32mPASSED\e[0m\n", __FILE__, __FUNCTION__); 

}
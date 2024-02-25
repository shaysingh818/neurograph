#include "includes/operations.h"


node_t *_add(computation_graph_t *g, node_t *inputs[], int inputs_size) {

    variable_t *var = malloc(sizeof(variable_t));
    var->value_destructor = NULL;
    var->output = 0;
    var->forward  = _add_forward;
    var->backward = NULL; 

    size_t name_size = strlen("S_ADD")+1;
    node_t *node = malloc(sizeof(node_t));
    node->node_type = malloc(sizeof(node_type_t));
    node->node_type->variable = var;
    node->node_type->variable->label = malloc(name_size * sizeof(char));
    strcpy(node->node_type->variable->label, "S_ADD");

    node->id = g->curr_node_id; 
    node->next = NULL;
    node->left = NULL; 
    node->right = NULL;
    g->curr_node_id += 1;

    /* add inputs */
    for(int i = 0; i < inputs_size; i++){
        add_variable(g, node, inputs[i]);
    }

    return node; 

}

void *_add_forward(void *graph, int node_id) {
    double sum = 0.0; 
    computation_graph_t *g = (computation_graph_t*)graph; 
    node_t *head = g->graph->list->items[node_id]->head;
    while(head) {
        scalar_t *value = (scalar_t*)head->node_type->variable->output;
        sum += value->value->_double;
        head = head->next; 
    }
    scalar_t *value = _double(sum);
    return (void*)value; 
}


node_t *_multiply(computation_graph_t *g, node_t *inputs[], int inputs_size) {

    variable_t *var = malloc(sizeof(variable_t));
    var->value_destructor = NULL;
    var->output = 0;
    var->forward  = _mult_forward;
    var->backward = NULL; 

    size_t name_size = strlen("S_MULT")+1;
    node_t *node = malloc(sizeof(node_t));
    node->node_type = malloc(sizeof(node_type_t));
    node->node_type->variable = var;
    node->node_type->variable->label = malloc(name_size * sizeof(char));
    strcpy(node->node_type->variable->label, "S_MULT");

    node->id = g->curr_node_id; 
    node->next = NULL;
    node->left = NULL; 
    node->right = NULL;
    g->curr_node_id += 1;

    /* add inputs */
    for(int i = 0; i < inputs_size; i++){
        add_variable(g, node, inputs[i]);
    }

    return node; 

}

void *_mult_forward(void *graph, int node_id) {
    double sum = 1.0;
    computation_graph_t *g = (computation_graph_t*)graph; 
    node_t *head = g->graph->list->items[node_id]->head;
    while(head) {
        scalar_t *value = (scalar_t*)head->node_type->variable->output;
        sum *= value->value->_double;
        head = head->next; 
    }
    scalar_t *value = _double(sum);
    return (void*)value; 
}


node_t *_tanh(computation_graph_t *g, node_t *inputs[], int inputs_size) {

    if(inputs_size > 1) {
        printf("TANH can only have 1 input\n"); 
        exit(0); 
    }

    variable_t *var = malloc(sizeof(variable_t));
    var->value_destructor = NULL;
    var->output = 0;
    var->forward  = _tanh_forward;
    var->backward = NULL; 

    size_t name_size = strlen("S_TANH")+1;
    node_t *node = malloc(sizeof(node_t));
    node->node_type = malloc(sizeof(node_type_t));
    node->node_type->variable = var;
    node->node_type->variable->label = malloc(name_size * sizeof(char));
    strcpy(node->node_type->variable->label, "S_TANH");

    node->id = g->curr_node_id; 
    node->next = NULL;
    node->left = NULL; 
    node->right = NULL;
    g->curr_node_id += 1;

    /* add inputs */
    for(int i = 0; i < inputs_size; i++){
        add_variable(g, node, inputs[i]);
    }

    return node; 
}


void *_tanh_forward(void *graph, int node_id) {
    computation_graph_t *g = (computation_graph_t*)graph; 
    node_t *head = g->graph->list->items[node_id]->head;
    scalar_t *value = (scalar_t*)head->node_type->variable->output;
    value->value->_double = tanh(value->value->_double);
    return (void*)value; 
}


node_t *nd_dot(computation_graph_t *g, node_t *inputs[], int inputs_size) {

    if(inputs_size > 2) {
        printf("Operation only takes two inputs (for now)\n"); 
        exit(0); 
    }

    variable_t *var = malloc(sizeof(variable_t));
    var->value_destructor = NULL;
    var->output = 0;
    var->forward  = dot_forward;
    var->backward = dot_backward; 

    size_t name_size = strlen("ND_DOT")+1;
    node_t *node = malloc(sizeof(node_t));
    node->node_type = malloc(sizeof(node_type_t));
    node->node_type->variable = var;
    node->node_type->variable->label = malloc(name_size * sizeof(char));
    strcpy(node->node_type->variable->label, "ND_DOT");

    node->id = g->curr_node_id; 
    node->next = NULL;
    node->left = NULL; 
    node->right = NULL;
    g->curr_node_id += 1;

    /* add inputs */
    for(int i = 0; i < inputs_size; i++){
        add_variable(g, node, inputs[i]);
    }

    return node; 
}


void *dot_forward(void *graph, int node_id) {
    computation_graph_t *g = (computation_graph_t*)graph; 
    node_t *head = g->graph->list->items[node_id]->head;

    node_t *first = head; 
    head = head->next; 
    node_t *second = head; 

    ndarray_t *left = (ndarray_t*)first->node_type->variable->output; 
    ndarray_t *right = (ndarray_t*)second->node_type->variable->output; 
    ndarray_t *result = ndot(left, right);
    return (void*)result; 
}


void *dot_backward(void *graph, int node_id) {

    computation_graph_t *g = (computation_graph_t*)graph; 
    node_t *head = g->graph->list->items[node_id]->head;

    ndarray_t *upstream = (ndarray_t*)head->node_type->variable->upstream_value; 
    node_t *first = head; 
    head = head->next; 
    node_t *second = head; 

    ndarray_t *left = (ndarray_t*)first->node_type->variable->output; 
    ndarray_t *right = (ndarray_t*)second->node_type->variable->output; 
    ndarray_t *left_grad = ndot(upstream, ntranspose(right));
    ndarray_t *right_grad = ndot(ntranspose(left), upstream);
    return (void*)upstream; 
}
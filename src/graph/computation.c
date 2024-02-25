#include "includes/computation.h"

node_t *variable(computation_graph_t *g, void *value) {

    variable_t *var = malloc(sizeof(variable_t));
    var->value_destructor = NULL;
    var->output = value;

    size_t name_size = strlen("variable")+1;
    node_t *node = malloc(sizeof(node_t));
    node->node_type = malloc(sizeof(node_type_t));
    node->node_type->variable = var;
    node->node_type->variable->label = malloc(name_size * sizeof(char));
    strcpy(node->node_type->variable->label, "variable");

    node->id = g->curr_node_id; 
    node->next = NULL;
    node->left = NULL; 
    node->right = NULL;
    g->curr_node_id += 1; 
    return node;
}

computation_graph_t *computation_graph(double base_derivative) {
	computation_graph_t *comp_graph = malloc(sizeof(computation_graph_t)); 
    comp_graph->curr_node_count = 3; 
    comp_graph->base_derivative = base_derivative;
    comp_graph->status = true; 
    comp_graph->graph = init_graph(
        comp_graph->curr_node_count, 
        comp_graph->curr_node_count, 
        false
    );
    return comp_graph;
}


void add_variable(computation_graph_t *g, node_t *operation, node_t *input) {

    int operation_id = operation->id;
    int input_id = input->id;

    if(operation_id >= g->curr_node_count || input_id >= g->curr_node_count){
        int new_size = g->curr_node_count + operation_id;
        g->graph->list->items = realloc(
            g->graph->list->items, 
            new_size * sizeof(node_obj_list_t*)
        );
        for(int i = g->curr_node_count; i < new_size; i++) {
            g->graph->list->items[i] = malloc(sizeof(node_obj_list_t));
            g->graph->list->items[i]->head = NULL; 
        }
        g->curr_node_count = new_size;
        g->graph->vertices = g->curr_node_count; 
        g->graph->list->v = g->curr_node_count; 
    }

    node_t *check = NULL; 
    adj_list_t *adj_list = g->graph->list; 
    if(adj_list->items[operation_id]->head == NULL) {
        input->next = adj_list->items[operation_id]->head;
        adj_list->items[operation_id]->head = input;
    } else {
        check = adj_list->items[operation_id]->head; 
        while(check->next != NULL){
            check = check->next; 
        }
        check->next = input;
    }

} 

void forward_evaluate(computation_graph_t *g, node_t *output) {

    for(int i = 0; i < output->id+1; i++){
        node_t *head = g->graph->list->items[i]->head;
        if(head != NULL) {
            if(strcmp(head->node_type->variable->label, "variable") != 0) {
                while(head) {
                    void *value = head->node_type->variable->forward((void*)g, head->id);
                    head->node_type->variable->output = value;
                    head  = head->next; 
                }
            }
        }
    }

    void *value = output->node_type->variable->forward((void*)g, output->id);
    output->node_type->variable->output = value;
}


void print_computation_graph(computation_graph_t *g) {
	for(int i = 0; i < g->graph->vertices; i++){
		node_t *head = g->graph->list->items[i]->head;
		printf("%d ", i);
		while(head) {
			printf(
                "-> (%d, %s)", 
                head->id, 
                head->node_type->variable->label
            ); 
			head  = head->next; 
		}
		printf("\n"); 
	}
}




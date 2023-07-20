#include "includes/gml.h"
#include "includes/re.h"

set_t *get_graph_nodes(char *filename, int file_size) {

	/* variables */
	FILE* fp = fopen(filename, "r");
   	int row_count = 0;
    char *head_label; 
    char* buffer = malloc(file_size * sizeof(char));
    node_t *head;
    set_t *node_set =  init_set(true); 


	while(fgets(buffer, file_size, fp)) {

		/* null terminate the buffer */ 
		int len = strlen(buffer); 
		if(buffer[len-1] == '\n') {
			buffer[len-1] = 0; 
		}

		/* extract tokens from regular expression */
		tokens_t *row_values = match_single(buffer, RE_GML); 
		int size = row_values->result_size;

        /* extract node */
		tokens_t *r_quotes = match_single(row_values->tokens[0], REMOVE_QUOTES); 
        char *node = r_quotes->tokens[0];
        insert_ordered(node_set, row_count, node, 0); 

        /* extract neighbors */
        for(int i = 1; i < size; i++){
		    r_quotes = match_single(row_values->tokens[i], REMOVE_QUOTES); 
            char *neighbor = r_quotes->tokens[0];
            insert_ordered(node_set, row_count, neighbor, 0); 
        }

		row_count += 1;
	}
    
    return node_set;
}


graph_t *serialize_graph_list(char *filename, int file_size) {

	/* variables */
	FILE* fp = fopen(filename, "r");
   	int row_count = 0;
    char *head_label; 
    char* buffer = malloc(file_size * sizeof(char));
    set_t *nodes = get_graph_nodes(filename, file_size); 
    graph_t *g = init_graph(nodes->count+1, nodes->count+1, false);


	while(fgets(buffer, file_size, fp)) {

		/* null terminate the buffer */ 
		int len = strlen(buffer); 
		if(buffer[len-1] == '\n') {
			buffer[len-1] = 0; 
		}

		/* extract tokens from regular expression */
		tokens_t *row_values = match_single(buffer, RE_GML); 
		int size = row_values->result_size;

        /* extract node */
		tokens_t *r_quotes = match_single(row_values->tokens[0], REMOVE_QUOTES); 
        char *node = r_quotes->tokens[0];

        /* add all nodes in graph to set */
        for(int i = 1; i < size; i++){

		    r_quotes = match_single(row_values->tokens[i], REMOVE_QUOTES); 
            char *neighbor = r_quotes->tokens[0];

            char *dst = neighbor;
            char *src = node;

            int dst_id = get_value_ordered(nodes, dst); 
            int src_id = get_value_ordered(nodes, src); 
            add_node(g->list, src_id, src, dst_id, dst, 0);

        }
		row_count += 1;
	}

    return g;
}


void deserialize_graph_list(graph_t *list, char *filename) {
    printf("De Serialize\n");
	FILE* fp = fopen(filename, "r");    
} 

graph_t *serialize_mat_graph(char *filename, int file_size) {
    printf("Serialize Mat\n");
}

void deserialize_mat_graph(graph_t *mat) {
    printf("De Serialize Mat\n");
} 
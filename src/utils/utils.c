#include "includes/utils.h"

adj_list_t *init_graph_util(int size, bool directed) {

	/* test first example of bfs */
    adj_list_t *g = init_graph(size, size, directed);
	if(g->err) {
		return FALSE; 
	}

	return g; 
}


int add_node_util(
	adj_list_t *g, int src_id, char *src, 
	int dst_id, char *dst, int weight) {

	/* do validation from here */ 
	if(src_id == dst_id) {
		printf("src and dest id can't be the same"); 
		return false; 
	}

	/* call method from c library */ 
	int status = add_node(g, src_id, src, dst_id, dst, weight); 
	if(!status) {
		return false; 
	}

	return true; 
}


adj_list_t *g_to_csv_util(char *filepath, int *features, int size, int row_limit){

	/* create instance of csv */ 
    csv_t *file = csv_init(filepath, FILE_BUFFER_SIZE, row_limit);
    if(!file->status) {
		printf("[+] YOUR FILE does not abide by CSV standards\n"); 
        exit(0);
    }

	/* test random walk */
	adj_list_t *g = csv_to_unweighted_graph(file, features, size, false);
	if(g->err) {
		g->err = true; 
	}

	return g; 
}


void free_graph(adj_list_t *g) {
	free(g); 
}


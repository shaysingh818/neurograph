#include "includes/utils.h"

graph_t *init_graph_util(int size, bool directed) {

	/* test first example of bfs */
    graph_t *g = init_graph(size, size, directed);
	if(g->err) {
		return FALSE; 
	}

	return g; 
}


int add_node_util(
	graph_t *g, int src_id, char *src, 
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

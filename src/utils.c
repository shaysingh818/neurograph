#include "includes/utils.h"

graph_t *init_graph_util(int size) {

	/* test first example of bfs */
    graph_t *g = init_graph(size, size, false);
	if(g->err) {
		return FALSE; 
	}

	printf("Testing param: %d\n", size); 	

    add_node(g, 0, "A", 1, "B", 0);
    add_node(g, 0, "A", 2, "C", 0);
    add_node(g, 0, "A", 3, "D", 0);
    add_node(g, 1, "B", 2, "C", 0);
    add_node(g, 4, "E", 2, "C", 0);

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

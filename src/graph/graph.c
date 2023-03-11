#include "includes/graph.h"
#include "../queue/includes/queue.h"


walk_t *init_walk(int steps) {
	walk_t *w;
	w = (walk_t*)malloc(sizeof(walk_t));
   	w->path = malloc(steps * sizeof(int));
   	w->steps = steps; 	
	w->cycles = 0; 
	w->weighted_sum = 0; 
	return w; 
}


mat_t *to_matrix(mat_t *m, adj_list_t *g, bool directed) {
	
	/* iterate through list and populate matrix */
	for(int i = 0; i < g->v; i++) {

		node_t *head = g->items[i].head;
		node_t *src_node = get_node_by_id(g, i); 
		int row = src_node->id; 
		int col = head->id; 

		while(head) {

			entry_t *src = init_entry(src_node->id, src_node->label); 
			entry_t *dst = init_entry(head->id, head->label); 

			if(directed) {
				insert(m, src, dst, head->weight, true); 
			} else {
				insert(m, src, dst, head->weight, false); 
			}

			head  = head->next;
		}
	}
	return m; 
}


adj_list_t *to_list(adj_list_t *g, mat_t *m, bool directed) {

	for(int i = 0; i < m->vertices; i++) {
		for(int j = 0; j < m->vertices; j++) {
			if(m->matrix[i*m->vertices+j]->label != NULL) {

				int weight_value = m->weights[i*m->vertices+j];

				entry_t *src = search_entry_by_id(m, i); 
				entry_t *dst = search_entry_by_id(m, j); 
				add_node(g, i, src->label, j, dst->label, weight_value);
			}
		}
	}

	return g; 
}

#include "includes/adj_mat.h"


adj_mat_t *init_adj_mat(int v, int e, bool directed) {

	adj_mat_t *mat;
	mat = (adj_mat_t*)malloc(sizeof(adj_mat_t)); 
   	mat->visited = malloc(v * sizeof(int)); 
	mat->used = malloc(v * sizeof(int)); 
	mat->weights = init_matrix(v, v);
   	mat->err = false; 	
	mat->directed = directed; 
	mat->v = v;
    mat->e = e; 

	/* allocate slots for node matrice */
	mat->items = malloc(sizeof(node_t*) * mat->v * mat->v); 
	if(mat->items != NULL) {
		for(int i = 0; i < mat->v; i++){
			for(int j = 0; j < mat->v; j++){
				mat->items[i*mat->v+j] = (node_t*)malloc(sizeof(node_t));
				mat->items[i*mat->v+j]->id = -1;  
			}
		}
	}

    /* allocate visted and used */
    for(int i = 0; i < mat->v; i++){
        mat->used[i] = 0;
        mat->visited[i] = 0;  
    }

    return mat; 
}


void add_node_mat(
    adj_mat_t *m, int src_id, char *src, 
    int dst_id, char *dst, double weight) {

	int directed_index = src_id*m->v+dst_id;
	int undirected_index = dst_id*m->v+src_id; 
    node_t *dst_node = create_node(dst_id, dst, weight); 
    node_t *src_node = create_node(src_id, src, weight); 

	if(m->directed) {
		m->items[directed_index] = dst_node;
		m->weights->arr[src_id][dst_id] = weight;  
	} else {

		/* add node values */
		m->items[directed_index] = dst_node; 
		m->items[undirected_index] = src_node;  

		/* add weights */
		m->weights->arr[src_id][dst_id] = weight; 
		m->weights->arr[dst_id][src_id] = weight;  
	}
}


node_t *search_node_by_id_mat(adj_mat_t *mat, int id) {
	
    /* get neighbors for each vertice */
    for(int i = 0; i < mat->v; i++){
        int node_index = 0;  
        for(int j = 0; j < mat->v; j++){
            node_t *neighbor = mat->items[i*mat->v+j];
            if(neighbor->id  == id){
				return neighbor;
            } 
        }
    }

	node_t *result = create_node(-1, "no id found", 0); 
	return result; 
}


adj_mat_t *transpose_items_mat(adj_mat_t *m, adj_mat_t *r) {
	for(int i = 0; i < m->v; i++) {
		node_t *dst = search_node_by_id_mat(m, i); 
		for(int j = 0; j < m->v; j++){
            node_t *neighbor = m->items[i*m->v+j];
			if(neighbor->label != NULL){
				node_t *src = search_node_by_id_mat(m, j); 
				add_node_mat(r, src->id, src->label, dst->id, dst->label, src->weight); 
			}
		}
	}
	return r; 
}


void print_adj_mat(adj_mat_t *mat){
    for(int i = 0; i < mat->v; i++){
		printf("%d: ", i); 
        for(int j = 0; j < mat->v; j++){
            node_t *neighbor = mat->items[i*mat->v+j];
            if(neighbor->label != NULL){
				printf(
					"-> (%d, %s, %d)",
					neighbor->id, neighbor->label, neighbor->weight
				); 
            } 
        }
		printf("\n"); 
    }
}
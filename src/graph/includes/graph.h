#ifndef GRAPH_H
#define GRAPH_H

/* include data structures library */
#include "../../data_structures/includes/set.h"
#include "../../data_structures/includes/queue.h"
#include "../../data_structures/includes/matrix.h"
#include "../../data_structures/includes/adj_list.h"

/* include extractors library for building graphs */
#include "../../extractors/includes/re.h"
#include "../../extractors/includes/gml.h"

#define TRUE 1
#define FALSE 0

/* structure for storing results of walking through a graph */ 
struct Walk {
	int *path;
   	int steps; 	
	int weighted_sum;  
	int cycles; 
}; 

typedef struct Walk walk_t;

/* improved graph structure for the future */
struct Graph {
	int vertices, edges;
	int *visited, *labels;
	char *filename; 
	bool directed; 
	adj_list_t *list; 
	mat_graph_t *matrix;
	walk_t *walk; 
};

typedef struct Graph graph_t;

/* create graph structure */
graph_t *init_graph(int v, int e, bool directed); 

/* init walk structure */
walk_t *init_walk(int steps);

/* conversion methods to matrix */
mat_graph_t *to_matrix(mat_graph_t *m, adj_list_t *g, bool directed);

/* conversion methods to adjacency list  */ 
adj_list_t *to_list(adj_list_t *g, mat_graph_t *m, bool directed);

/* printing methods */
void label_node(graph_t *g, int index, int label); 
void print_graph_list(graph_t *g); 
void print_graph_matrix(graph_t *g);
void print_graph_walk(graph_t *g); 
void print_walk(walk_t *w);

/* frame to graph methods  */
graph_t *frame_to_unweighted_graph(frame_t *frame, int *cols, int size, bool directed);
graph_t *frame_to_weighted_graph(frame_t *frame, int *cols, int size, bool directed); 

/* adj list */
set_t *get_graph_nodes(char *filename, int file_size); 
graph_t *serialize_graph_list(char *filename, int file_size);
void deserialize_graph_list(graph_t *list, char *filename); 

/* matrice methods */
graph_t *serialize_mat_graph(char *filename, int file_size);
void deserialize_mat_graph(graph_t *mat); 

#endif


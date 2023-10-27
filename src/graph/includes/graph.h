#ifndef GRAPH_H
#define GRAPH_H

/* include data structures library */
#include "../../data_structures/set/includes/set.h"
#include "../../data_structures/queue/includes/queue.h"
#include "../../data_structures/matrix/includes/matrix.h"
#include "../../data_structures/list/includes/adj_list.h"
#include "../../data_structures/matrix/includes/adj_mat.h"

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
	adj_mat_t *matrix;
	walk_t *walk; 
};

typedef struct Graph graph_t;

/* create graph structure */
graph_t *init_graph(int v, int e, bool directed); 

/* init walk structure */
walk_t *init_walk(int steps);

/* conversion methods to matrix */
adj_mat_t *to_matrix(adj_mat_t *m, adj_list_t *g, bool directed);

/* conversion methods to adjacency list  */ 
adj_list_t *to_list(adj_list_t *g, adj_mat_t *m, bool directed);

/* mutator methods */
void remove_unused_slots(graph_t *g); 
void label_node(graph_t *g, int index, int label); 
void print_graph_list(graph_t *g); 
void print_graph_matrix(graph_t *g);
void print_graph_walk(graph_t *g); 
void print_walk(walk_t *w);

/* frame to graph methods  */
graph_t *frame_to_unweighted_graph(frame_t *frame, int *cols, int size, bool directed);
graph_t *frame_to_weighted_graph(frame_t *frame, int *cols, int size, bool directed); 

/* adj list */
int get_max_vertex_count(char *filename, int file_size); 
set_t *get_graph_node_ids(graph_t *g); 
ordered_set_t *get_graph_nodes(graph_t *g); 
set_t *get_graph_node_ids_file(char *filename, int file_size); 
set_t *get_graph_nodes_from_file(char *filename, int file_size);
graph_t *serialize_graph_list(char *filename, int file_size, bool directed); 
graph_t *serialize_graph_list_sorted_label(char *filename, int file_size);
void deserialize_graph_list(graph_t *list, char *filename); 

/* matrice methods */
graph_t *serialize_mat_graph(char *filename, int file_size);
void deserialize_mat_graph(graph_t *mat); 

#endif


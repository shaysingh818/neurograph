#include "graph/includes/graph.h"
#include "matrice/includes/matrix.h"
#include "queue/includes/queue.h"
#include "map/includes/map.h"
#include "graph/includes/path.h"
#include "csv/includes/csv.h"

int main(int argc, char **argv) {


	/* test random walk */ 
  	int vertices = 5; // num of vertices

	graph_t *g = init_graph(vertices, vertices, false); 
	add_node(g, 0, "A", 1, "B", 0); 
	add_node(g, 0, "A", 2, "C", 0); 
	add_node(g, 0, "A", 3, "D", 0); 
	add_node(g, 1, "B", 2, "C", 0);
	add_node(g, 4, "E", 2, "C", 0);

	printf("Graph library test\n"); 
	print_graph(g); 

	printf("\n");

	/* create adjacency matrix graph with size 5 */
	mat_t *m = init_matrice_graph(5); 

    /* create unique nodes */
    entry_t *a = init_entry(0, "A"); 
    entry_t *b = init_entry(1, "B"); 
    entry_t *c = init_entry(2, "C"); 
    entry_t *d = init_entry(3, "D"); 

	/* connect a to everyone */ 
    insert(m, a, b, 0, false); 
    insert(m, a, c, 0, false); 
    insert(m, b, c, 0, false); 
    insert(m, b, d, 0, false); 
    insert(m, c, d, 0, false); 

	printf("Matrix library test\n");
	print_matrix_ids(m);

	printf("\n"); 

	/* create nodes */ 
    node_t *node1 = create_node(1, "A", 0); 
    node_t *node2 = create_node(2, "B", 0); 
    node_t *node3 = create_node(3, "C", 0); 
    

	/* csv library */
   	csv_t *file = csv_init("../examples/data/test.csv", FILE_BUFFER_SIZE, 4);
	if(!file->status) {
		exit(0); 
	}	

	printf("CSV library test\n");
	csv_info(file);



	return 0; 
}

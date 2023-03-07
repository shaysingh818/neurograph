
#ifndef GRAPH_H
#define GRAPH_H

#include "../../queue/includes/queue.h"
#include "../../matrice/includes/matrix.h"
#include "../../list/includes/adj_list.h"

#define TRUE 1
#define FALSE 0

/* conversion methods to matrix */
mat_t *to_matrix(mat_t *m, adj_list_t *g, bool directed);

/* conversion methods to graph */ 
adj_list_t *to_list(adj_list_t *g, mat_t *m, bool directed); 


#endif


#include <stdio.h>
#include <unistd.h>
#include <stdbool.h>
#include <string.h> 
#include <stdlib.h>
#include <regex.h> 

/* data structures needed for GML interpretation */
#include "frame.h"
#include "re.h"

#define RE_NODE "\"[^\"]*\"|[^:]+"
#define RE_GML "\"[a-zA-Z]+\":|\"[a-zA-Z]+\""
#define RE_NEIGHBORS "\"[a-zA-Z]+\""
#define REMOVE_QUOTES "[a-zA-Z]+"

/* adj list */
set_t *get_graph_nodes(char *filename, int file_size); 
graph_t *serialize_graph_list(char *filename, int file_size);
void deserialize_graph_list(graph_t *list, char *filename); 

/* matrice methods */
graph_t *serialize_mat_graph(char *filename, int file_size);
void deserialize_mat_graph(graph_t *mat); 
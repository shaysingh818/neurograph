#ifndef FRAME_H
#define FRAME_H

#include <stdio.h>
#include <unistd.h>
#include <stdbool.h>
#include <string.h> 
#include <stdlib.h>
#include <regex.h> 

#include "../../data_structures/includes/ll.h"
#include "../../data_structures/includes/node.h"
#include "../../data_structures/includes/adj_list.h"
#include "../../data_structures/includes/matrix.h"
#include "../../data_structures/includes/map.h"

#define RE_CSV "\"[^\"]*\"|[^,]+"
#define RE_JSON "None Yet"
#define RE_YAML "Yaml"

#define FRAME_DEBUG true

struct Value {
	size_t value_size;
	int index;
	char *value;
}; 

typedef struct Value value_t; 


struct Header {
	int index, values_amount;
	char *name;
	size_t name_size; 
	value_t **values;  
}; 

typedef struct Header header_t; 


struct Frame {
	int buffer_size;
   	int header_count;
	int row_count; 
	char *filename;
	char *file_buffer; 
	char separator;
	bool status; 
	header_t **headers;
	map_t *map; 
};

typedef struct Frame frame_t; 


header_t **init_frame_headers(frame_t *frame);
frame_t *init_frame(char *filepath, int buffer_size);

void extract_frame_headers(frame_t *frame);  
void init_frame_rows(frame_t *frame);
void init_frame_map(frame_t *frame); 

void f_cols(frame_t *frame); 
void f_rows(frame_t *frame, header_t *header); 

/* dataframe to graph methods */ 
adj_list_t *frame_to_unweighted_graph(frame_t *frame, int *cols, int size, bool directed);
adj_list_t *frame_to_weighted_graph(frame_t *frame, int *cols, int size, bool directed); 
mat_t *frame_g_mat(frame_t *frame, int *cols, int size, int directed);

#endif
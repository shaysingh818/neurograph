#ifndef FRAME_H
#define FRAME_H

#include <stdio.h>
#include <unistd.h>
#include <stdbool.h>
#include <string.h> 
#include <stdlib.h>
#include <regex.h> 
#include <errno.h>

#include "../../data_structures/includes/ll.h"
#include "../../data_structures/includes/map.h"
#include "../../data_structures/includes/matrix.h"
#include "../../data_structures/includes/set.h"
#include "re.h"

#define RE_CSV "\"[^\"]*\"|[^,]+"
#define RE_CSV_TEST "\"[^\"]*\"|[^,]+"
#define RE_JSON "None Yet"
#define RE_YAML "Yaml"

#define FRAME_DEBUG true

struct RowValue {
	size_t value_size;
	int index;
	char *value;
}; 

typedef struct RowValue row_value_t; 


struct Header {
	int index, values_amount;
	char *name;
	size_t name_size; 
	row_value_t **values;  
}; 

typedef struct Header header_t; 


struct Frame {
	int buffer_size, header_count, row_count, row_limit; 
	char *filename, *file_buffer, *delimeter; 
	bool status; 
	header_t **headers;
	map_t *map; 
};

typedef struct Frame frame_t; 


/* initiate frame structure */
frame_t *init_frame(char *filepath, int buffer_size, int row_limit);

/* Methods to populate frame data */ 
void extract_frame_headers(frame_t *frame);  
void init_frame_rows_regex(frame_t *frame);
void init_frame_map(frame_t *frame); 

/* row value extraction methods */ 
array_t *match_delimeter_file(char *line, char *delimiter); 
mat_t *frame_to_mat(frame_t *frame, char **cols, int feature_store_size); 

/* header helper methods */
void allocate_frame_headers(frame_t *frame, array_t *row_values);
void copy_row_values(frame_t *frame, array_t *row_values, int row_count);
void allocate_header_rows(frame_t *frame);
int match_header(frame_t *frame, char *header_key);  
header_t **init_frame_headers(frame_t *frame);

/* get cols and rows for dataframe */
void f_cols(frame_t *frame); 
void f_rows(frame_t *frame, header_t *header); 

/* utilities for working with files */
void end_line_terminate(char *buffer); 
int count_lines(char *filename, int file_size);


#endif

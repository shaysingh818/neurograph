#ifndef FRAME_H
#define FRAME_H

#include <stdio.h>
#include <unistd.h>
#include <stdbool.h>
#include <string.h> 
#include <stdlib.h>
#include <regex.h> 
#include <errno.h>

#include <data_structures/list/includes/array.h>
#include <data_structures/list/includes/ll.h>
#include <data_structures/map/includes/map.h>
#include <data_structures/map/includes/table.h>
#include <data_structures/map/includes/hash.h>
#include <data_structures/matrix/includes/matrix.h>
#include <data_structures/set/includes/set.h>
#include "re.h"
#include "utils.h"

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


struct Frame {
	int buffer_size, header_count; 
	int curr_row, row_count, row_limit; 
	char *filename, *file_buffer, *delimiter; 
	bool status;
	mat_t *matrix;    
	array_t *headers; 
    hash_table_t *frame;
};

typedef struct Frame frame_t; 


/* initiates frame structure itself */
frame_t *create_frame(char *filepath, int buffer_size, int row_limit, char *delimiter);

/* hash map based frame */
frame_t *dataframe(char *filepath, int buffer_size, int row_limit, char *delimiter);  

/* initiate row value structure */
row_value_t *init_row_value(int index, char *value); 

/* convert selected columns to a floating point matrix */
mat_t *frame_to_matrix(frame_t *frame, array_t *cols); 

/* extract headers from frame  */
void extract_headers(frame_t *frame);

/* populate rows using hash map structure */
void init_rows(frame_t *frame); 

/* print cols for data frame  */
void print_cols(frame_t *frame); 

/* print rows for data frame */
void print_rows(frame_t *frame);

/* select columns you want to see/print */
void select_cols(frame_t *frame, void** headers); 

/* select columns you want to see/print */
void drop_cols(frame_t *frame, array_t *cols); 

/* get row values from key */
char **get_row_key(frame_t *frame, char *key); 

#endif
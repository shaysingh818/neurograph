#ifndef CSV_H
#define CSV_H

#include "../../src/includes/graph.h"
#include <stdio.h>
#include <unistd.h>

#define FEATURE_SIZE 6
#define DEFAULT_ROW_LIMIT 10
#define FILE_BUFFER_SIZE 1024
#define DEBUG FALSE

/* column structure for csv file */ 
struct Column {
	char *name; 
	int row_index; 
	size_t name_length; 
}; 

typedef struct Column col_t; 


/* column structure for csv file */ 
struct Row {
	char **line; 
	int value_count; 
	int line_size; 
}; 

typedef struct Row row_t; 


/* formal CSV structure */ 
struct CSV {
	int buffer_size;
   	int col_count;
	int row_limit; // for now let the user choose how many rows to load in 
	int status; 	
	char *filename;
	col_t **cols;
	row_t **rows; 
};

typedef struct CSV csv_t;


/* csv structure helper methods */
int populate_headers(csv_t *csv); 
int populate_rows(csv_t *csv); 
csv_t *csv_init(char *filename, int buf_size, int set_limit);

/* formatted printing methods */ 
void print_cols(csv_t *csv); 
void print_rows(csv_t *csv); 
void csv_info(csv_t *csv);

/* csv to graph methods */ 
graph_t *csv_to_unweighted_graph(csv_t *csv, int *cols, int size, int directed);
graph_t *csv_to_weighted_graph(csv_t *csv, int *cols, int size, int directed); 
mat_t *csv_g_mat(csv_t *csv, int *cols, int size, int directed); 

#endif


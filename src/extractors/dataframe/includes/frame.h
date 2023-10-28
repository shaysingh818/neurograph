#ifndef FRAME_H
#define FRAME_H

#include <stdio.h>
#include <unistd.h>
#include <stdbool.h>
#include <string.h> 
#include <stdlib.h>
#include <regex.h> 
#include <errno.h>

#include "../../../data_structures/list/includes/ll.h"
#include "../../../data_structures/map/includes/map.h"
#include "../../../data_structures/map/includes/table.h"
#include "../../../data_structures/map/includes/hash.h"
#include "../../../data_structures/matrix/includes/matrix.h"
#include "../../../data_structures/set/includes/set.h"
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
	int buffer_size, header_count; 
	int curr_row, row_count, row_limit; 
	char *filename, *file_buffer, *delimeter; 
	bool status; 
	header_t **headers;
    hash_table_t *frame;   
	map_t *map;
};

typedef struct Frame frame_t; 



#endif
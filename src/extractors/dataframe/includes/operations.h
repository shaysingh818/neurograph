
#ifndef OPERATIONS_H
#define OPERATIONS_H

#include <stdio.h>
#include <unistd.h>
#include <stdbool.h>
#include <string.h> 
#include <stdlib.h>
#include <regex.h> 
#include <errno.h>

#include "re.h"
#include "frame.h"


/* initiate frame structure */
frame_t *init_frame(char *filepath, int buffer_size, int row_limit);
frame_t *create_frame(char *filepath, int buffer_size, int row_limit);
frame_t *dataframe(char *filepath, int buffer_size, int row_limit);  
frame_t *array_dataframe(char *filepath, int buffer_size, int row_limit);  

#endif
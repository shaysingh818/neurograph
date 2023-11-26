
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
void add_frame_cols(frame_t *frame, char *col1, char *col2, char *result_col); 
void subtract_frame_cols(frame_t *frame, char *col1, char *col2, char *result_col); 

#endif
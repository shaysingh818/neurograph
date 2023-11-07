
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
frame_t *add_frame_cols(frame_t *frame, void *col1, void *col2); 
frame_t *subtract_frame_cols(frame_t *frame, void *col1, void *col2); 

#endif
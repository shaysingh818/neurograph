#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>
#include <unistd.h>
#include <stdbool.h>
#include <string.h> 
#include <stdlib.h>
#include <regex.h> 
#include <errno.h>


/* utilities for working with files */
void end_line_terminate(char *buffer); 
void remove_character(char *buffer, char remove); 
int count_lines(char *filename, int file_size);


#endif
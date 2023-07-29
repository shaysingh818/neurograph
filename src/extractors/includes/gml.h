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
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
#define REMOVE_QUOTES "[a-zA-Z]+"
#define GET_QUOTES "(['\"])"

/* new expressions for weights and ids */
// #define RE_GML_NODE "[0-9]+|[a-zA-Z]+"

#define RE_GML_NODE "[0-9]+|\"[^\"]*\""
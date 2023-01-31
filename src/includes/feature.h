#ifndef FEATURE_H
#define FEATURE_H

#include "../../src/includes/graph.h"
#include <stdio.h>

#define FEATURE_SIZE 6


/* defintion of a feature (refer to documentation) */ 
struct Feature {
	char *name; 
	int row_index; 
	size_t name_length; 
}; 

typedef struct Feature feature_t; 


/* defintion of a feature (refer to documentation) */ 
struct FeatureList {
	char *file_name; 
	int feature_count; 
	feature_t **features; 
}; 

typedef struct FeatureList feature_list_t; 


/* get row data with associated selected feature */ 
struct FeatureValues {
	feature_t *selected_feature; 
	char **data; 
	int size; 
}; 

typedef struct FeatureValues row_t;

#endif


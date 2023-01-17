#ifndef CSV_H
#define CSV_H

#include "../../src/includes/graph.h"
#include <stdio.h>

#define FEATURE_SIZE 5
#define FILE_BUFFER_SIZE 1024

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

/* utility methods for feature extraction and csv files */ 
feature_list_t *init_feature_list(
	char *file_name, int feature_count, 
	feature_t **features
);

feature_list_t *csv_feature_extraction(char *set_filename); 
void print_feature(feature_t *f); 

#endif


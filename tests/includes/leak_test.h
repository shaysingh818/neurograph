#ifndef LEAK_TEST_H
#define LEAK_TEST_H

#include "../../src/includes/csv.h"

int test_headers_populate(csv_t *csv);
int test_rows_populate(csv_t *csv); 
csv_t *test_csv_init(char *filename, int buf_size, int set_limit); 
void csv_free(csv_t *csv); 

#endif

#include "leak_test.h"

int main(char **argv, int argc) {

	printf("Testing\n"); 
	csv_t *file = test_csv_init("../example/data/movies.csv", FILE_BUFFER_SIZE, 4);
	free_csv(file); 	

}

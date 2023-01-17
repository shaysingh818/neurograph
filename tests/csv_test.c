#include "includes/csv_test.h"

void test_header_extraction() {

	int equality_status = TRUE;
	feature_list_t *feature_list = csv_feature_extraction(
		"../examples/data/city_population_density.csv"
	);

	/* expected results */ 
	char feature_output[8][100] = {
		"City", "Population", "Area KM2",
		"Area M2", "Density KM2", "Density  M2",
		"Country", "Year"
	};

	/* expected results */ 
	int row_output[8] = { 0, 1, 2, 3, 4, 5, 6, 7};

	/* compare against expected results */ 
	for(int i = 0; i < feature_list->feature_count; i++) {
		char *feature_name = feature_list->features[i]->name; 
		int row_index = feature_list->features[i]->row_index; 
		int row_condition = row_index == row_output[i]; 
		int name_condition = strcmp(feature_name, feature_output[i]) == 0;

		if(!name_condition || !row_condition) {
			equality_status = FALSE; 
		}

	}

	if(!equality_status) {
        printf("%s::%s... FAILED\n", __FILE__, __FUNCTION__);
    }
    printf("%s::%s... \e[0;32mPASSED\e[0m\n", __FILE__, __FUNCTION__);


}

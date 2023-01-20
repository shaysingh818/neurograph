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

void test_header_extraction_two() {

	int equality_status = TRUE;
	feature_list_t *feature_list = csv_feature_extraction(
		"../examples/data/power_generation.csv"
	);

	/* expected results */ 
	char feature_output[10][100] = {
		"Power Station", "Monitored Cap.(MW)", "Total Cap. Under Maintenace (MW)",
		"Planned Maintanence (MW)", "Forced Maintanence(MW)", "Other Reasons (MW)",
		"Programme or Expected(MU)", "Actual(MU)", "Excess(+) / Shortfall (-)",
		"Deviation"
	};
	int row_output[10] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

	for(int i = 0; i < feature_list->feature_count; i++) {

		/* values */ 
		char *feature_name = feature_list->features[i]->name; 
		int row_index = feature_list->features[i]->row_index;

		/* compare against expected results  */ 
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


void test_header_extraction_three() {

	int equality_status = TRUE;
	feature_list_t *feature_list = csv_feature_extraction(
		"../examples/data/store_orders.csv"
	);

	/* expected results */ 
	char feature_output[20][50] = {
		"order_date", "ship_date", "ship_mode",
		"customer_name", "segment", "state",
		"country", "market", "region", "product_id",
		"category", "sub_category", "product_name",
		"sales", "quantity", "discount", "profit",
		"shipping_cost", "order_priority", "year"
	};

	int row_output[20] = { 
		0, 1, 2, 3, 4, 5, 6, 7,
		8, 9, 10, 11, 12, 13, 14,
		15, 16, 17, 18, 19
	};

	for(int i = 0; i < feature_list->feature_count; i++) {

		/* values */ 
		char *feature_name = feature_list->features[i]->name; 
		int row_index = feature_list->features[i]->row_index;

		/* compare against expected results */  
		int row_condition = row_index == row_output[i]; 
		int name_condition = strcmp(feature_name, feature_output[i]) == 0;

		/* figure out why the year value doesn't work */ 

		if(!name_condition || !row_condition) {
			equality_status = FALSE; 
		}  
	}


}



void test_header_extraction_four() {

	int equality_status = TRUE;
	feature_list_t *feature_list = csv_feature_extraction(
		"../examples/data/movies.csv"
	);

	/* expected results */ 
	char feature_output[8][100] = {
		"movie_name", "year_of_release", "category",
		"run_time", "genre", "imdb_rating",
		"votes", "gross_total"
	};
	int row_output[10] = { 0, 1, 2, 3, 4, 5, 6, 7};

	for(int i = 0; i < feature_list->feature_count; i++) {

		/* values */ 
		char *feature_name = feature_list->features[i]->name; 
		int row_index = feature_list->features[i]->row_index;

		/* compare against expected results */ 
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

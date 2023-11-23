import neurograph.tests.frame as ng
import cython
from pprint import pprint
import unittest

class TestFrame(unittest.TestCase):

    def test_dataframe(self):
        
        # create dataframe
        df = ng.DataFrame("../examples/data/ms_prediction.csv", 10)
        results = df.props()           
        self.assertEqual(results["buffer_size"], 1024)
        self.assertEqual(results["current_row"], 10)
        self.assertEqual(results["row_count"], 0)
        self.assertEqual(results["row_limit"], 10)
        self.assertEqual(results["header_count"], 20)
        self.assertTrue(results["status"], True)
        self.assertEqual(
            results["filename"], 
            "../examples/data/ms_prediction.csv"
        )

    def test_features(self):
        
        # create dataframe
        df = ng.DataFrame("../examples/data/ms_prediction.csv", 10)
        results = df.props()
        self.assertEqual(results["header_count"], 20)

        expected_headers = [
            "Patient_ID", "Gender", "Age", "Schooling",
            "Breastfeeding", "Varicella", "Initial_Symptom", "Mono_or_Polysymptomatic",
            "Oligoclonal_Bands", "LLSSEP", "ULSSEP", "VEP", "BAEP", 
            "Periventricular_MRI", "Cortical_MRI", "Infratentorial_MRI", 
            "Spinal_Cord_MRI", "Initial_EDSS", "Final_EDSS", "group"
        ]

        headers = df.get_headers()
        for i in range(len(headers)):
            self.assertEqual(headers[i]["name"], expected_headers[i])

        movie_df = ng.DataFrame("../examples/data/movies.csv", 10)
        results = movie_df.props() 
        self.assertEqual(results["header_count"], 9)

        expected_headers = [
            "index", "movie_name", "year_of_release", "category",
            "run_time", "genre", "imdb_rating", "votes", "gross_total"
        ]

        movie_headers = movie_df.get_headers()
        for i in range(len(movie_headers)):
            self.assertEqual(movie_headers[i]["name"], expected_headers[i])

    def test_get_rows(self):

        # create dataframe
        df = ng.DataFrame("../examples/data/ms_prediction.csv", 10)
        results = df.props()   
        self.assertEqual(results["row_limit"], 10)
        self.assertEqual(results["header_count"], 20)
        rows = df.rows()

        expected_row1 = ['0', '1', '2', '3', '4', '5', '6', '7', '8', '9']
        expected_row2 = ['1','1','1','2','2','1','2','2','1', '2']
        expected_last_row = ['1','1','1','1','1','1','1','1','1','1']
        keys = []
        for item in df.get_headers():
            keys.append(item["name"])

        headers = df.get_headers()
        for i in range(len(headers)):
            key = headers[i]["name"]
            self.assertEqual(len(rows[key]), 10)

        self.assertEqual(expected_row1, rows["Patient_ID"])
        self.assertEqual(expected_row2, rows["Gender"])
        self.assertEqual(expected_last_row, rows["group"])


    def test_select_cols(self):
        pass

    def test_drop_cols(self):
        pass

    def test_to_matrix(self):
        pass
from neurograph.extractors import DataFrame
from neurograph.structures import Matrix
from pprint import pprint
import unittest

class TestFrame(unittest.TestCase):

    def test_dataframe(self):
        
        # create dataframe
        df = DataFrame("../examples/data/ms_prediction.csv", 10)
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
        df = DataFrame("../examples/data/ms_prediction.csv", 10)
        results = df.props()
        self.assertEqual(results["header_count"], 20)

        expected_headers = [
            "Patient_ID", "Gender", "Age", "Schooling",
            "Breastfeeding", "Varicella", "Initial_Symptom", "Mono_or_Polysymptomatic",
            "Oligoclonal_Bands", "LLSSEP", "ULSSEP", "VEP", "BAEP", 
            "Periventricular_MRI", "Cortical_MRI", "Infratentorial_MRI", 
            "Spinal_Cord_MRI", "Initial_EDSS", "Final_EDSS", "group"
        ]

        headers = df.headers()
        for i in range(len(headers)):
            self.assertEqual(headers[i]["name"], expected_headers[i])

        movie_df = DataFrame("../examples/data/movies.csv", 10)
        results = movie_df.props() 
        self.assertEqual(results["header_count"], 9)

        expected_headers = [
            "index", "movie_name", "year_of_release", "category",
            "run_time", "genre", "imdb_rating", "votes", "gross_total"
        ]

        movie_headers = movie_df.headers()
        for i in range(len(movie_headers)):
            self.assertEqual(movie_headers[i]["name"], expected_headers[i])

    def test_get_rows(self):

        # create dataframe
        df = DataFrame("../examples/data/ms_prediction.csv", 10)
        results = df.props()   
        self.assertEqual(results["row_limit"], 10)
        self.assertEqual(results["header_count"], 20)
        rows = df.rows()

        expected_row1 = ['0', '1', '2', '3', '4', '5', '6', '7', '8', '9']
        expected_row2 = ['1','1','1','2','2','1','2','2','1', '2']
        expected_last_row = ['1','1','1','1','1','1','1','1','1','1']
        keys = []
        for item in df.headers():
            keys.append(item["name"])

        headers = df.headers()
        for i in range(len(headers)):
            key = headers[i]["name"]
            self.assertEqual(len(rows[key]), 10)

        self.assertEqual(expected_row1, rows["Patient_ID"])
        self.assertEqual(expected_row2, rows["Gender"])
        self.assertEqual(expected_last_row, rows["group"])


    def test_drop_cols(self):
        
        # create dataframe
        df = DataFrame("../examples/data/online_retail.csv", 1000) 
        current = df.headers()
        
        expected_headers = [
            'InvoiceNo', 'StockCode', 'Description', 'Quantity',
            'InvoiceDate', 'UnitPrice', 'CustomerID', 'Country'
        ]

        for i in range(len(current)):
            self.assertEqual(current[i]["name"], expected_headers[i])

        dropped_headers = [
            'Description', 'InvoiceDate', 'UnitPrice', 'CustomerID', 'Country'
        ]

        df.drop_cols(cols=["InvoiceNo", "StockCode", "Quantity"])
        dropped = df.headers()

        for i in range(len(dropped)):
            self.assertEqual(dropped[i]["name"], dropped_headers[i])

    def test_to_matrix(self):
        
        df = DataFrame("../examples/data/ms_prediction.csv", 10)
        self.assertEqual(len(df.headers()), 20) 

        x = Matrix(df, cols=["Schooling", "Age", "Gender"])
        self.assertEqual(x.rows(), 10)
        self.assertEqual(x.cols(), 3)

        y = Matrix(df, ["group"])
        self.assertEqual(y.rows(), 10)
        self.assertEqual(y.cols(), 1)

    def test_add_cols(self):

        df = DataFrame("../examples/data/ms_prediction.csv", 10)
        df.sum(cols=["Patient_ID", "Age"], result="my_sum")
        self.assertEqual(len(df.headers()), 21)
        expected_vals = [
            '34.00', '62.00', '24.00', '44.00', '38.00',
            '34.00', '59.00', '31.00', '44.00', '37.00'
        ]
        self.assertEqual(df.map_header("my_sum"), expected_vals)

        df.sum(cols=["Patient_ID", "Breastfeeding"], result="total_sum") 
        self.assertEqual(len(df.headers()), 22)
        expected_vals = [
            '1.00', '4.00', '5.00', '4.00', '6.00',
            '6.00', '7.00', '8.00', '9.00', '10.00'
        ]
        self.assertEqual(df.map_header("total_sum"), expected_vals)


    def test_subtract_cols(self):

        df = DataFrame("../examples/data/ms_prediction.csv", 10)
        df.subtract(cols=["Patient_ID", "Age"], result="my_sum")
        self.assertEqual(len(df.headers()), 21)
        expected_vals = [
            '-34.00', '-60.00', '-20.00', '-38.00', '-30.00', 
            '-24.00', '-47.00', '-17.00', '-28.00', '-19.00'
        ]
        self.assertEqual(df.map_header("my_sum"), expected_vals)

        df.subtract(cols=["Patient_ID", "Breastfeeding"], result="total_sum") 
        self.assertEqual(len(df.headers()), 22)
        expected_vals = [
            '-1.00', '-2.00', '-1.00', '2.00', '2.00', 
            '4.00', '5.00', '6.00', '7.00', '8.00'
        ]

        self.assertEqual(df.map_header("total_sum"), expected_vals)
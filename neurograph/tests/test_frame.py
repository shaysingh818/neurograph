import frame as ng
import cython
from pprint import pprint
import unittest

class TestFrame(unittest.TestCase):

    def test_dataframe(self):
        
        # create dataframe
        df = ng.DataFrame(b"../examples/data/ms_prediction.csv", 10)
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
        pass

    def test_select_cols(self):
        pass

    def test_drop_cols(self):
        pass

    def test_to_matrix(self):
        pass
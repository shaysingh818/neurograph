from neurograph.structures import ndarray
from pprint import pprint
import unittest
import os

class TestNetworks(unittest.TestCase):

    def test_create_ndarray(self):

        # init
        instance = ndarray(shape=[4, 2], values=[[0,0],[1,1],[1,0],[0,0]])
        size = instance.size()
        rank = instance.rank()
        values = instance.values()

        self.assertEqual(size, 8)
        self.assertEqual(rank, 2)
        self.assertEqual(instance.shape(), (4, 2))
        self.assertEqual(values, [0,0,1,1,1,0,0,0])

        # failed instance 
        self.assertRaises(Exception, ndarray, [4, 4], [[0,0],[1,1],[1,0],[0,0]])
        self.assertRaises(Exception, ndarray, [4, 3], [[0,0],[1,1],[1,0],[0,0]])
        self.assertRaises(Exception, ndarray, [4, 2], [[0],[1,1],[1,0],[0,0]])
        self.assertRaises(Exception, ndarray, [4, 2], [[0],[1,1],[1,0],[0,0,0,0]])
        self.assertRaises(Exception, ndarray, [3, 4])
        self.assertRaises(Exception, ndarray, [3, 4],  [[0,0],[1,1],[1,0],[0,0]], "test")


    def test_add_ndarray(self):

        # input 
        x = ndarray(shape=[4, 2], values=[[0,0],[1,1],[1,0],[0,0]])
        y = ndarray(shape=[4, 2], values=[[0,0],[3,3],[3,0],[0,0]])

        x.add(y)
        vals = x.values()
        expected_vals = [0,0,4,4,4,0,0,0]
        self.assertEqual(expected_vals, vals)

        # add uneven size
        x1 = ndarray(shape=[4, 1], values=[[0],[1],[1],[0]])
        y1 = ndarray(shape=[4, 2], values=[[0,0],[3,3],[3,0],[0,0]])
        self.assertRaises(Exception, x1.add, y1)

        # add unequal rank 
        x2 = ndarray(shape=[2, 2, 2], values=[[0,0],[3,3],[3,0],[0,0]])
        y2 = ndarray(shape=[4, 2], values=[[0,0],[3,3],[3,0],[0,0]])
        self.assertRaises(Exception, x2.add, y2)


    def test_subtract_ndarray(self):

        # input 
        x = ndarray(shape=[4, 2], values=[[0,0],[1,1],[1,0],[0,0]])
        y = ndarray(shape=[4, 2], values=[[0,0],[10,10],[10,0],[0,0]])

        y.subtract(x)
        vals = y.values()
        expected_vals = [0,0,9,9,9,0,0,0]
        self.assertEqual(expected_vals, vals)

        # subtract uneven size
        x1 = ndarray(shape=[4, 1], values=[[0],[1],[1],[0]])
        y1 = ndarray(shape=[4, 2], values=[[0,0],[3,3],[3,0],[0,0]])
        self.assertRaises(Exception, y1.subtract, x1)

        # subtract unequal rank 
        x2 = ndarray(shape=[2, 2, 2], values=[[0,0],[3,3],[3,0],[0,0]])
        y2 = ndarray(shape=[4, 2], values=[[0,0],[3,3],[3,0],[0,0]])
        self.assertRaises(Exception, y2.subtract, x2)


    def test_dot_ndarray(self):

        # square matrixes 
        x1 = ndarray(shape=[2, 2], values=[[0,0],[2,2]])
        y1 = ndarray(shape=[2, 2], values=[[0,0],[10,10]])
        x1.dot(y1)
        self.assertEqual(x1.values(), [0, 0, 20, 20])

        # dimension mismatch 
        x = ndarray(shape=[4, 2], values=[[0,0],[2,2],[2,0],[0,0]])
        y = ndarray(shape=[4, 2], values=[[0,0],[10,10],[10,0],[0,0]])
        self.assertRaises(Exception, x.dot, y)

        # rank mismatch 
        x2 = ndarray(shape=[2, 2, 2], values=[[0,0],[3,3],[3,0],[0,0]])
        y2 = ndarray(shape=[4, 2], values=[[0,0],[3,3],[3,0],[0,0]])
        self.assertRaises(Exception, x2.dot, y2)


    def test_scale_add(self):

        x = ndarray(shape=[4, 3], values=[
            [0,0,0],
            [2,2,2],
            [2,2,2],
            [4,4,4]
        ])

        x1 = ndarray(shape=[4, 4], values=[
            [0,0,0,0],
            [2,2,2,2],
            [2,2,2,2],
            [4,4,4,4]
        ])

        y = ndarray(shape=[1, 3], values=[1,1,1])
        y1 = ndarray(shape=[1, 3], values=[1,1,1])
        rank_3 = ndarray(shape=[2, 2, 2], values=[[0,0],[3,3],[3,0],[0,0]])

        x.scale_add(y)
        vals = x.values()
        expected_vals  = [
            1,1,1,
            3,3,3,
            3,3,3,
            5,5,5
        ]

        self.assertEqual(expected_vals, vals)
        self.assertRaises(Exception, x1.scale_add, y1)
        self.assertRaises(Exception, x1.scale_add, rank_3)

    
    def test_transpose(self):
        
        square = ndarray(shape=[6, 6], values=[
            [1,2,3,4,5,6],
            [1,2,3,4,5,6],
            [0,0,2,0,0,0],
            [0,0,0,2,0,0],
            [0,0,0,0,2,0],
            [0,0,0,0,0,2],
        ])

        expected_values = [
            1,1,0,0,0,0,
            2,2,0,0,0,0,
            3,3,2,0,0,0,
            4,4,0,2,0,0,
            5,5,0,0,2,0,
            6,6,0,0,0,2
        ]

        # transpose
        square.transpose()
        vals = square.values()
        self.assertEqual(vals, expected_values)
        self.assertEqual(square.shape(), (6,6))

        # rank exception
        x2 = ndarray(shape=[2, 2, 2], values=[[0,0],[3,3],[3,0],[0,0]])
        self.assertRaises(Exception, x2.transpose)


    def test_permute(self):
        
        square = ndarray(shape=[6, 6], values=[
            [1,2,3,4,5,6],
            [1,2,3,4,5,6],
            [0,0,2,0,0,0],
            [0,0,0,2,0,0],
            [0,0,0,0,2,0],
            [0,0,0,0,0,2],
        ])

        expected_values = [
            1,1,0,0,0,0,
            2,2,0,0,0,0,
            3,3,2,0,0,0,
            4,4,0,2,0,0,
            5,5,0,0,2,0,
            6,6,0,0,0,2
        ]

        square.permute(indice_order=[1,0])
        vals = square.values()
        self.assertEqual(vals, expected_values)
        self.assertEqual(square.shape(), (6,6))

        # rank exception
        x2 = ndarray(shape=[2, 2, 2], values=[[0,0],[3,3],[3,0],[0,0]])
        self.assertRaises(Exception, x2.permute, [1, 0])
        self.assertRaises(Exception, square.permute, [2, 1, 0])

        # permute in 3 dimemsions
        x2.permute(indice_order=[2,1,0])
        vals = x2.values()
        expected_vals = [0,3,3,0,0,0,3,0]
        self.assertEqual(vals, expected_vals)
        self.assertEqual(x2.shape(), (2,2,2))


    def test_save_ndarray(self):

        square = ndarray(shape=[6, 6], values=[
            [1,2,3,4,5,6],
            [1,2,3,4,5,6],
            [0,0,2,0,0,0],
            [0,0,0,2,0,0],
            [0,0,0,0,2,0],
            [0,0,0,0,0,2],
        ])

        # save tensor to file
        self.assertRaises(Exception, square.save, "data", "test_file")
        self.assertRaises(Exception, square.save, "random_path", "test_file_2")

        # successful save 
        square.save(path="./", name="test")
        path_exists = os.path.exists("test")
        self.assertEqual(path_exists, True)

        expected_dim_vals = ["rank: 2", "dim: 6", "dim: 6"]
        expected_file_vals = [
            1,2,3,4,5,6,
            1,2,3,4,5,6,
            0,0,2,0,0,0,
            0,0,0,2,0,0,
            0,0,0,0,2,0,
            0,0,0,0,0,2,
        ]

        # vals
        dim_vals = []
        file_vals = []

        # read values from file
        counter = 0
        ndarray_file = open("test", "r")
        for line in ndarray_file:
            if counter < 3:
                dim_vals.append(line.strip())
            else:
                int_val = float(line.strip())
                file_vals.append(int_val)
            counter += 1

        self.assertEqual(dim_vals, expected_dim_vals)
        self.assertEqual(file_vals, expected_file_vals)

        # remove temp file 
        os.remove("test")


    def test_load_ndarray(self):

        square = ndarray(shape=[6, 6], values=[
            [1,2,3,4,5,6],
            [1,2,3,4,5,6],
            [0,0,2,0,0,0],
            [0,0,0,2,0,0],
            [0,0,0,0,2,0],
            [0,0,0,0,0,2],
        ])

        # expected loaded values
        expected_file_vals = [
            1,2,3,4,5,6,
            1,2,3,4,5,6,
            0,0,2,0,0,0,
            0,0,0,2,0,0,
            0,0,0,0,2,0,
            0,0,0,0,0,2,
        ]

        # successful save 
        square.save(path="./", name="test")
        path_exists = os.path.exists("test")
        self.assertEqual(path_exists, True)

        loaded_array = ndarray(filepath="test")
        self.assertEqual(loaded_array.shape(), (6,6))
        self.assertEqual(expected_file_vals, loaded_array.values())
        self.assertRaises(Exception, ndarray)
        os.remove("test")
        
                



       


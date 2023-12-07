from neurograph.extractors import DataFrame
from neurograph.structures import Matrix, batch_matrix
from neurograph.networks import Network
from pprint import pprint
import unittest

class TestNetworks(unittest.TestCase):

    def test_mlp(self):

        # input 
        x = Matrix(rows=4, cols=2)
        x.array(entries=[[0,0],[0,1],[1,0],[1,1]])
        val = x.to_value()

        # expected output
        y = Matrix(rows=4, cols=1)
        y.array(entries=[[0],[1],[1],[0]])

        # create mlp architecture
        mlp = Network(learning_rate=0.01, value=val, batch_size=0)
        mlp.linear(input_size=2, output_size=3)
        mlp.activation(input_size=2, output_size=3, loss_type="tanh")
        mlp.linear(input_size=3, output_size=1)
        mlp.activation(input_size=3, output_size=1, loss_type="tanh")
        mlp.train(epochs=2000, output=y, log=False)

        model_structure = mlp.architecture()
        first_layer = model_structure["layer_0"]
        self.assertEqual(first_layer["input_size"], 2)
        self.assertEqual(first_layer["output_size"], 3)
        self.assertEqual(first_layer["type"], "linear")

        second_layer = model_structure["layer_1"]
        self.assertEqual(second_layer["input_size"], 2)
        self.assertEqual(second_layer["output_size"], 3)
        self.assertEqual(second_layer["type"], "loss")

        third_layer = model_structure["layer_2"]
        self.assertEqual(third_layer["input_size"], 3)
        self.assertEqual(third_layer["output_size"], 1)
        self.assertEqual(third_layer["type"], "linear")

        fourth_layer = model_structure["layer_3"]
        self.assertEqual(fourth_layer["input_size"], 3)
        self.assertEqual(fourth_layer["output_size"], 1)
        self.assertEqual(fourth_layer["type"], "loss")

        results = mlp.predict(input=x).to_list()
        self.assertEqual(results[0][0] < results[1][0], True)
        self.assertEqual(results[2][0] > results[0][0], True)
        self.assertEqual(results[3][0] < results[1][0], True)
        self.assertEqual(results[3][0] < results[2][0], True)


    def test_mlp_batch_train(self):
     
        # input 
        x = Matrix(rows=4, cols=2)
        x.array(entries=[[0,0],[0,1],[1,0],[1,1]])
        x_train = batch_matrix(mat_instance=x, batch_size=2)
        val = x.to_value()

        # expected output
        y = Matrix(rows=4, cols=1)
        y.array(entries=[[0],[1],[1],[0]])
        y_train = batch_matrix(mat_instance=y, batch_size=2)

        # create mlp architecture
        mlp = Network(learning_rate=0.01, value=val, batch_size=2)
        mlp.linear(input_size=2, output_size=3)
        mlp.activation(input_size=2, output_size=3, loss_type="tanh")
        mlp.linear(input_size=3, output_size=1)
        mlp.activation(input_size=3, output_size=1, loss_type="tanh")
        mlp.batch_train(epochs=2000, output=y, log=False)

        model_structure = mlp.architecture()
        first_layer = model_structure["layer_0"]
        self.assertEqual(first_layer["input_size"], 2)
        self.assertEqual(first_layer["output_size"], 3)
        self.assertEqual(first_layer["type"], "linear")

        second_layer = model_structure["layer_1"]
        self.assertEqual(second_layer["input_size"], 2)
        self.assertEqual(second_layer["output_size"], 3)
        self.assertEqual(second_layer["type"], "loss")

        third_layer = model_structure["layer_2"]
        self.assertEqual(third_layer["input_size"], 3)
        self.assertEqual(third_layer["output_size"], 1)
        self.assertEqual(third_layer["type"], "linear")

        fourth_layer = model_structure["layer_3"]
        self.assertEqual(fourth_layer["input_size"], 3)
        self.assertEqual(fourth_layer["output_size"], 1)
        self.assertEqual(fourth_layer["type"], "loss")

        mlp.predict(input=x_train[0])


    def save_mlp_model(self):
        
        # input 
        x = Matrix(rows=4, cols=2)
        x.array(entries=[[0,0],[0,1],[1,0],[1,1]])
        val = x.to_value()

        # expected output
        y = Matrix(rows=4, cols=1)
        y.array(entries=[[0],[1],[1],[0]])

        # create mlp architecture
        mlp = Network(learning_rate=0.01, value=val, batch_size=0)
        mlp.linear(input_size=2, output_size=3)
        mlp.activation(input_size=2, output_size=3, loss_type="tanh")
        mlp.linear(input_size=3, output_size=1)
        mlp.activation(input_size=3, output_size=1, loss_type="tanh")
        mlp.train(epochs=2000, output=y)
        mlp.save(filepath="pynet")

        # verify model layer paths exist

    def load_mlp_model(self):
        pass



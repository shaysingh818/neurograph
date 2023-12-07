import cython
from pprint import pprint
from neurograph.structures import Matrix, batch_matrix
# from neurograph.graph import Graph
from neurograph.networks import Network

def main():

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
    # mlp.save(filepath="pynet")
    results = mlp.predict(input=x)
    vals = results.to_list()
    print(vals)





main()

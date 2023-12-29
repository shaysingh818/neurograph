import cython
from pprint import pprint
from neurograph.structures import Matrix, batch_matrix
# from neurograph.graph import Graph
from neurograph.networks import Network
from neurograph.extractors import DataFrame


def main():


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

    results = mlp.predict(input=x_train[0]).to_list()
    print(results)



main()


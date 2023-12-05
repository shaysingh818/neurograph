import cython
from pprint import pprint
from neurograph.structures import Matrix, batch_matrix
from neurograph.graph import Graph

def main():

    # input 
    x = Matrix(rows=4, cols=2)
    x.array(entries=[[0,0],[0,1],[1,0],[1,1]])
    x_train = batch_matrix(mat_instance=x, batch_size=2)
    
    # expected output
    y = Matrix(rows=4, cols=1)
    y.array(entries=[[0],[1],[1],[0]])
    y_train = batch_matrix(mat_instance=y, batch_size=2)

    # # create mlp architecture
    # mlp = Network(learning_rate=0.01, value=val, batch_size=2)
    # mlp.linear(input_size=2, output_size=3)
    # mlp.activation(input_size=2, output_size=3, loss_type="tanh")
    # mlp.linear(input_size=3, output_size=1)
    # mlp.activation(input_size=3, output_size=1, loss_type="tanh")
    # mlp.batch_train(epochs=5000, output=y)

    # num_layers = mlp.num_layers()
    # print(num_layers)

    # test graph works
    g = Graph(vertices=10, directed=False)
    g.add_node(src_id=0, src="A", dst_id=1, dst="B", weight=5)
    g.add_node(src_id=0, src="A", dst_id=2, dst="C", weight=5)
    g.add_node(src_id=1, src="B", dst_id=2, dst="C", weight=15)
    g.add_node(src_id=1, src="B", dst_id=3, dst="D", weight=7)
    g.add_node(src_id=1, src="B", dst_id=4, dst="E", weight=8)
    g.add_node(src_id=2, src="C", dst_id=3, dst="D", weight=2)
    g.add_node(src_id=2, src="C", dst_id=5, dst="F", weight=4)
    g.add_node(src_id=3, src="D", dst_id=4, dst="E", weight=2)
    g.add_node(src_id=3, src="D", dst_id=5, dst="F", weight=9)
    g.add_node(src_id=3, src="D", dst_id=6, dst="G", weight=10)
    g.add_node(src_id=4, src="E", dst_id=6, dst="G", weight=3)
    results = g.adj_list()
    pprint(results)







main()

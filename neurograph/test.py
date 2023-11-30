import cython
from pprint import pprint
from neurograph.extractors import DataFrame
from neurograph.structures import Matrix
from neurograph.graph import Graph, SerializedGraph, DataFrameGraph, GraphWalk

def main():

    # create graph
    g = Graph(vertices=7, directed=False)
    g.add_node(src_id=0, src="A", dst_id=1, dst="B", weight=2)
    g.add_node(src_id=0, src="A", dst_id=2, dst="C", weight=6)
    g.add_node(src_id=1, src="B", dst_id=3, dst="D", weight=5)
    g.add_node(src_id=2, src="C", dst_id=3, dst="D", weight=8)
    g.add_node(src_id=3, src="D", dst_id=4, dst="E", weight=10)
    g.add_node(src_id=3, src="D", dst_id=5, dst="F", weight=15)
    g.add_node(src_id=4, src="E", dst_id=5, dst="F", weight=6)
    g.add_node(src_id=5, src="F", dst_id=6, dst="G", weight=6)
    g.add_node(src_id=4, src="E", dst_id=6, dst="G", weight=2)
    g.matrix()

    graph_walk = GraphWalk(
        graph=g, 
        start_vertex=0, 
        steps=10, 
        weighted=False,
        matrix=True
    )

    results = graph_walk.contents()
    pprint(results)







main()

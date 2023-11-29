import cython
from pprint import pprint
from neurograph.extractors import DataFrame
from neurograph.structures import Matrix
from neurograph.graph import Graph, SerializedGraph, DataFrameGraph, GraphWalk

def main():

    # create graph
    g = Graph(vertices=5, directed=False)
    g.add_node(src_id=0, src="A", dst_id=1, dst="B", weight=0)
    g.add_node(src_id=0, src="A", dst_id=2, dst="C", weight=5)
    g.add_node(src_id=0, src="A", dst_id=3, dst="D", weight=15)
    g.add_node(src_id=1, src="B", dst_id=2, dst="C", weight=7)
    g.add_node(src_id=4, src="E", dst_id=2, dst="C", weight=8)

    graph_walk = GraphWalk(graph=g, start_vertex=0, steps=10)
    pprint(graph_walk.contents())






main()

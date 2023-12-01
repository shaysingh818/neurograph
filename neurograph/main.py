import cython
from pprint import pprint
from neurograph.extractors import DataFrame
from neurograph.structures import Matrix
from neurograph.graph import Graph, SerializedGraph, DataFrameGraph, GraphWalk

def main():

    # create graph
    g = Graph(vertices=8, directed=True)
    g.add_node(src_id=0, src="A", dst_id=1, dst="B", weight=0)
    g.add_node(src_id=1, src="B", dst_id=2, dst="C", weight=0)
    g.add_node(src_id=2, src="C", dst_id=3, dst="D", weight=0)
    g.add_node(src_id=3, src="D", dst_id=0, dst="A", weight=0)

    # bridge
    g.add_node(src_id=2, src="C", dst_id=4, dst="E", weight=0)

    # second community
    g.add_node(src_id=4, src="E", dst_id=5, dst="F", weight=0)
    g.add_node(src_id=5, src="F", dst_id=6, dst="G", weight=0)
    g.add_node(src_id=6, src="G", dst_id=4, dst="E", weight=0)
    g.add_node(src_id=6, src="G", dst_id=7, dst="H", weight=0)
    g.add_end_node(src_id=7, src="H", weight=0)

    # label propagation
    g.kosaraju(start_vertex=0) 
    






main()

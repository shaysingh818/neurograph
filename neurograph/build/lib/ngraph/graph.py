from ctypes import  c_int,c_bool, c_char_p, POINTER
from ngraph.utils import load_library
from ngraph.structures import (
    AdjacencyList,
    AdjacencyMatrix,
    Walk,
    Node,
)


class Graph:

    def __init__(self, vertice_count):

        self.lib = load_library("neurograph.so")

        # Instantiate
        self.lib.init_graph.restype = POINTER(AdjacencyList)
        self.lib.init_graph.argtypes = [c_int, c_int, c_bool]
        self.adj_list = self.lib.init_graph(
            vertice_count, 
            vertice_count, 
            False
        )
        
    def add_node(
        self, 
        src_id: int, 
        src: str, 
        dst_id: int, 
        dst: str, 
        weight: int):

        self.lib.add_node.restype = c_int
        self.lib.add_node(
            self.adj_list,
            src_id, src, 
            dst_id, dst, weight
        )
    
    def shortest_path(self, start_vertex, end_vertex):
        self.lib.shortest_path.restype = c_int
        self.lib.shortest_path.argtypes = [POINTER(AdjacencyList), c_int, c_int]
        result = self.lib.shortest_path(
            self.adj_list, 
            start_vertex,
            end_vertex 
        )
        return result

    def dijkstra(self, start_vertex: int):
        self.lib.dijkstra.restype = POINTER(c_int)
        self.lib.dijkstra.argtypes = [POINTER(AdjacencyList), c_int]
        result = self.lib.dijkstra(self.adj_list, start_vertex)
        return result

    def print_graph(self):
        self.lib.print_graph(self.adj_list)



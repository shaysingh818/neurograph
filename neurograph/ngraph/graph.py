from ctypes import  c_int,c_bool, c_char_p, POINTER, pointer
from ngraph.queue_service import QueueService
from ngraph.utils import load_library
from ngraph.structures import (
    AdjacencyList,
    AdjacencyMatrix,
    Walk,
    Node,
    Queue
)


class Graph:

    def __init__(self, vertice_count):

        self.lib = load_library("neurograph.so")

        # Instantiate
        self.lib.init_graph.restype = POINTER(AdjacencyList)
        self.lib.init_graph.argtypes = [c_int, c_int, c_bool]
        self.vertices = vertice_count
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


    def bfs(self, start_vertex): 

        # Get node by ID
        self.lib.get_node_by_id.restype = POINTER(Node)
        self.lib.get_node_by_id.argtypes = [POINTER(AdjacencyList), c_int]
        node_item = self.lib.get_node_by_id(self.adj_list, start_vertex)        

        # call bfs method
        self.lib.bfs.restype = POINTER(Queue)
        self.lib.bfs.argtypes = [
            POINTER(AdjacencyList),
            POINTER(Node)
        ]
        results = self.lib.bfs(self.adj_list, node_item)
        return results


    def dfs(self, start_vertex, queue_service):

        # Get node by ID
        self.lib.get_node_by_id.restype = POINTER(Node)
        self.lib.get_node_by_id.argtypes = [POINTER(AdjacencyList), c_int]
        node_item = self.lib.get_node_by_id(self.adj_list, start_vertex)
        queue = queue_service.instance()

        # Perform dfs
        self.lib.dfs.restype = c_int
        self.lib.dfs.argtypes = [
            POINTER(Queue),
            POINTER(AdjacencyList),
            POINTER(Node)
        ]
        self.lib.dfs(queue, self.adj_list, node_item)


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


    def weighted_random_walk(self, steps: int, start_vertex: int):

        # create instance of walk structure
        self.lib.init_walk.restype = POINTER(Walk)
        self.lib.init_walk.argtypes = [c_int]
        walk = self.lib.init_walk(steps)

        # create instance of walk structure        
        self.lib.weighted_random_walk.restype = POINTER(Walk)
        self.lib.weighted_random_walk.argtypes = [POINTER(AdjacencyList), POINTER(Walk), c_int]
        walk_results = self.lib.weighted_random_walk(self.adj_list, walk, start_vertex)
        return walk_results
    
        # print walk results
        self.lib.print_walk.restype = None
        self.lib.print_walk.argtypes = [POINTER(Walk)]
        self.lib.print_walk(walk_results)
        

    def print_graph(self):
        self.lib.print_graph(self.adj_list)



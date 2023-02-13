from pprint import pprint
from ctypes import c_double, c_int,c_bool, CDLL
from ctypes import  *
import sys

# path to shared object library
lib_path = './diffusion.so'
graph_lib = CDLL(lib_path)


# create node structure
class Node(Structure):
    pass

# attach fields to node
Node._fields_ = [
    ("id", c_int), 
    ("weight", c_int), 
    ("label", c_char),
    ("next", POINTER(Node))
]

class NodeList(Structure):
    _fields_ = [("head", POINTER(Node))]


class Edge(Structure): 
    _fields_ = [
        ("weight", c_int), 
        ("src", POINTER(Node)),
        ("dst", POINTER(Node))
    ]


# node structure
class Graph(Structure):
    _fields_ = [
        ("v", c_int),
        ("e", c_int), 
        ("visited", POINTER(c_int)),
        ("directed", c_bool), 
        ("err", c_bool),
        ("edges", POINTER(POINTER(Edge))),
        ("items", POINTER(NodeList))
    ]


def graph_serialize(graph):
    
    body = {
        "vertice_count": graph.contents.v,
        "edge_count": graph.contents.e,
        "visited_nodes": graph.contents.visited,
        "directed": graph.contents.directed,
        "err": graph.contents.err,
        "edges": [],
        "items": []
    }

    # serialize edges
    print(graph.contents.edges)

    # serialize items

    return body
    
# get graph utils
graph_lib.init_graph_util.restype = POINTER(Graph)
result = graph_lib.init_graph_util(10)
json_result = graph_serialize(result)
pprint(json_result)

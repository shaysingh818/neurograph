from ctypes import c_double, c_int,c_bool, CDLL
from ctypes import  *

# create node structure
class Node(Structure):
    pass

# attach fields to node
Node._fields_ = [
    ("id", c_int),
    ("weight", c_int),
    ("label", c_char_p),
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

    def __init__(self):
        self.vertices = self.__fields_[0]
        
from ctypes import c_double, c_int,c_bool, c_uint, CDLL
from ctypes import  *

# Graph Structures
class Node(Structure):
    pass

Node._fields_ = [
    ("id", c_int),
    ("weight", c_int),
    ("label", c_char_p),
    ("next", POINTER(Node)),
    ("left", POINTER(Node)),
    ("right", POINTER(Node))
]

class NodeList(Structure):
    _fields_ = [("head", POINTER(Node))]

class Entry(Structure):
    _fields_ = [
        ("id", c_int),
        ("label", c_char_p),
    ]

class Edge(Structure):
    _fields_ = [
        ("weight", c_int),
        ("src", POINTER(Node)),
        ("dst", POINTER(Node))
    ]

class Walk(Structure):
    _fields_ = [
        ("path", POINTER(c_int)),
        ("steps", c_int),
        ("weighted_sum", c_int),
        ("cycles", c_int)
    ]

class AdjacencyList(Structure):
    _fields_ = [
        ("v", c_int),
        ("e", c_int),
        ("visited", POINTER(c_int)),
        ("used", POINTER(c_int)),
        ("directed", c_bool),
        ("err", c_bool),
        ("edges", POINTER(POINTER(Edge))),
        ("items", POINTER(NodeList))
    ]

class AdjacencyMatrix(Structure):
    _fields_ = [
        ("rows", c_int),
        ("cols", c_int),
        ("vertices", c_int),
        ("weights", POINTER(c_int)),
        ("matrix", POINTER(POINTER(Entry))),
    ]

# queueing 
class QueueItem(Structure):
    pass

QueueItem._fields_ = [
    ("integer", c_int),
    ("string", c_char_p),
    ("priority", c_int),
    ("node", POINTER(Node)),
    ("next", POINTER(QueueItem)),
]

class Queue(Structure):
    _fields_ = [
        ("capacity", c_uint),
        ("front_index", c_int),
        ("rear_index", c_int),
        ("item_count", c_int),
        ("front", POINTER(QueueItem)),
        ("rear", POINTER(QueueItem)),
        ("items", POINTER(POINTER(QueueItem))),
    ]
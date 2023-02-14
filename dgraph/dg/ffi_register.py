from ctypes import CDLL
from .d_types import Graph
from ctypes import  *

# load shared object file
lib_path = "../so_files/diffusion.so"
lib = CDLL(lib_path)

# init graph
lib.init_graph_util.restype = POINTER(Graph)

# add node
lib.add_node_util.restype = c_bool

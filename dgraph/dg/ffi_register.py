from ctypes import CDLL
from .d_types import Graph, AdjacencyList
from ctypes import  *
from ctypes.util import find_library
import os

lib_path = os.path.join(os.path.dirname(os.path.abspath(__file__)), 'lib', 'diffusion.so')
my_lib = CDLL(lib_path, use_errno=True)
if my_lib._handle is None:
    errno = get_errno()
    raise OSError(errno, os.strerror(errno))

# load shared object file
lib = CDLL(lib_path)

# init graph
lib.init_graph_util.restype = POINTER(Graph)

# add node
lib.add_node_util.restype = c_bool

# csv to graph
lib.g_to_csv_util.argtypes = [c_char_p, POINTER(c_int), c_int, c_int]
lib.g_to_csv_util.restype = POINTER(Graph)

from ctypes import CDLL
from ctypes import  *
import os


def load_library(filename):
    lib_path = os.path.join(os.path.dirname(os.path.abspath(__file__)), 'lib', filename)
    my_lib = CDLL(lib_path, use_errno=True)
    if my_lib._handle is None:
        errno = get_errno()
        raise OSError(errno, os.strerror(errno))
    lib = CDLL(lib_path)
    return lib
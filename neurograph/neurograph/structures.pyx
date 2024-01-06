# cython: boundscheck=True
import os
import sys
import re
import cython
from pathlib import Path
from libc.stdlib cimport malloc
from itertools import chain
cimport libneurograph.extractors.cframe as fr
cimport libneurograph.data_structures.clist as ll
cimport libneurograph.data_structures.cmatrix as matrix
cimport libneurograph.data_structures.cndarray as nd
from neurograph.extractors cimport DataFrame
from neurograph.networks import Value
from typing import List


cdef class ndarray:

    def __cinit__(self):
        self.nd = NULL

    def __init__(self, shape: List[int] = None, values: list = None, filepath: str = None):

        # validate args
        self.constructor_validation(shape, values, filepath)

        if filepath:
            # validate filepath argument
            if not os.path.exists(filepath):
                raise Exception(f"Path {filepath} does not exist")

            # create instance of ndarray from file path
            file_encode = filepath.encode('utf-8')
            self.nd = nd.load_ndarray(file_encode)
            if self.nd is NULL:
                print("We have a memory error")
                raise MemoryError()

        else:
            # create shape and rank attributes
            self.rank_order = len(shape)
            shape_size = 1
            self.shape_view = <int*>malloc(self.rank_order * sizeof(int))
            for i in range(self.rank_order):
                self.shape_view[i] = shape[i]
                shape_size *= shape[i]

            # validate shape array is the same as dimemnsion product
            converted_vals = self.shape_set(values)
            if len(converted_vals) != shape_size:
                raise Exception(f"Shape array length uneven: {shape_size} total values required")

            # create instance of ndarray 
            self.nd = nd.ndarray(self.rank_order, self.shape_view)
            if self.nd is NULL:
                print("We have a memory error")
                raise MemoryError()
            
            # copy values to shape array
            for i in range(len(converted_vals)):
                self.nd.values[i] = converted_vals[i]


    def constructor_validation(self, shape: List[int] = None, values: list = None, filepath: str = None):
        
        shape_exists = shape is not None
        values_exists = values is not None
        filepath_exists = filepath is not None

        if not shape_exists and not values_exists and not filepath_exists:
            raise Exception("Shape and Values or Filepath must be provided")

        if shape_exists and values_exists and filepath_exists:
            raise Exception("Too Many Aruments: Provide shape and values, or just a filepath")

        if shape_exists and values_exists and not filepath_exists:

            if len(values) == 0:
                raise Exception("NDArray Must have values")

            if len(shape) < 2:
                raise Exception("NDArray needs atleast 2 shape values")


    def add(self, value: ndarray):

        # validate rank
        if(value.rank() != self.nd.rank):
            raise Exception(f"Add: Values not of same rank")

        # validate size
        if value.size() != self.nd.size:
            raise Exception(f"Add: Values not of same size")

        self.nd = nd.nadd(self.nd, value.nd)
        if not self.nd.status:
            err_msg = self.nd.err_msg.decode('utf-8')
            raise Exception(err_msg)


    def subtract(self, value: ndarray):

        # validate rank
        if(value.rank() != self.nd.rank):
            raise Exception(f"Subtract: Values not of same rank")

        # validate size
        if value.size() != self.nd.size:
            raise Exception(f"Subtract: Values not of same size")

        self.nd = nd.nsubtract(self.nd, value.nd)
        if not self.nd.status:
            err_msg = self.nd.err_msg.decode('utf-8')
            raise Exception(err_msg)


    def dot(self, value: ndarray):

        if self.nd.shape[0] != value.nd.shape[value.nd.rank-1]:
            raise Exception("Dot: dimension mismatch")
        
        if self.nd.rank != value.rank():
            raise Exception("Dot: Rank mismatch")
        
        self.nd = nd.ndot(self.nd, value.nd)
        if not self.nd.status:
            err_msg = self.nd.err_msg.decode('utf-8')
            raise Exception(err_msg)


    def scale_add(self, value: ndarray):

        if self.nd.rank != 2:
            raise Exception("Scale Add: Must have rank of atleast 2")

        if self.nd.shape[self.nd.rank-1] != value.size():
            raise Exception("Scale Add: Axis cols don't match")

        self.nd = nd.nscale_add(self.nd, value.nd) 
        if not self.nd.status:
            err_msg = self.nd.err_msg.decode('utf-8')
            raise Exception(err_msg)


    def transpose(self):

        if self.nd.rank != 2:
            raise Exception("Transpose: Must have rank of atleast 2")

        self.nd = nd.ntranspose(self.nd)
        if not self.nd.status:
            err_msg = self.nd.err_msg.decode('utf-8')
            raise Exception(err_msg)


    def permute(self, indice_order: List[int]): 

        if len(indice_order) != self.nd.rank:
            raise Exception("Permute: shape length does not match rank")

        cdef int* shape_view = <int*>malloc(self.rank_order * sizeof(int))
        for i in range(self.rank_order):
            shape_view[i] = indice_order[i]

        self.nd = nd.permute(self.nd, shape_view)
        if not self.nd.status:
            err_msg = self.nd.err_msg.decode('utf-8')
            raise Exception(err_msg)


    def save(self, path: str, name: str):

        if not os.path.exists(path):
            raise Exception(f"Save: filepath {path} does not exist")

        # join path
        file_path = os.path.join(path, name)
        file_encode = file_path.encode('utf-8')
        nd.save_ndarray(self.nd, file_encode)


    def values(self):
        values = []
        for i in range(self.nd.size):
            values.append(self.nd.values[i])
        return values


    def shape(self):
        shape = ()
        for item in range(self.nd.rank):
            shape_val = self.nd.shape[item]
            shape = shape + (shape_val,)
        return shape


    def shape_set(self, values: any):
        as_bytes = str(values)
        brackets = as_bytes.replace("[" , "").replace("]", "")
        strip_whitespace = re.sub('[\s+]', '', brackets)
        str_list_vals = brackets.split(",")
        list_vals = [ float(x) for x in str_list_vals ]
        return list_vals


    def size(self):
        return self.nd.size


    def rank(self):
        return self.nd.rank

        
    def debug(self):
        nd.print_tensor(self.nd)


cdef class Matrix:

    def __cinit__(self):
        self.mat = NULL

    def __init__(self, rows, cols):
        self.mat = matrix.init_matrix(rows, cols)
        if self.mat is NULL:
            print("We have a memory error")
            raise MemoryError()

    def set_matrix(self, my_mat: Matrix):
        self.mat = matrix.copy_matrix(my_mat.mat)

    def print_mat(self):
        matrix.print_vec(self.mat)

    def rows(self):
        return self.mat.rows

    def cols(self):
        return self.mat.cols

    def to_value(self):
        val = Value(self)
        return val

    def array(self, entries: List[List[float]]):
        for i in range(len(entries)):
            for j in range(len(entries[i])):
                matrix.entry(self.mat, i, j, entries[i][j])

    def to_list(self):
        result_list = []
        for i in range(self.mat.rows):
            temp = []
            for j in range(self.mat.cols):
                value = matrix.get(self.mat, i, j)
                convert = f"{value:.2f}"
                val = float(convert)
                temp.append(val)
            result_list.append(temp)
        return result_list


def batch_matrix(mat_instance: Matrix, batch_size: int) -> List[Matrix]:
    result_list = []
    results = matrix.batch_matrix(mat_instance.mat, batch_size)
    result_len = mat_instance.mat.rows - batch_size
    # for i in range(result_len):
    #     m = Matrix(rows=results[i].rows, cols=results[i].cols)
    #     m.mat = results[i]
    #     result_list.append(m)
    return result_list


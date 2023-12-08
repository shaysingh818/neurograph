# cython: boundscheck=True

cimport libneurograph.extractors.cframe as fr
cimport libneurograph.data_structures.clist as ll
cimport libneurograph.data_structures.cmatrix as matrix
from neurograph.extractors cimport DataFrame
from neurograph.networks import Value
from typing import List


cdef class Matrix:

    def __cinit__(self):
        self.mat = NULL

    def __init__(self, rows, cols):
        self.mat = matrix.init_matrix(rows, cols)
        if self.mat is NULL:
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
    for i in range(result_len):
        m = Matrix(results[i].rows, results[i].cols)
        m.mat = results[i]
        result_list.append(m)
    return result_list


cimport pxds.extractors.cframe as fr
cimport pxds.data_structures.cll as ll
cimport pxds.data_structures.cmatrix as matrix
from neurograph.extractors cimport DataFrame

cdef class Matrix:

    def __cinit__(self):
        self.mat = NULL

    def __init__(self, rows, cols):
        self.mat = matrix.init_matrix(rows, cols)

    def __init__(self, dataframe: DataFrame, cols: list):
        selected_cols = ll.init_array()
        for item in cols:
            ll.insert_char(selected_cols, bytes(item, encoding="utf8"))
 
        self.mat = fr.frame_to_matrix(dataframe.frame, selected_cols)

    def set_matrix(self, my_mat: Matrix):
        self.mat = matrix.copy_matrix(my_mat.mat)

    def print_mat(self):
        matrix.print_vec(self.mat)
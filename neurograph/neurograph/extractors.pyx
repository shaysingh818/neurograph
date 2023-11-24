cimport pxds.extractors.cframe as fr
cimport pxds.data_structures.clist as ll
cimport pxds.data_structures.cmatrix as matrix
from tabulate import tabulate

cdef class DataFrame:

    def __cinit__(self):
        self.frame = NULL
        self.mat = NULL

    def __init__(self, filepath, row_limit):
        encoded_filepath = filepath.encode("utf-8")
        self.frame = fr.dataframe(encoded_filepath, 1024, row_limit, ",")
        self.selected_cols = ll.init_array()
        if self.frame is NULL:
            raise MemoryError()
 
    def features(self):
        fr.print_cols(self.frame)

    def view_selected_features(self):
        ll.print_array(self.selected_cols)



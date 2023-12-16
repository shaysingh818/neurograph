cimport libneurograph.extractors.cframe as fr
cimport libneurograph.data_structures.clist as ll
cimport libneurograph.data_structures.cmatrix as matrix

cdef class Matrix:
    cdef matrix.Matrix *mat
    cdef ll.Array *selected_cols 
    cdef fr.Frame *frame
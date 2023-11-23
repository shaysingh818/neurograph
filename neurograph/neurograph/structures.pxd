cimport pxds.extractors.cframe as fr
cimport pxds.data_structures.cll as ll
cimport pxds.data_structures.cmatrix as matrix

cdef class Matrix:

    cdef matrix.Matrix *mat
    cdef ll.Array *selected_cols 
    cdef fr.Frame *frame 
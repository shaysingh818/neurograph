cimport pxds.extractors.cframe as fr
cimport pxds.data_structures.cll as ll
cimport pxds.data_structures.cmatrix as matrix

cdef class DataFrame:

    cdef fr.Frame *frame
    cdef ll.Array *selected_cols
    cdef matrix.Matrix *mat

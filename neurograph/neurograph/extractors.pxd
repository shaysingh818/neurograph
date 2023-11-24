cimport libneurograph.extractors.cframe as fr
cimport libneurograph.data_structures.clist as ll
cimport libneurograph.data_structures.cmatrix as matrix

cdef class DataFrame:

    cdef fr.Frame *frame
    cdef ll.Array *selected_cols
    cdef matrix.Matrix *mat

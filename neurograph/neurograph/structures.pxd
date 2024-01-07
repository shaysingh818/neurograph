cimport libneurograph.extractors.cframe as fr
cimport libneurograph.data_structures.clist as ll
cimport libneurograph.data_structures.cmatrix as matrix
cimport libneurograph.data_structures.cndarray as nd

cdef class ndarray:
    cdef int* shape_view
    cdef int rank_order
    cdef nd.NDArray *nd


cdef class Matrix:
    cdef matrix.Matrix *mat
    cdef ll.Array *selected_cols 
    cdef fr.Frame *frame
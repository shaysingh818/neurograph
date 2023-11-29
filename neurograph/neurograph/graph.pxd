cimport libneurograph.extractors.cframe as fr
cimport libneurograph.data_structures.clist as ll
cimport libneurograph.extractors.cframe as fr
cimport libneurograph.graph.cgraph as gr
from neurograph.extractors cimport DataFrame

cdef class Graph:
    cdef gr.Graph *graph
    cdef gr.Walk *walk
    cdef int v
    cdef bint directed


cdef class SerializedGraph(Graph):
    cdef str filename
    cdef int file_size


cdef class DataFrameGraph(Graph):
    cdef ll.Array *columns
    cdef DataFrame frame
    cdef int file_size


cdef class Walk():
    cdef gr.Walk *walk
    cdef int steps
    cdef int weighted_sum
    cdef int cycles


cdef class GraphWalk(Walk):
    cdef gr.Graph *graph
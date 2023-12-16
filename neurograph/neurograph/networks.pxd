cimport libneurograph.computation_graph.cvalue as val
cimport libneurograph.networks.cnetwork as net
cimport libneurograph.networks.clayer as la

cdef class Value:
    cdef val.Value *value


cdef class Network:
    cdef net.Network *network
    cdef int num_layers
    cdef bint batched


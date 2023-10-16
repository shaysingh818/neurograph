# node.pyx

cimport node

@cython.cclass
class Node:

    _c_node: cython.pointer(cnode.Node)

    def __cinit__(self, id: int, label: str, weight: id):
        self._c_node = cnode.create_node(id, label, weight)
        if self._c_node is cython.NULL:
            raise MemoryError()

from ctypes import  c_uint, c_int, c_bool, c_char_p, POINTER, pointer
from ngraph.utils import load_library
from ngraph.structures import (
    Node,
    QueueItem,
    Queue
)

class QueueService:

    def __init__(self, capacity):
        self.lib = load_library("neurograph.so")
        self.lib.init_queue.restype = POINTER(Queue)
        self.lib.init_queue.argtypes = [c_uint]
        self.capacity = capacity
        self.q = self.lib.init_queue(capacity)

    def instance(self):
        return self.q

    def set_instance(self, instance):
        self.q = instance
    
    def print_queue(self):
        self.lib.print_queue.restype = None
        self.lib.print_queue.argtypes = [POINTER(Queue)]
        self.lib.print_queue(self.q)

    def push(self, item: int, label: str, priority: int):

        # convert label to bytes
        label_to_bytes = bytes(label, 'utf-8')

        # bind create node function 
        self.lib.create_node.restype = POINTER(Node)
        self.lib.create_node.argtypes = [
            c_int, c_char_p, c_int
        ]

        # create node instance 
        node_instance = self.lib.create_node(
            item, 
            label_to_bytes, 
            priority
        )

        # bind create queue item function
        self.lib.init_item.restype = POINTER(QueueItem)
        self.lib.init_item.argtypes = [
            c_int, c_char_p, c_int, POINTER(Node)
        ]

        # create item instance
        item = self.lib.init_item(
            item, 
            label_to_bytes, 
            0, node_instance
        )

        # bind push function
        self.lib.push.restype = None
        self.lib.push.argtypes = [
            POINTER(Queue), POINTER(QueueItem)
        ]
        self.lib.push(self.q, item)

    def pop(self): 
        self.lib.pop.restype = None
        self.lib.pop.argtypes = [POINTER(Queue)]
        self.lib.pop()


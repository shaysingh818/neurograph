from ctypes import  c_uint, c_int, c_bool, c_char_p, POINTER
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
        self.q = self.lib.init_queue(capacity)

    def push(self, item: int):

        # create node for queueitem
        node = Node()
        node.id = 69
        node.weight = 0
        node.label = b"random"
        node.next = None
        node.left = None
        node.right = None

        # create queue item
        my_item = QueueItem()
        my_item.integer = 69
        my_item.string = b"test"
        my_item.priority = 0
        my_item.next = None

        self.lib.push.restype = None
        self.lib.push.argtypes = [
            POINTER(Queue), POINTER(QueueItem)
        ]
        self.lib.push(self.q, my_item)

    def pop(self):
        pass

    def print_queue(self):
        self.lib.print_queue.restype = None
        self.lib.print_queue.argtypes = [POINTER(Queue)]
        self.lib.print_queue(self.q)        

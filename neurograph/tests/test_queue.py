import unittest
from ngraph.queue_service import QueueService


class TestQueuehMethods(unittest.TestCase):

    def test_queue_obj(self):
        queue_instance = QueueService(100)
        queue_instance.push(item=1)
        queue_instance.push(item=2)
        queue_instance.push(item=3)


if __name__ == '__main__':
    unittest.main()
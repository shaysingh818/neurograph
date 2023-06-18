import unittest
from ngraph.queue_service import QueueService


class TestQueuehMethods(unittest.TestCase):

    def test_queue_obj(self):

        # create instance and push items
        queue_instance = QueueService(capacity=7)
        queue_instance.push(item=1, label="A", priority=0)
        queue_instance.push(item=2, label="B", priority=0)
        queue_instance.push(item=3, label="C", priority=0)
        queue_instance.push(item=4, label="D", priority=0)
        queue_instance.push(item=5, label="E", priority=0)
        queue_instance.push(item=6, label="F", priority=0)
        queue_instance.push(item=7, label="G", priority=0)

        # validate attributes
        self.assertEqual(queue_instance.q.contents.item_count, 7)
        self.assertEqual(queue_instance.q.contents.capacity, 7)

        queue_instance.pop()

        # count should be one less
        self.assertEqual(queue_instance.q.contents.item_count, 6)
        self.assertEqual(queue_instance.q.contents.capacity, 7)

if __name__ == '__main__':
    unittest.main()
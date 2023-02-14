from pprint import pprint
import unittest
import os.path
import sys
sys.path.append("..")

from dg import *

class TestGraphMethods(unittest.TestCase):

    def test_init_graph(self):
        
        # test creating a graph
        graph = init_graph(
            vertice_count=10, 
            directed=False
        )

        # serialize graph result
        result = graph_serialize(graph)

        # validate
        self.assertTrue(result["edge_count"], 10)
        self.assertTrue(result["vertice_count"], 10)
        self.assertEqual(result["directed"], False)

    def test_add_node(self):
        pass

    def test_serialize_graph(self):

        # validate relationships
        node_1 = ['B', 'C', 'D']
        node_2 = ['A', 'C']
        node_3 = ['A', 'B', 'E']
        node_4 = ['A']
        node_5 = ['C']

        #self.assertEqual(result["items"][0], node_1)
        #self.assertEqual(result["items"][1], node_2)
        #self.assertEqual(result["items"][2], node_3)
        #self.assertEqual(result["items"][3], node_4)
        #self.assertEqual(result["items"][4], node_5)
        pass


if __name__ == '__main__':
    unittest.main()

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

        # check amount of nodes in graph
        nodes = result["items"].keys()
        node_count = len(nodes)
        self.assertTrue(node_count, result["vertice_count"])


    def test_add_node(self):

        # create graph of size 10
        graph = init_graph(
            vertice_count=10, 
            directed=False
        )

        # add nodes to graph
        add_node(graph, 0, "A", 1, "B", 0) 
        add_node(graph, 0, "A", 2, "C", 0)
        add_node(graph, 0, "A", 3, "D", 0)
        add_node(graph, 1, "B", 2, "C", 0)
        add_node(graph, 4, "E", 2, "C", 0)

        # serialize graph
        result = graph_serialize(graph)

        # validate node relationships
        node_1 = ['B', 'C', 'D']
        node_2 = ['A', 'C']
        node_3 = ['A', 'B', 'E']
        node_4 = ['A']
        node_5 = ['C']

        self.assertEqual(result["items"][0], node_1)
        self.assertEqual(result["items"][1], node_2)
        self.assertEqual(result["items"][2], node_3)
        self.assertEqual(result["items"][3], node_4)
        self.assertEqual(result["items"][4], node_5)

    def test_add_directed_node(self):

        # create graph of size 10
        graph = init_graph(
            vertice_count=10, 
            directed=True
        )

        # add nodes to graph
        add_node(graph, 0, "A", 1, "B", 0) 
        add_node(graph, 0, "A", 2, "C", 0)
        add_node(graph, 0, "A", 3, "D", 0)
        add_node(graph, 1, "B", 2, "C", 0)
        add_node(graph, 4, "E", 2, "C", 0)

        # serialize graph
        result = graph_serialize(graph)

        # validate relationships
        node_1 = ['B', 'C', 'D']
        node_2 = ['C']
        node_3 = []
        node_4 = []
        node_5 = ['C']

        self.assertEqual(result["items"][0], node_1)
        self.assertEqual(result["items"][1], node_2)
        self.assertEqual(result["items"][2], node_3)
        self.assertEqual(result["items"][3], node_4)
        self.assertEqual(result["items"][4], node_5)

    def test_serialize_graph(self):

        # create graph of size 10
        graph = init_graph(
            vertice_count=10, 
            directed=True
        )
        
        # add nodes to graph
        add_node(graph, 0, "A", 1, "B", 0) 
        add_node(graph, 0, "A", 2, "C", 0)
        add_node(graph, 0, "A", 3, "D", 0)
        add_node(graph, 1, "B", 2, "C", 0)
        add_node(graph, 4, "E", 2, "C", 0)

        result = graph_serialize(graph)

        # graph serializer result
        g_result = {
            "directed": True, 
            "edge_count": 10, 
            "edges": [],
            "err": False, 
            "items": {
                0 : ['B', 'C', 'D'],
                1 : ['C'],
                2 : [],
                3 : [],
                4 : ['C'],
                5 : [],
                6 : [],
                7 : [],
                8 : [],
                9 : [],
            },
            "vertice_count": 10, 
            "visited_nodes": []
        }

        # check if serialization is equal
        self.assertEqual(result, g_result)

if __name__ == '__main__':
    unittest.main()

import unittest
from ctypes import POINTER
from ngraph import Graph, QueueService
from ngraph.structures import Queue
from pprint import pprint

class TestGraphMethods(unittest.TestCase):

    def test_graph_obj(self):

        # initiate graph
        testing = Graph(7)
        testing.add_node(0, "A", 1, "B", 100)
        testing.add_node(0, "A", 2, "C", 100)
        testing.add_node(0, "A", 3, "D", 100) 
        testing.add_node(1, "B", 2, "C", 100)
        testing.add_node(4, "E", 2, "C", 100)
    
        # confirm all attributes in core lib are set
        vertices = testing.adj_list.contents.v
        edges = testing.adj_list.contents.e
        directed = testing.adj_list.contents.directed
        err = testing.adj_list.contents.err

        # asserts
        self.assertEqual(vertices, 7)
        self.assertEqual(edges, 7)
        self.assertEqual(directed, True)
        self.assertEqual(err, False)

    def test_dijkstra(self):

        # create a graph
        graph = Graph(7)
        graph.add_node(0, "A", 1, "B", 2)
        graph.add_node(0, "A", 2, "C", 6)
        graph.add_node(1, "B", 3, "D", 5)
        graph.add_node(2, "C", 3, "D", 8)
        graph.add_node(3, "D", 4, "E", 10)
        graph.add_node(3, "D", 5, "F", 15)
        graph.add_node(4, "E", 5, "F", 6)
        graph.add_node(5, "F", 6, "G", 6)
        graph.add_node(4, "E", 6, "G", 2)

        validation = True
        start_vertex = 0
        expected_outputs = [0,2,6,7,17,22,19]
        result = graph.dijkstra(start_vertex=start_vertex)
        for i in range(graph.vertices):
            if result[i] != expected_outputs[i]:
                validation = False

        self.assertEqual(validation, True)

    def test_shortest_path(self):
        
        # initiate graph
        graph = Graph(7)
        graph.add_node(0, "A", 1, "B", 2)
        graph.add_node(0, "A", 2, "C", 6)
        graph.add_node(1, "B", 3, "D", 5)
        graph.add_node(2, "C", 3, "D", 8)
        graph.add_node(3, "D", 4, "E", 10)
        graph.add_node(3, "D", 5, "F", 15)
        graph.add_node(4, "E", 5, "F", 6)
        graph.add_node(5, "F", 6, "G", 6)
        graph.add_node(4, "E", 6, "G", 2)

        # # iterate through vertices and perform dijkstra
        validation = True
        for i in range(graph.vertices):
            dijkstra_result = graph.dijkstra(start_vertex=i)
            for j in range(graph.vertices):
                temp_result = graph.shortest_path(i, j)
                if temp_result != dijkstra_result[j]:
                    validation = False

        self.assertEqual(validation, True)

    def test_bfs(self):

        # init graph 
        graph = Graph(7)
        graph.add_node(0, "A", 1, "B", 2)
        graph.add_node(0, "A", 2, "C", 6)
        graph.add_node(1, "B", 3, "D", 5)
        graph.add_node(2, "C", 3, "D", 8)
        graph.add_node(3, "D", 4, "E", 10)
        graph.add_node(3, "D", 5, "F", 15)
        graph.add_node(4, "E", 5, "F", 6)
        graph.add_node(5, "F", 6, "G", 6)
        graph.add_node(4, "E", 6, "G", 2)

        # create queue to store bfs results 
        result = graph.bfs(start_vertex=0)

        # asserts
        self.assertEqual(result.contents.capacity, 7)
        self.assertEqual(result.contents.front_index, 0)
        self.assertEqual(result.contents.rear_index, 6)
        self.assertEqual(result.contents.item_count, 7)

    def test_dfs(self):
        
        # init graph 
        graph = Graph(7)
        graph.add_node(0, "A", 1, "B", 2)
        graph.add_node(0, "A", 2, "C", 6)
        graph.add_node(1, "B", 3, "D", 5)
        graph.add_node(2, "C", 3, "D", 8)
        graph.add_node(3, "D", 4, "E", 10)
        graph.add_node(3, "D", 5, "F", 15)
        graph.add_node(4, "E", 5, "F", 6)
        graph.add_node(5, "F", 6, "G", 6)
        graph.add_node(4, "E", 6, "G", 2)

        # create queue for storing results
        queue = QueueService(capacity=7)
        graph.dfs(start_vertex=0, queue_service=queue)

        # assert queue attributes are correct
        self.assertEqual(queue.q.contents.capacity, 7)
        self.assertEqual(queue.q.contents.front_index, 0)
        self.assertEqual(queue.q.contents.rear_index, 6)
        self.assertEqual(queue.q.contents.item_count, 7)
    
    def test_weighted_random_walk(self):
        
        # init graph 
        graph = Graph(7)
        graph.add_node(0, "A", 1, "B", 2)
        graph.add_node(0, "A", 2, "C", 6)
        graph.add_node(1, "B", 3, "D", 5)
        graph.add_node(2, "C", 3, "D", 8)
        graph.add_node(3, "D", 4, "E", 10)
        graph.add_node(3, "D", 5, "F", 15)
        graph.add_node(4, "E", 5, "F", 6)
        graph.add_node(5, "F", 6, "G", 6)
        graph.add_node(4, "E", 6, "G", 2)

        # call weighted random walk
        walk = graph.weighted_random_walk(start_vertex=0, steps=10)

        # print walk results
        self.assertEqual(walk.contents.cycles, 0)
        self.assertTrue(walk.contents.weighted_sum > 0)
        

if __name__ == '__main__':
    unittest.main()

import unittest
from pprint import pprint
from neurograph.graph import Graph, SerializedGraph, DataFrameGraph, GraphWalk
from neurograph.extractors import DataFrame
import os

class TestGraphMethods(unittest.TestCase):

    def test_create_graph(self):

        # create graph
        g = Graph(vertices=10, directed=False)
        g.add_node(src_id=0, src="A", dst_id=1, dst="B", weight=5)
        g.add_node(src_id=0, src="A", dst_id=2, dst="C", weight=5)
        g.add_node(src_id=1, src="B", dst_id=2, dst="C", weight=15)
        g.add_node(src_id=1, src="B", dst_id=3, dst="D", weight=7)
        g.add_node(src_id=1, src="B", dst_id=4, dst="E", weight=8)
        g.add_node(src_id=2, src="C", dst_id=3, dst="D", weight=2)
        g.add_node(src_id=2, src="C", dst_id=5, dst="F", weight=4)
        g.add_node(src_id=3, src="D", dst_id=4, dst="E", weight=2)
        g.add_node(src_id=3, src="D", dst_id=5, dst="F", weight=9)
        g.add_node(src_id=3, src="D", dst_id=6, dst="G", weight=10)
        g.add_node(src_id=4, src="E", dst_id=6, dst="G", weight=3)
        results = g.contents()

        # expected output from graph contents 
        expected_results = [
            [(1, 'B'), (2, 'C')],
            [(0, 'A'), (2, 'C'), (3, 'D'), (4, 'E')],
            [(0, 'A'), (1, 'B'), (3, 'D'), (5, 'F')],
            [(1, 'B'), (2, 'C'), (4, 'E'), (5, 'F'), (6, 'G')],
            [(1, 'B'), (3, 'D'), (6, 'G')],
            [(2, 'C'), (3, 'D')],
            [(3, 'D'), (4, 'E')],
            [],
            [],
            []
        ]

        # validate results 
        for i in range(10):
            self.assertEqual(results[i], expected_results[i])

    def test_serialize_graph(self):

        # create graph
        g = SerializedGraph(
            filename="../examples/gml/unit_tests/standard2.gmul",
            file_size=1024,
            directed=False # directed gives nodes with 0 relationships
        )

        directed_g = SerializedGraph(
            filename="../examples/gml/unit_tests/standard2.gmul",
            file_size=1024,
            directed=True # directed gives nodes with 0 relationships
        )

        d_results = directed_g.contents()
        results = g.contents()

        # expected output from graph contents 
        directed_results = [
            [(3, 'D')],
            [],
            [(3, 'D')],
            [(4, 'E')],
            [(5, 'F')],
            [(6, 'G'), (1, 'B')],
            []
        ]

        nond_results = [
            [(3, 'D')],
            [(5, 'F')],
            [(3, 'D')],
            [(0, 'A'), (2, 'C'), (4, 'E')],
            [(3, 'D'), (5, 'F')],
            [(4, 'E'), (6, 'G'), (1, 'B')],
            [(5, 'F')]
        ]

        # validate results 
        for i in range(7):
            self.assertEqual(d_results[i], directed_results[i])

        # validate results 
        for i in range(7):
            self.assertEqual(results[i], nond_results[i])

        # save graph
        g.save(output_path='test.gmul')
        self.assertEqual(os.path.exists("test.gmul"), True)

    def test_dataframe_graph(self):

        # create frame
        df = DataFrame(
            filepath="../examples/data/movies.csv",
            row_limit=5,
            memory_size=1024
        )

        # create graph from frame
        df_graph = DataFrameGraph(
            dataframe=df,
            cols=["category", "genre"],
            directed=False,
            weighted=False
        )
        results = df_graph.contents()

        nond_results = [
           [
            (1, '"Crime, Drama"'),
            (2, '"Crime, Drama, Thriller"'),
            (5, 'Drama'),
            (6, '"Drama, Horror"')
            ], 
            [(0, 'R')],
            [(0, 'R')],
            [(4, '"Action, Adventure, Fantasy"')],
            [(3, 'PG')],
            [(0, 'R')],
            [(0, 'R')],
            [],
            [],
            []
        ]

        # validate results 
        for i in range(len(results.keys())):
            self.assertEqual(results[i], nond_results[i])


    def test_dijkstra(self):
        
        # create graph
        g = Graph(vertices=7, directed=False)
        g.add_node(src_id=0, src="A", dst_id=1, dst="B", weight=2)
        g.add_node(src_id=0, src="A", dst_id=2, dst="C", weight=6)
        g.add_node(src_id=1, src="B", dst_id=3, dst="D", weight=5)
        g.add_node(src_id=2, src="C", dst_id=3, dst="D", weight=8)
        g.add_node(src_id=3, src="D", dst_id=4, dst="E", weight=10)
        g.add_node(src_id=3, src="D", dst_id=5, dst="F", weight=15)
        g.add_node(src_id=4, src="E", dst_id=5, dst="F", weight=6)
        g.add_node(src_id=5, src="F", dst_id=6, dst="G", weight=6)
        g.add_node(src_id=4, src="E", dst_id=6, dst="G", weight=2)
        results = g.dijkstra(start_vertex=0)
        expected = [0, 2, 6, 7, 17, 22, 19]
        self.assertEqual(results, expected)



    def test_shortest_path(self):

        # create graph
        g = Graph(vertices=7, directed=False)
        g.add_node(src_id=0, src="A", dst_id=1, dst="B", weight=2)
        g.add_node(src_id=0, src="A", dst_id=2, dst="C", weight=6)
        g.add_node(src_id=1, src="B", dst_id=3, dst="D", weight=5)
        g.add_node(src_id=2, src="C", dst_id=3, dst="D", weight=8)
        g.add_node(src_id=3, src="D", dst_id=4, dst="E", weight=10)
        g.add_node(src_id=3, src="D", dst_id=5, dst="F", weight=15)
        g.add_node(src_id=4, src="E", dst_id=5, dst="F", weight=6)
        g.add_node(src_id=5, src="F", dst_id=6, dst="G", weight=6)
        g.add_node(src_id=4, src="E", dst_id=6, dst="G", weight=2)
        results = g.shortest_path(start_vertex=0, end_vertex=3)

        for i in range(g.vertices()):
            start_vertex = i
            results = g.dijkstra(start_vertex=start_vertex)
            for j in range(g.vertices()):
                temp_result = g.shortest_path(start_vertex=start_vertex, end_vertex=j)
                self.assertEqual(temp_result, results[j])

    def test_random_walk(self):
        
        # create graph
        g = Graph(vertices=5, directed=False)
        g.add_node(src_id=0, src="A", dst_id=1, dst="B", weight=0)
        g.add_node(src_id=0, src="A", dst_id=2, dst="C", weight=5)
        g.add_node(src_id=0, src="A", dst_id=3, dst="D", weight=15)
        g.add_node(src_id=1, src="B", dst_id=2, dst="C", weight=7)
        g.add_node(src_id=4, src="E", dst_id=2, dst="C", weight=8)

        graph_walk = GraphWalk(graph=g, start_vertex=0, steps=10)
        results = graph_walk.contents()

        self.assertEqual(results["cycles"], 0)
        self.assertEqual(results["steps"], 10)
        self.assertEqual(results["weighted_sum"], 0)
        self.assertEqual(len(results["path"]), 10)

    def test_bfs(self):
        pass

    def test_dfs(self):
        pass    
    
    def test_weighted_random_walk(self):
        pass
        

if __name__ == '__main__':
    unittest.main()

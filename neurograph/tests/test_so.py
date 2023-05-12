from pprint import pprint
import unittest
import os.path
import sys
sys.path.append("..")
from ngraph import *
import pathlib

class TestSharedObject(unittest.TestCase):

    def test_shared_object_reference(self):

        graph = init_graph(
            vertice_count=10, 
            directed=False
        )

        add_node(graph, 0, "A", 1, "B", 0) 
        add_node(graph, 0, "A", 2, "C", 0)
        add_node(graph, 0, "A", 3, "D", 0)
        add_node(graph, 1, "B", 2, "C", 0)
        add_node(graph, 4, "E", 2, "C", 0)


        result = graph_serialize(graph)
        pprint(result)

        # print current path
        curr_path = pathlib.Path(__file__).parent.resolve()
        print(curr_path)

    def test_tsv(self):

        csv_graph = graph_to_csv(
            filename="../../examples/data/power_generation.csv",
            features=[1,3],
            size=2,
            row_limit=10
        )

        graph_result = graph_serialize(csv_graph)
        pprint(graph_result)


        


if __name__ == '__main__':
    unittest.main()

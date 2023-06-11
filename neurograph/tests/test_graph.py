import unittest
from ngraph import Graph

class TestGraphMethods(unittest.TestCase):

    def test_graph_obj(self):

        testing = Graph(7)
        testing.add_node(0, "A", 1, "B", 100)
        testing.add_node(0, "A", 2, "C", 100)
        testing.add_node(0, "A", 3, "D", 100)
        testing.print_graph()
    
        result = testing.shortest_path(0, 3)
        print(result)

        

if __name__ == '__main__':
    unittest.main()

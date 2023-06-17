from ctypes import POINTER, pointer
from graph import Graph
from queue_service import QueueService
from pprint import pprint
from structures import (
    Node,
    QueueItem
)

def main():

    # graph structure 
    testing = Graph(7)
    testing.add_node(0, "A", 1, "B", 100)
    testing.add_node(0, "A", 2, "C", 100)
    testing.add_node(0, "A", 3, "D", 100)
    testing.add_node(1, "B", 2, "C", 100)
    testing.add_node(4, "E", 2, "C", 100)
    testing.print_graph()
    print("\n")
 
    # Depth first search results
    print("DFS Results")
    print("============================")
    queue_service = QueueService(7)
    testing.dfs(1, queue_service=queue_service)

    # Random Walk results
    print("Weighted Random Walk Results")
    print("============================")
    testing.weighted_random_walk(steps=10, start_vertex=0)




main()

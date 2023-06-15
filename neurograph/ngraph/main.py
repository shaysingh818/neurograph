from ctypes import POINTER, pointer
from graph import Graph
from queue_service import QueueService
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
    
    # get shortest path results
    result = testing.shortest_path(0, 3)
    print("Shortest path results: ", result)
    print("\n")

    # Breath first search results
    print("BFS Results")
    testing.bfs(0)

    # Depth first search results
    print("DFS Results")






    

main()

from graph import Graph
from queue_service import QueueService

def main():

    # graph structure 
    testing = Graph(7)
    testing.add_node(0, "A", 1, "B", 100)
    testing.add_node(0, "A", 2, "C", 100)
    testing.add_node(0, "A", 3, "D", 100)
    testing.print_graph()
    
    result = testing.shortest_path(0, 3)
    print(result)

    # queue structure
    print("Queue tests go here: ")
    instance = QueueService(100)
    instance.push(1)
    instance.push(2)
    instance.push(3)
    instance.push(4)
    instance.print_queue()
    

main()

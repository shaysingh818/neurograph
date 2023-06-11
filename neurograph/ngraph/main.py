from graph import Graph


def main():

    testing = Graph(7)
    testing.add_node(0, "A", 1, "B", 100)
    testing.add_node(0, "A", 2, "C", 100)
    testing.add_node(0, "A", 3, "D", 100)
    testing.print_graph()
    
    result = testing.shortest_path(0, 3)
    print(result)

    

main()

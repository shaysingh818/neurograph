cdef extern from "../src/data_structures/includes/node.h":
    
    struct Node:
        int id
        int weight
        int counter
        Node* next
        Node* left
        Node* right


    Node* create_node(int id, char *label, int weight)
    void print_node(Node* node)


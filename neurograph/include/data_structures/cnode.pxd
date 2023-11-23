cdef extern from "../src/data_structures/node/includes/node.h":
    
    struct Node:
        int id
        int weight
        int counter
        char *label
        Node* next
        Node* left
        Node* right


    Node* create_node(int id, char *label, int weight)
    void print_node(Node* node)


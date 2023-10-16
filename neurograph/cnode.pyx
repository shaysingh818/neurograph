cdef extern from "../src/data_structures/includes/node.h":

    ctypedef struct Node:
        int id
        int weight
        int counter
        char *label
        Node* next
        Node* left
        Node* right

    ctypedef struct NodeList:
        Node* head
 
    ctypedef struct Edge:
        Node* src
        Node* dest
        int weight

    Node* create_node(int id, char *label, int weight)
    void print_node(Node* node)

    Edge* create_edge(Node* n1, Node* n2, int weight)
    void print_edge(Edge* e)

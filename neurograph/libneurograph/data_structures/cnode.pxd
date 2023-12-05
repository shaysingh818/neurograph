cdef extern from "<data_structures/node/includes/node.h>":

    struct Node:
        int id
        int weight
        int counter
        char *label
        Node* next
        Node* left
        Node* right

    struct NodeList:
        Node *head

    struct Edge:
        Node* src
        Node *dst
        int weight


    Node* create_node(int id, char *label, int weight)
    Node *copy_node(Node* node)
    void print_node(Node* node)

    Edge *create_edge(Node* n1, Node* n2, int weight)
    void print_edge(Edge* e)


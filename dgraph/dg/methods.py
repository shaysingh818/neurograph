from pprint import pprint
from .ffi_register import lib


def init_graph(vertice_count, directed):

    # validate some stuff here
    if vertice_count < 0:
        print("Vertice can't be negative")
        return False
    
    # init graph
    graph = lib.init_graph_util(vertice_count, directed)
    return graph


def add_node(graph, src_id, src, dst_id, dst, weight):

    # call add node from lib
    result = lib.add_node_util(
        graph, src_id, src, 
        dst_id, dst, weight
    )

    return result


def graph_serialize(graph):
    
    body = {
        "vertice_count": graph.contents.v,
        "edge_count": graph.contents.e,
        "visited_nodes": graph.contents.visited,
        "directed": graph.contents.directed,
        "err": graph.contents.err,
        "edges": [],
        "items": {}
    }

    # serialize items
    node_list = graph.contents.items
    for i in range(graph.contents.v):
        head_node = node_list[i].head
        body["items"][i] = []
        neighbors = [] 
        while head_node:
            label = head_node.contents.label
            body["items"][i].append(label)
            neighbors.append(label)
            head_node = head_node.contents.next

    return body

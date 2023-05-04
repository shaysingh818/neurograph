from pprint import pprint
from .ffi_register import lib
import ctypes


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
        "visited_nodes": [],
        "directed": graph.contents.directed,
        "err": graph.contents.err,
        "edges": [],
        "items": {}
    }

    # serialize items
    node_list = graph.contents.items
    for i in range(graph.contents.v):
        head_node = node_list[i].head
        #print(f"Vertex {i} head node: {head_node}")
        body["items"][i] = []
        while head_node:
            label = head_node.contents.label
            #print(f"Vertex {i} label: {label}")
            label_decode = label.decode('utf-8')
            body["items"][i].append(label_decode)
            if head_node is not None:
                head_node = head_node.contents.next

    return body


def graph_to_csv(filename, features, size, row_limit):

    # convert types
    count = len(features)
    c_features = (ctypes.c_int * count)(*features)
    c_size = ctypes.c_int(size)
    c_row_limit = ctypes.c_int(row_limit)
    c_filename = ctypes.create_string_buffer(len(filename)+1)
    c_filename.value = filename.encode('utf-8')

    # call add node from lib
    result = lib.g_to_csv_util(c_filename, c_features, c_size, c_row_limit)
    return 

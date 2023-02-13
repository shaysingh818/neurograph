from pprint import pprint
from ffi_register import lib


def add_node(graph, src_id, src, dst_id, dst, weight):

    # call add node from lib
    result = add_node_util(
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


def main():

    # load graph test
    result = lib.init_graph_util(10)
    lib.add_node_util(result, 4, "D", 0, "A", 0)
    json_result = graph_serialize(result)
    pprint(json_result)



if __name__ == "__main__":
    main()

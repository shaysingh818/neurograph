cimport libneurograph.graph.cgraph as gr
cimport libneurograph.graph.cpath as cp
cimport libneurograph.graph.ccommunity as cc
cimport libneurograph.data_structures.clist as ll
cimport libneurograph.data_structures.cmatrix as mat
from neurograph.extractors cimport DataFrame

cdef class Graph:

    def __cinit__(self):
        self.graph = NULL

    def __init__(self, vertices: int, directed: bool):
        self.graph = gr.init_graph(vertices, vertices, directed)
        if self.graph is NULL:
            raise MemoryError()

    def add_node(self, src_id: int, src: str, dst_id: int, dst: str, weight: int):

        # add to adjacency list
        ll.add_node(
            self.graph.list, 
            src_id, src.encode('utf-8'),
            dst_id, dst.encode('utf-8'),
            weight
        )

        # add to matrice
        mat.add_node_mat(
            self.graph.matrix,
            src_id, src.encode('utf-8'),
            dst_id, dst.encode('utf-8'),
            weight
        )

    def add_end_node(self, src_id: int, src: str, weight: int):
        ll.add_end_node(
            self.graph.list, 
            src_id, 
            src.encode('utf-8'), 
            weight
        )

    def label_node(self, index: int, label: int):
        gr.label_node(self.graph, index, label)


    def save(self, output_path: str):
        gr.deserialize_graph_list(
            self.graph, 
            output_path.encode('utf-8')
        )

    def dijkstra(self, start_vertex: int, matrix=False) -> list:
        result_list = []
        if matrix:
            results = cp.dijkstra_mat(self.graph, start_vertex)
        else:
            results = cp.dijkstra_list(self.graph, start_vertex)

        for i in range(self.graph.vertices):
            result_list.append(results[i])
        return result_list

    def shortest_path(self, start_vertex: int, end_vertex: int, matrix=False):
        if matrix:
            return cp.shortest_path_mat(
                self.graph,
                start_vertex,
                end_vertex
            )
        else:
            return cp.shortest_path_list(
                self.graph,
                start_vertex,
                end_vertex
            )

    def closeness_centrality(self, start_vertex: int, normalized=False):
        if normalized:
            return cc.normalized_closeness_centrality_list(
                self.graph,
                start_vertex,
            )
        else:
            return cc.closeness_centrality_list(
                self.graph,
                start_vertex,
            )

    def kosaraju(self, start_vertex: int, iterative=False):
        predicted_labels = []
        results = cc.kosaraju_list(self.graph, start_vertex)
        for i in range(self.graph.list.v):
            for j in range(self.graph.list.v):
                print(results[i][j])
                
    def adj_list(self):
        results = {}
        for i in range(self.graph.list.v):
            results[i] = []
            head = self.graph.list.items[i].head
            while head:
                item = (head.id, head.label.decode('utf-8'))
                results[i].append(item)
                head = head.next
        return results

    def print_graph(self):
        ll.print_graph(self.graph.list)

    def matrix(self):
        mat.print_adj_mat(self.graph.matrix)

    def vertices(self):
        return self.graph.vertices

    def edges(self):
        return self.graph.edges

    def labels(self):
        results = []
        for i in range(self.graph.list.v):
            results.append(self.graph.labels[i])
        return results

    

cdef class SerializedGraph(Graph):

    def __cinit__(self):
        self.graph = NULL

    def __init__(self, filename: str, file_size=1024, directed=False):
        filename_encode = filename.encode('utf-8')
        self.filename = filename
        self.file_size = file_size
        self.graph = gr.serialize_graph_list(filename_encode, file_size, directed)
        if self.graph is NULL:
            raise MemoryError()


cdef class DataFrameGraph(Graph):

    def __cinit__(self):
        self.graph = NULL
        
    def __init__(self, dataframe: DataFrame, cols: list, directed: bool, weighted: bool):

        # select cols to create graph
        self.frame = dataframe
        self.columns = ll.init_array()
        for item in cols:
            ll.insert_char(self.columns, bytes(item, encoding="utf8"))

        if weighted:
            self.graph = gr.frame_to_weighted_graph(
                self.frame.frame,
                self.columns,
                directed
            )
        else:
            self.graph = gr.frame_to_unweighted_graph(
                self.frame.frame,
                self.columns,
                directed
            )

        if self.graph is NULL:
            raise MemoryError()


cdef class Walk:

    def __cinit__(self):
        self.walk = NULL

    def __init__(self, steps: int):
        self.walk = gr.init_walk(steps)
        if self.walk is NULL:
            raise MemoryError()
    
    def contents(self):
        steps = []
        for i in range(self.walk.steps):
            steps.append(self.walk.path[i])
        
        return {
            "path": steps,
            "steps": self.walk.steps,
            "weighted_sum": self.walk.weighted_sum,
            "cycles": self.walk.cycles
        }


cdef class GraphWalk(Walk):

    def __cinit__(self):
        self.walk = NULL

    def __init__(self, graph: Graph, start_vertex: int, steps: int, weighted: bool, matrix=False):

        if weighted:
            self.walk = cp.weighted_random_walk_list(
                graph.graph, 
                start_vertex, 
                steps
            )
        else:
            if matrix:
                self.walk = cp.random_walk_mat(
                    graph.graph, 
                    start_vertex, 
                    steps
                )
            else:
                self.walk = cp.random_walk_list(
                    graph.graph, 
                    start_vertex, 
                    steps
                )

        if self.walk is NULL:
            raise MemoryError()
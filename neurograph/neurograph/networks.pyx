cimport libneurograph.data_structures.cmatrix as matrix
cimport libneurograph.computation_graph.cvalue as val
cimport libneurograph.networks.clayer as la
cimport libneurograph.networks.cnetwork as net
from neurograph.structures cimport Matrix
from pprint import pprint


cdef class Value:

    def __cinit__(self):
        self.value = NULL

    def __init__(self, matrix: Matrix):
        self.value = val.value(matrix.mat)
        if self.value is NULL:
            raise MemoryError()


cdef class Network:

    def __cinit__(self):
        self.network = NULL

    def __init__(self, learning_rate: float, value: Value, batch_size: int):
        self.network = net.init_network(learning_rate, value.value, batch_size)
        if self.network is NULL:
            raise MemoryError()

    def linear(self, input_size: int, output_size: int):
        net.layer(self.network, la.linear(input_size, output_size))

    def activation(self, input_size: int, output_size: int, loss_type: str):
        loss_encode = loss_type.encode('utf-8')
        net.layer(self.network, la.activation(input_size, output_size, loss_encode))

    def train(self, epochs: int, output: Matrix, log=True):
        net.train(self.network, epochs, output.mat, log)

    def batch_train(self, epochs: int, output: Matrix, log=True):
        net.batch_train(self.network, epochs, output.mat, log)

    def predict(self, input: Matrix):
        cdef matrix.Matrix *val = net.predict(self.network, input.mat)
        result = Matrix(val.rows, val.cols)
        result.mat = val
        return result

    def num_layers(self):
        val = self.network.num_layers
        return val

    def save(self, filepath: str):
        value = filepath.encode('utf-8')
        net.save_model_params(self.network, value)

    def load(self, filepath: str):
        net.load_model_params(self.network, filepath.encode('utf-8'))

    def architecture(self):
        results = {}
        for i in range(self.network.num_layers):
            key = f"layer_{i}"
            results[key] = {
                "type": self.network.layers[i].layer_name.decode('utf-8'),
                "input_size": self.network.layers[i].input_size,
                "output_size": self.network.layers[i].output_size,
            }
        return results
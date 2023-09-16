#Outputs and compilation target
BIN=bin
CC=gcc
TARGET=target/neurograph
TEST_TARGET=target/test_neurograph

# source code objects
DS_GRAPH = ../data_structures/matrix.o ../data_structures/adj_list.o ../data_structures/adj_mat.o
DS_QUEUE = ../data_structures/map.o ../data_structures/node.o ../data_structures/queue.o ../data_structures/set.o ../data_structures/ll.o
DS_OBJS = $(DS_GRAPH)  $(DS_QUEUE)

CGRAPH_OBJS = ../computation_graph/computation_graph.o ../computation_graph/value.o ../computation_graph/mat_ops.o ../computation_graph/tanh.o ../computation_graph/mse.o
NETWORK_OBJS = ../networks/layer.o ../networks/network.o
GRAPH_OBJS = ../graph/graph.o ../graph/community.o ../graph/path.o ../graph/search.o
EXTRACTOR_OBJS = ../extractors/re.o ../extractors/frame.o ../extractors/gml.o

OBJS = $(DS_OBJS) $(GRAPH_OBJS) $(EXTRACTOR_OBJS) $(CGRAPH_OBJS) $(NETWORK_OBJS)


# source header files
HEADERS = $(wildcard ./includes/*.h)

SRC_OBJS = test_graph_extraction.o test_nn_train.o

FLAGS = -lm -lpthread -g

all: source

source: main.o $(SRC_OBJS) $(OBJS)
	$(CC) -o $(TEST_TARGET) main.o $(SRC_OBJS) $(OBJS)  $(FLAGS)


clean_binary:
	rm $(TEST_TARGET)

clean:
	rm -f *.o *~

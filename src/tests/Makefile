#Outputs and compilation target
BIN=bin
CC=gcc
TARGET=target/neurograph
TEST_TARGET=target/test_neurograph

# source code objects
QUEUE_OBJS = ../data_structures/queue/queue.o ../data_structures/node/node.o 
MATRIX_OBJS = ../data_structures/matrix/matrix.o ../data_structures/matrix/adj_mat.o
LIST_OBJS = ../data_structures/list/adj_list.o ../data_structures/list/ll.o ../data_structures/list/array.o
MAP_OBJS = ../data_structures/map/map.o ../data_structures/map/table.o ../data_structures/map/hash.o
SET_OBJS = ../data_structures/set/set.o
DS_OBJS = $(QUEUE_OBJS)  $(MATRIX_OBJS) $(LIST_OBJS) $(MAP_OBJS) $(SET_OBJS)

CGRAPH_OBJS = ../computation_graph/computation_graph.o ../computation_graph/value.o ../computation_graph/ops.o ../computation_graph/loss.o
NETWORK_OBJS = ../networks/layer.o ../networks/network.o ../networks/linear.o ../networks/activation.o
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

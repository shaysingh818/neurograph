# object files

DS_GRAPH = data_structures/matrix.o data_structures/adj_list.o data_structures/adj_mat.o
DS_QUEUE = data_structures/map.o data_structures/node.o data_structures/queue.o data_structures/set.o data_structures/ll.o data_structures/array.o
DS_OBJS = $(DS_GRAPH)  $(DS_QUEUE)

CGRAPH_OBJS = computation_graph/computation_graph.o computation_graph/value.o computation_graph/ops.o computation_graph/loss.o
NETWORK_OBJS = networks/layer.o networks/network.o networks/linear.o networks/activation.o
GRAPH_OBJS = graph/graph.o graph/community.o graph/path.o graph/search.o
EXTRACTOR_OBJS = extractors/re.o extractors/frame.o extractors/gml.o

OBJS = $(DS_OBJS) $(GRAPH_OBJS) $(EXTRACTOR_OBJS) $(CGRAPH_OBJS) $(NETWORK_OBJS)

# Outputs and compilation target
BIN=bin
CC=gcc
TARGET=../target/neurograph
SO_TARGET = neurograph.so
INSTALL_DIR = /usr/local/lib

FLAGS = -lm -lpthread
SO_FLAGS =  -fPIC 


all: build source shared 

shared: main.o $(OBJS)
	$(CC) -o $(SO_TARGET) main.o $(SO_FLAGS) $(OBJS) $(FLAGS)

source: main.o $(OBJS)
	$(CC) -o $(TARGET) main.o $(OBJS)  $(FLAGS)

build: graph data_structures extractors computation_graph networks

data_structures:
	$(MAKE) -C ./data_structures

graph: 
	$(MAKE) -C ./graph

networks:
	$(MAKE) -C ./networks

extractors:
	$(MAKE) -C ./extractors

computation_graph:
	$(MAKE) -C ./computation_graph

main.o: main.c graph/includes/graph.h data_structures/includes/node.h
	$(CC) -c main.c

install:
	cp $(SO_TARGET) $(INSTALL_DIR)
	ldconfig
	rm $(SO_TARGET)

clean_binary:
	rm $(TARGET)

clean:
	rm -f *.o *~
	$(MAKE) -C  ./data_structures clean
	$(MAKE) -C ./networks clean
	$(MAKE) -C ./graph clean
	$(MAKE) -C ./extractors clean
	$(MAKE) -C  ./computation_graph clean

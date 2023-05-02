# object files

DATA_STRUCTURE_OBJS = data_structures/matrix.o data_structures/adj_list.o data_structures/map.o data_structures/node.o data_structures/queue.o
NETWORK_OBJS = networks/layer.o networks/activations.o networks/network.o
GRAPH_OBJS = graph/graph.o graph/community.o graph/path.o graph/search.o
EXTRACTOR_OBJS = extractors/csv.o


OBJS = $(DATA_STRUCTURE_OBJS) $(NETWORK_OBJS) $(GRAPH_OBJS) $(EXTRACTOR_OBJS)

# Outputs and compilation target
BIN=bin
CC=gcc
TARGET=../target/neurograph
SHARED_TARGET = ../dgraph/dg/lib/neurograph.so


FLAGS = -lm -lpthread
SO_FLAGS = -shared -fPIC


all: build source shared

shared: main.o $(OBJS)
	$(CC) -o $(SHARED_TARGET) main.o $(OBJS) $(FLAGS) $(SO_FLAGS)

source: main.o $(OBJS)
	$(CC) -o $(TARGET) main.o $(OBJS)  $(FLAGS)

build: graph data_structures extractors networks

data_structures:
	$(MAKE) -C ./data_structures

graph: 
	$(MAKE) -C ./graph

networks:
	$(MAKE) -C ./networks

extractors:
	$(MAKE) -C ./extractors


# utilities for python
utils.o: utils/utils.c utils/includes/utils.h
	$(CC) -c utils/utils.c


main.o: main.c graph/includes/graph.h data_structures/includes/node.h
	$(CC) -c main.c

clean_binary:
	rm $(TARGET)

clean:
	rm -f *.o *~
	rm ../dgraph/dg/lib/*.so
	$(MAKE) -C  ./data_structures clean
	$(MAKE) -C ./networks clean
	$(MAKE) -C ./graph clean
	$(MAKE) -C ./extractors clean

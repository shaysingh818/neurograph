# object files

DS_GRAPH = data_structures/matrix.o data_structures/adj_list.o
DS_QUEUE = data_structures/map.o data_structures/node.o data_structures/queue.o
DS_OBJS = $(DS_GRAPH)  $(DS_QUEUE)

NETWORK_OBJS = networks/layer.o networks/activations.o networks/network.o
GRAPH_OBJS = graph/graph.o graph/community.o graph/path.o graph/search.o
EXTRACTOR_OBJS = extractors/csv.o
UTIL_OBJS = utils/utils.o


OBJS = $(DS_OBJS) $(NETWORK_OBJS) $(GRAPH_OBJS) $(EXTRACTOR_OBJS) $(UTIL_OBJS)

# Outputs and compilation target
BIN=bin
CC=gcc
TARGET=../target/neurograph
SHARED_TARGET = ../neurograph/ngraph/lib/neurograph.so


FLAGS = -lm -lpthread
SO_FLAGS = -shared -fPIC


all: build source shared

shared: main.o $(OBJS)
	$(CC) -o $(SHARED_TARGET) main.o $(OBJS) $(FLAGS) $(SO_FLAGS)

source: main.o $(OBJS)
	$(CC) -o $(TARGET) main.o $(OBJS)  $(FLAGS)

build: graph data_structures extractors networks utils

data_structures:
	$(MAKE) -C ./data_structures

graph: 
	$(MAKE) -C ./graph

networks:
	$(MAKE) -C ./networks

extractors:
	$(MAKE) -C ./extractors

utils: 
	$(MAKE) -C ./utils

main.o: main.c graph/includes/graph.h data_structures/includes/node.h
	$(CC) -c main.c

clean_binary:
	rm $(TARGET)

clean:
	rm -f *.o *~
	rm ../neurograph/ngraph/lib/*.so
	$(MAKE) -C  ./data_structures clean
	$(MAKE) -C ./networks clean
	$(MAKE) -C ./graph clean
	$(MAKE) -C ./extractors clean
	$(MAKE) -C ./utils clean

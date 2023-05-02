BIN=bin
CC=gcc
TARGET=target/utils
TEST_TARGET=target/test_utils

# Data Structures objects
DS_GRAPH = ../data_structures/adj_list.o ../data_structures/matrix.o
DS_QUEUE = ../data_structures/queue.o  ../data_structures/node.o 
DS_MAP = ../data_structures/map.o 
DS_OBJS = $(DS_GRAPH)  $(DS_QUEUE) $(DS_MAP)

# Network Objects
NETWORK_OBJS = ../networks/layer.o ../networks/network.o ../networks/activations.o

# Graph objects
GRAPH_OBJS = ../graph/graph.o ../graph/path.o ../graph/search.o ../graph/community.o

# Extractor objs
EXTRACTOR_OBJS = ../extractors/csv.o

UTILS = serializers.o utils.o

# object files
TEST_OBJS = test_serializers.o
OBJS = $(DS_OBJS) $(NETWORK_OBJS) $(GRAPH_OBJS) $(EXTRACTOR_OBJS) $(UTILS)
ALL_OBJS = $(TEST_OBJS) $(OBJS)

FLAGS = -lm -lpthread

all: unit_test source


networks:
	$(MAKE) -C ../networks

graph:
	$(MAKE) -C ../graph

data_structures:
	$(MAKE) -C ../data_structures

extractors:
	$(MAKE) -C ../extractors


unit_test: unit_test.o $(ALL_OBJS)
	$(CC) -o $(TEST_TARGET) unit_test.o $(ALL_OBJS) $(FLAGS)

source: main.o $(OBJS)
	$(CC) -o $(TARGET) main.o $(OBJS) $(FLAGS)

utils.o: utils.c includes/utils.h
	$(CC) -c utils.c

serializers.o: serializers.c includes/serializers.h
	$(CC) -c serializers.c

test_serializers.o: tests/test_serializers.c tests/includes/test_serializers.h
	$(CC) -c tests/test_serializers.c

# main files
unit_test.o: tests/unit_test.c tests/includes/test_serializers.h
	gcc -c tests/unit_test.c

main.o: main.c $(HEADERS)
	gcc -c main.c


# clean compilation (target doesn't work)
clean_binary:
	rm $(TARGET)

clean:
	rm -f *.o *~ *.pyc
	$(MAKE) -C  ../graph clean
	$(MAKE) -C ../networks clean
	$(MAKE) -C ../data_structures clean
	$(MAKE) -C ../extractors clean

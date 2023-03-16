# object files
GRAPH_OBJS = graph/graph.o list/adj_list.o list/node.o graph/path.o graph/search.o graph/community.o
QUEUE_OBJS = queue/queue.o
MAP_OBJS = map/map.o
MATRICE_OBJS = matrice/matrix.o
CSV_OBJS = csv/csv.o
UTIL_OBJS = utils.o
OBJS = $(GRAPH_OBJS) $(CSV_OBJS) $(MATRICE_OBJS) $(MAP_OBJS) $(QUEUE_OBJS) $(UTIL_OBJS)


# Outputs and compilation target
BIN=bin
CC=gcc
TARGET=../target/diffusion
SHARED_TARGET = ../dgraph/dg/lib/diffusion.so


FLAGS = -lm -lpthread
SO_FLAGS = -shared -fPIC


all: build source shared

shared: main.o $(OBJS)
	$(CC) -o $(SHARED_TARGET) main.o $(OBJS) $(FLAGS) $(SO_FLAGS)

source: main.o $(OBJS)
	$(CC) -o $(TARGET) main.o $(OBJS)  $(FLAGS)

build: queue matrice list map graph csv


csv:
	$(MAKE) -C ../csv

graph:
	$(MAKE) -C ../graph

matrice:
	$(MAKE) -C ../matrice

list:
	$(MAKE) -C ../list

queue:
	$(MAKE) -C ../queue

map:
	$(MAKE) -C ../map


# utilities for python
utils.o: utils/utils.c utils/includes/utils.h
	$(CC) -c utils/utils.c


main.o: main.c graph/includes/graph.h
	$(CC) -c main.c

clean_binary:
	rm $(TARGET)

clean:
	rm -f *.o *~
	rm ../dgraph/dg/lib/*.so
	$(MAKE) -C  ./graph clean
	$(MAKE) -C ./csv clean
	$(MAKE) -C ./queue clean
	$(MAKE) -C ./matrice clean
	$(MAKE) -C ./map clean
	$(MAKE) -C ./list clean

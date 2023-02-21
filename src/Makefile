# Object files


GRAPH_OBJS = graph/graph.o graph/node.o graph/path.o graph/search.o graph/community.o
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

FLAGS = -lm -lpthread


all: build source

source: main.o $(OBJS)
	gcc -o $(TARGET) main.o $(OBJS)  $(FLAGS)

build: queue matrice map graph csv


csv:
	$(MAKE) -C ../csv

graph:
	$(MAKE) -C ../graph

matrice:
	$(MAKE) -C ../matrice

queue:
	$(MAKE) -C ../queue

map:
	$(MAKE) -C ../map


# utilities for python
utils.o: utils/utils.c utils/includes/utils.h
	$(CC) -c utils/utils.c


main.o: main.c graph/includes/graph.h
	gcc -c main.c

clean_binary:
	rm $(TARGET)

clean:
	rm -f *.o *~
	$(MAKE) -C  ./graph clean
	$(MAKE) -C ./csv clean
	$(MAKE) -C ./queue clean
	$(MAKE) -C ./matrice clean
	$(MAKE) -C ./map clean

# Outputs and compilation target
BIN=bin
CC=gcc
TARGET= diffusion.so

SOURCE_FLAGS = -lm -lpthread
SO_FLAGS = -shared -fPIC

GRAPH_OBJS = ../../src/graph/graph.o ../../src/graph/node.o 
GRAPH_EXT = ../../src/graph/path.o ../../src/graph/search.o ../../src/graph/community.o
QUEUE_OBJS = ../../src/queue/queue.o
MAP_OBJS = ../../src/map/map.o
MATRICE_OBJS = ../../src/matrice/matrix.o
CSV_OBJS = ../../src/csv/csv.o
UTIL_OBJS = ../../src/utils/utils.o
OBJS = $(GRAPH_OBJS) $(GRAPH_EXT) $(CSV_OBJS) $(MATRICE_OBJS) $(MAP_OBJS) $(QUEUE_OBJS) $(UTIL_OBJS)


all: $(OBJS) $(OBJ_EXTENSIONS)
	gcc -o $(TARGET) $(OBJS) $(OBJ_EXTENSIONS) $(SOURCE_FLAGS) $(SO_FLAGS)


build: queue matrice map graph csv

csv:
	$(MAKE) -C ../../src/csv

graph:
	$(MAKE) -C ../../src/graph

matrice:
	$(MAKE) -C ../../src/matrice

queue:
	$(MAKE) -C ../../src/queue

map:
	$(MAKE) -C ../../src/map


utils.o: ../../src/utils/utils.c ../../src/utils/includes/utils.h
	gcc -c ../../src/utils/utils.c


clean_binary:
	rm $(TARGET)

clean:
	rm -f *.so *~ *.pyc
	$(MAKE) -C  ../../src/graph clean
	$(MAKE) -C ../../src/csv clean
	$(MAKE) -C ../../src/queue clean
	$(MAKE) -C ../../src/matrice clean
	$(MAKE) -C ../../src/map clean

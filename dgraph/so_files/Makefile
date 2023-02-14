# Outputs and compilation target
BIN=bin
CC=gcc
TARGET= diffusion.so

SOURCE_FLAGS = -lm -lpthread
SO_FLAGS = -shared -fPIC

OBJS = graph.o matrix.o queue.o node.o map.o utils.o
OBJ_EXTENSIONS = path.o search.o community.o csv.o

all: $(OBJS) $(OBJ_EXTENSIONS)
	gcc -o $(TARGET) $(OBJS) $(OBJ_EXTENSIONS) $(SOURCE_FLAGS) $(SO_FLAGS)

utils.o: ../../src/utils.c ../../src/includes/utils.h
	gcc -c ../../src/utils.c

csv.o: ../../src/csv.c ../../src/includes/csv.h
	gcc -c ../../src/csv.c

graph.o: ../../src/graph.c ../../src/includes/graph.h
	gcc -c ../../src/graph.c

matrix.o: ../../src/matrix.c ../../src/includes/matrix.h
	gcc -c ../../src/matrix.c

map.o: ../../src/map.c ../../src/includes/map.h
	gcc -c ../../src/map.c

queue.o: ../../src/queue.c ../../src/includes/queue.h
	gcc -c ../../src/queue.c

node.o: ../../src/node.c ../../src/includes/node.h
	gcc -c ../../src/node.c

path.o: ../../src/path.c ../../src/includes/path.h
	gcc -c ../../src/path.c

search.o: ../../src/search.c ../../src/includes/search.h
	gcc -c ../../src/search.c

community.o: ../../src/community.c ../../src/includes/community.h
	gcc -c ../../src/community.c

clean_binary:
	rm $(TARGET)

clean:
	rm -f *.o *~ *.pyc

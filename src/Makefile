# Object files
GRAPH_OBJS = graph.o matrix.o queue.o node.o map.o
GRAPH_EXTENSIONS = path.o search.o community.o csv.o

# Header files
UTILITY_HEADERS = includes/graph.h includes/matrix.h includes/queue.h includes/csv.h
EXTENSION_HEADERS = includes/path.h includes/search.h includes/community.h includes/map.h

# Outputs and compilation target
BIN=bin
CC=gcc
TARGET=../target/diffusion

FLAGS = -lm -lpthread

all: main.o $(GRAPH_OBJS) $(GRAPH_EXTENSIONS)
	gcc -o $(TARGET) main.o $(GRAPH_OBJS) $(GRAPH_EXTENSIONS) $(FLAGS)

csv.o: csv.c includes/csv.h
	gcc -c csv.c

graph.o: graph.c includes/graph.h
	gcc -c graph.c

matrix.o: matrix.c includes/matrix.h
	gcc -c matrix.c

map.o: map.c includes/map.h
	gcc -c map.c

queue.o: queue.c includes/queue.h
	gcc -c queue.c

node.o: node.c includes/node.h
	gcc -c node.c

path.o: path.c includes/path.h
	gcc -c path.c

search.o: search.c includes/search.h
	gcc -c search.c

community.o: community.c includes/community.h
	gcc -c community.c

main.o: main.c $(UTILITY_HEADERS) $(EXTENSION_HEADERS)
	gcc -c main.c

clean_binary:
	rm $(TARGET)

clean:
	rm -f *.o *~

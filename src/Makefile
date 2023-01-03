OBJECT_FILES= graph.o matrix.o queue.o node.o
MAIN_HEADER_FILES = includes/graph.h includes/matrix.h includes/queue.h 

BIN=bin
CC=gcc
TARGET=../target/graph


FLAGS = -lm -lpthread

all: main.o $(OBJECT_FILES)
	gcc -o $(TARGET) main.o $(OBJECT_FILES) $(FLAGS)

graph.o: graph.c includes/graph.h
	gcc -c graph.c

matrix.o: matrix.c includes/matrix.h
	gcc -c matrix.c

queue.o: queue.c includes/queue.h
	gcc -c queue.c

node.o: node.c includes/node.h
	gcc -c node.c

main.o: main.c $(MAIN_HEADER_FILES)
	gcc -c main.c

clean_binary:
	rm $(TARGET)

clean:
	rm -f *.o *~

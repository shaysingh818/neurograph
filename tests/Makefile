BIN=bin
CC=gcc
TARGET=../target/unit_test

# Header files
MATRIX_HEADER = includes/matrix_test.h
GRAPH_HEADER = includes/graph_test.h
QUEUE_HEADER = includes/queue_test.h
MAIN_HEADER_FILES = $(MATRIX_HEADER) $(GRAPH_HEADER) $(QUEUE_HEADER)


# Object files
GRAPH_OBJS = graph_test.o graph.o node.o
MATRIX_OBJS = matrix_test.o matrix.o
QUEUE_OBJS = queue_test.o queue.o
OBJECT_FILES = $(GRAPH_OBJS) $(MATRIX_OBJS) $(QUEUE_OBJS)

# Flags
FLAGS = -lm -lpthread

all: main.o $(OBJECT_FILES)
	gcc -o $(TARGET) main.o $(OBJECT_FILES) $(FLAGS)

node.o: ../src/node.c ../src/includes/node.h
	gcc -c ../src/node.c

graph.o: ../src/graph.c ../src/includes/graph.h
	gcc -c ../src/graph.c

graph_test.o: graph_test.c includes/graph_test.h
	gcc -c graph_test.c

queue.o: ../src/queue.c ../src/includes/queue.h
	gcc -c ../src/queue.c

matrix.o: ../src/matrix.c ../src/includes/matrix.h
	gcc -c ../src/matrix.c

matrix_test.o: matrix_test.c includes/matrix_test.h
	gcc -c matrix_test.c

main.o: main.c $(MAIN_HEADER_FILES)
	gcc -c main.c

clean_binary:
	rm $(TARGET)

clean:
	rm -f *.o *~

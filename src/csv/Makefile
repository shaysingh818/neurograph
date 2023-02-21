BIN=bin
CC=gcc
TARGET=target/csv
TEST_TARGET=target/test_csv
INCLUDES = -I./includes -I../graph/includes -I../map/includes -I./tests/includes

FLAGS = -g -lm -lpthread $(INCLUDES)

# Graph dependencies
GRAPH_OBJS = ../graph/graph.o ../graph/node.o 
GRAPH_EXTENSIONS = ../graph/path.o ../graph/search.o ../graph/community.o 
GRAPH_STRUCTURES = ../graph/queue.o ../graph/matrix.o
GRAPH_LIBS = $(GRAPH_OBJS) $(GRAPH_EXTENSIONS) $(GRAPH_STRUCTURES)

# CSV source objects
CSV_OBJS = csv.o map.o test_csv.o

# Objects
OBJS = $(CSV_OBJS) $(GRAPH_OBJS) $(GRAPH_EXTENSIONS) $(GRAPH_STRUCTURES) $(TEST_OBJS)


# link all programs here
all: graph source unit_test

unit_test: unit_test.o $(OBJS)
	gcc -o $(TEST_TARGET) unit_test.o $(OBJS) $(FLAGS)

source: main.o $(OBJS)
	gcc -o $(TARGET) main.o $(OBJS) $(FLAGS)

graph:
	$(MAKE) -C ../graph


# link files here
csv.o: csv.c includes/csv.h
	gcc -c csv.c

map.o: ../map/map.c ../map/includes/map.h
	gcc -c ../map/map.c


# test files
test_csv.o: tests/test_csv.c includes/csv.h
	gcc -c tests/test_csv.c


# main files
unit_test.o: tests/unit_test.c tests/includes/test_csv.h
	gcc -c tests/unit_test.c

main.o: main.c includes/csv.h
	gcc -c main.c


# clean compilation (target doesn't work)
clean_binary:
	rm $(TARGET)

clean:
	rm -f *.o *~ *.pyc
	$(MAKE) -C ../graph clean

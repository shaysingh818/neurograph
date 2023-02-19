# Outputs and compilation target
BIN=bin
CC=gcc
TARGET=target/graph
TEST_TARGET=target/test_graph

# header files
GRAPH_HEADER = tests/includes/test_graph.h
PATH_HEADER = tests/includes/test_path.h
SEARCH_HEADER = tests/includes/test_search.h
COMMUNITY_HEADER = tests/includes/test_community.h
HEADERS = $(GRAPH_HEADER) $(PATH_HEADER) $(SEARCH_HEADER) $(COMMUNITY_HEADER)

# source objects
GRAPH_OBJS = graph.o node.o path.o search.o community.o queue.o matrix.o

# unit test objects
TEST_PATH_OBJS = test_path.o
TEST_SEARCH_OBJS = test_search.o 
TEST_COMMUNITY_OBJS = test_community.o 
TEST_GRAPH_OBJS = test_graph.o
TEST_OBJS = $(TEST_PATH_OBJS) $(TEST_SEARCH_OBJS) $(TEST_COMMUNITY_OBJS) $(TEST_GRAPH_OBJS)

# flags
FLAGS = -g -lm -lpthread


# link all programs here
all: unit_test source

unit_test: unit_test.o $(GRAPH_OBJS) $(TEST_OBJS)
	gcc -o $(TEST_TARGET) unit_test.o $(GRAPH_OBJS) $(TEST_OBJS)

source: main.o $(GRAPH_OBJS)
	gcc -o $(TARGET) main.o $(GRAPH_OBJS) $(FLAGS)


# object files for graph lib
graph.o: graph.c includes/graph.h
	gcc -c graph.c

node.o: node.c includes/node.h
	gcc -c node.c

path.o: path.c includes/path.h
	gcc -c path.c

search.o: search.c includes/search.h
	gcc -c search.c

community.o: community.c includes/community.h
	gcc -c community.c

queue.o: ../queue/queue.c ../queue/includes/queue.h
	gcc -c ../queue/queue.c

matrix.o: ../matrice/matrix.c ../matrice/includes/matrix.h
	gcc -c ../matrice/matrix.c


# object files for testing
test_community.o: tests/test_community.c tests/includes/test_community.h
	gcc -c tests/test_community.c

test_search.o: tests/test_search.c tests/includes/test_search.h
	gcc -c tests/test_search.c

test_path.o: tests/test_path.c tests/includes/test_path.h
	gcc -c tests/test_path.c

test_graph.o: tests/test_graph.c tests/includes/test_graph.h
	gcc -c tests/test_graph.c


# main files
unit_test.o: tests/unit_test.c includes/graph.h
	gcc -c tests/unit_test.c

main.o: main.c $(HEADERS)
	gcc -c main.c


# clean compilation (target doesn't work)
clean_binary:
	rm $(TARGET)

clean:
	rm -f *.o *~ *.pyc


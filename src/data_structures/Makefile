# Outputs and compilation target
BIN=bin
CC=gcc
TARGET=target/data_structures
TEST_TARGET=target/test_data_structures

# header files
MATRIX_HEADER = tests/includes/test_matrix.h
QUEUE_HEADER = tests/includes/test_queue.h
MAP_HEADER = tests/includes/test_map.h
ADJ_LIST_HEADER = tests/includes/test_adj_list.h 
HEADERS = $(MATRIX_HEADER) $(QUEUE_HEADER) $(MAP_HEADER) $(ADJ_LIST_HEADER)

# source objects
SRC_OBJS = matrix.o map.o adj_list.o queue.o node.o 

# unit test objects
TEST_MATRIX_OBJS = test_matrix.o
TEST_QUEUE_OBJS = test_queue.o 
TEST_MAP_OBJS = test_map.o 
TEST_ADJ_LIST_OBJS = test_adj_list.o
TEST_OBJS = $(TEST_MATRIX_OBJS) $(TEST_QUEUE_OBJS) $(TEST_MAP_OBJS) $(TEST_ADJ_LIST_OBJS)

# flags
FLAGS = -g -lm -lpthread


# link all programs here
all: unit_test source

unit_test: unit_test.o $(SRC_OBJS) $(TEST_OBJS)
	gcc -o $(TEST_TARGET) unit_test.o $(SRC_OBJS) $(TEST_OBJS) $(FLAGS)

source: main.o $(SRC_OBJS)
	gcc -o $(TARGET) main.o $(SRC_OBJS) $(FLAGS)


queue.o: queue.c includes/queue.h
	gcc -c queue.c

test_queue.o: tests/test_queue.c tests/includes/test_queue.h
	gcc -c tests/test_queue.c

matrix.o: matrix.c includes/matrix.h
	gcc -c matrix.c

test_matrix.o: tests/test_matrix.c tests/includes/test_matrix.h
	gcc -c tests/test_matrix.c

map.o: map.c includes/map.h
	gcc -c map.c

test_map.o: tests/test_map.c tests/includes/test_map.h
	gcc -c tests/test_map.c

node.o: node.c includes/node.h
	gcc -c node.c

adj_list.o: adj_list.c includes/adj_list.h
	gcc -c adj_list.c

test_adj_list.o: tests/test_adj_list.c tests/includes/test_adj_list.h
	gcc -c tests/test_adj_list.c


# main files
unit_test.o: tests/unit_test.c $(HEADERS)
	gcc -c tests/unit_test.c

main.o: main.c $(HEADERS)
	gcc -c main.c


# clean compilation (target doesn't work)
clean_binary:
	rm $(TARGET)

clean:
	rm -f *.o *~ *.pyc
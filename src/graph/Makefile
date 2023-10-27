# Outputs and compilation target
BIN=bin
CC=gcc
TARGET=target/graph
TEST_TARGET=target/test_graph

# source header files
HEADERS = $(wildcard /includes/*.h)

# test header files
TEST_HEADERS = $(wildcard /tests/includes/*.h)

# Data structure objects 
QUEUE_OBJS = ../data_structures/queue/queue.o ../data_structures/node/node.o 
MATRIX_OBJS = ../data_structures/matrix/matrix.o ../data_structures/matrix/adj_mat.o
LIST_OBJS = ../data_structures/list/adj_list.o ../data_structures/list/ll.o ../data_structures/list/array.o
MAP_OBJS = ../data_structures/map/map.o ../data_structures/map/table.o ../data_structures/map/hash.o
SET_OBJS = ../data_structures/set/set.o

# Data structures library dependency
DATA_STRUCTURES =  $(QUEUE_OBJS) $(MATRIX_OBJS) $(LIST_OBJS) $(MAP_OBJS) $(SET_OBJS)


EXTRACTORS = ../extractors/re.o ../extractors/gml.o ../extractors/frame.o

# source objects for extractors library
TEST_OBJS = test_path.o test_search.o test_community.o test_graph.o
SRC_OBJS = $(DATA_STRUCTURES) $(EXTRACTORS) graph.o path.o search.o community.o

# flags
FLAGS = -g -lm -lpthread

# link all programs here
all: extractors unit_test source

unit_test: unit_test.o $(SRC_OBJS) $(TEST_OBJS)
	gcc -o $(TEST_TARGET) unit_test.o $(SRC_OBJS) $(TEST_OBJS) $(FLAGS)

source: main.o $(SRC_OBJS)
	gcc -o $(TARGET) main.o  $(SRC_OBJS) $(FLAGS)

extractors:
	$(MAKE) -C ../extractors

# build source and test objects 
$(SRC_OBJS): %.o: %.c $(HEADERS)
	$(CC) -c $<

$(TEST_OBJS): %.o: tests/%.c tests/includes/%.h $(HEADERS)
	$(CC) -c $< -o $@

# main files
unit_test.o: tests/unit_test.c  $(HEADERS)
	gcc -c tests/unit_test.c

main.o: main.c $(HEADERS)
	gcc -c main.c


# clean compilation (target doesn't work)
clean_binary:
	rm $(TARGET)

clean:
	rm -f *.o *~ *.pyc
	$(MAKE) -C ../extractors clean
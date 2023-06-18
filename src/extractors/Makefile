BIN=bin
CC=gcc
TARGET=target/extractors
TEST_TARGET=target/test_extractors
FLAGS = -g -lm -lpthread $(INCLUDES)

# source header files
HEADERS = $(wildcard /includes/*.h)

# test header files
TEST_HEADERS = $(wildcard /tests/includes/*.h)

# Graph dependencies
GRAPH_OBJS = ../graph/graph.o ../graph/path.o ../graph/search.o ../graph/community.o 
DATA_STRUCTURES = ../data_structures/queue.o ../data_structures/matrix.o ../data_structures/adj_list.o ../data_structures/node.o ../data_structures/map.o ../data_structures/ll.o ../data_structures/set.o
GRAPH_LIBS = $(GRAPH_OBJS) $(DATA_STRUCTURES)

# source objects for extractors library
TEST_OBJS = test_csv.o test_frame.o test_re.o
SRC_OBJS = $(GRAPH_OBJS) $(DATA_STRUCTURES) csv.o frame.o re.o


# link all programs here
all: graph source unit_test

graph:
	$(MAKE) -C ../graph

unit_test: unit_test.o $(SRC_OBJS) $(TEST_OBJS)
	gcc -o $(TEST_TARGET) unit_test.o $(SRC_OBJS) $(TEST_OBJS) $(FLAGS)

source: main.o $(SRC_OBJS)
	gcc -o $(TARGET) main.o  $(SRC_OBJS) $(FLAGS)


# build source and test objects 
$(SRC_OBJS): %.o: %.c $(HEADERS)
	$(CC) -c $<

$(TEST_OBJS): %.o: tests/%.c tests/includes/%.h $(HEADERS)
	$(CC) -c $< -o $@


# main files
unit_test.o: tests/unit_test.c
	gcc -c tests/unit_test.c

main.o: main.c
	gcc -c main.c

# clean compilation (target doesn't work)
clean_binary:
	rm $(TARGET)

clean:
	rm -f *.o *~ *.pyc
	$(MAKE) -C ../graph clean

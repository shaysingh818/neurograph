BIN=bin
CC=gcc
TARGET=target/extractors
TEST_TARGET=target/test_extractors
INCLUDES = -I./includes -I../graph/includes -I../data_structures/includes -I./tests/includes

FLAGS = -g -lm -lpthread $(INCLUDES)

# Graph dependencies
GRAPH_OBJS = ../graph/graph.o ../graph/path.o ../graph/search.o ../graph/community.o 
DATA_STRUCTURES = ../data_structures/queue.o ../data_structures/matrix.o ../data_structures/adj_list.o ../data_structures/node.o ../data_structures/map.o 
GRAPH_LIBS = $(GRAPH_OBJS) $(DATA_STRUCTURES)

# CSV source objects

TEST_OBJS = test_csv.o
CSV_OBJS = csv.o 

# Objects
OBJS = $(CSV_OBJS) $(GRAPH_OBJS) $(DATA_STRUCTURES) $(TEST_OBJS)


# link all programs here
all: graph source unit_test

unit_test: unit_test.o $(OBJS)
	gcc -o $(TEST_TARGET) unit_test.o $(OBJS) $(FLAGS)

source: main.o $(OBJS)
	gcc -o $(TARGET) main.o $(OBJS) $(FLAGS)

graph:
	$(MAKE) -C ../graph

data_structures:
	$(MAKE) -C ../data_structures

# link files here
csv.o: csv.c includes/csv.h
	gcc -c csv.c

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
	$(MAKE) -C ../data_structures clean

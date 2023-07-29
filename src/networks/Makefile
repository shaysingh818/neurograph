#Outputs and compilation target
BIN=bin
CC=gcc
TARGET=target/networks
TEST_TARGET=target/test_networks
FLAGS = -lm -lpthread

# source header files
HEADERS = $(wildcard /includes/*.h)

# test header files
TEST_HEADERS = $(wildcard /tests/includes/*.h)

# data structure objects needed
MATRIX = ../data_structures/matrix.o

# source objects
SRC_OBJS = network.o activations.o computation_graph.o $(MATRIX)

# unit test objects
TEST_OBJS =  test_network.o test_computation_graph.o

# flags
FLAGS = -g -lm -lpthread


# link all programs here
all: data_structures unit_test source

data_structures:
	$(MAKE) -C ../data_structures

unit_test: unit_test.o $(SRC_OBJS) $(TEST_OBJS)
	gcc -o $(TEST_TARGET) unit_test.o $(SRC_OBJS) $(TEST_OBJS) $(FLAGS)

source: main.o $(SRC_OBJS)
	gcc -o $(TARGET) main.o  $(SRC_OBJS) $(FLAGS)


# build source and test objects 
$(SRC_OBJS): %.o: %.c $(HEADERS)
	$(CC) -c $<

$(TEST_OBJS): %.o: tests/%.c tests/includes/%.h $(HEADERS)
	$(CC) -c $< -o $@

unit_test.o: tests/unit_test.c $(TEST_HEADERS)
	$(CC) -c $< -o $@

main.o: main.c $(HEADERS)
	$(CC) -c $< -o $@


# clean compilation (target doesn't work)
clean_binary:
	rm $(TARGET)

clean:
	rm -f $(TARGET) $(TEST_TARGET) *.o *~ *.pyc
BIN=bin
CC=gcc
TARGET=target/layer
TEST_TARGET=target/test_layer

# object files
TEST_OBJS = test_layer.o test_network.o
OBJS = layer.o network.o activations.o ../data_structures/matrix.o
ALL_OBJS = $(TEST_OBJS) $(OBJS)

FLAGS = -lm -lpthread

all: unit_test source

unit_test: unit_test.o $(ALL_OBJS)
	$(CC) -o $(TEST_TARGET) unit_test.o $(ALL_OBJS) $(FLAGS)

source: main.o $(OBJS)
	$(CC) -o $(TARGET) main.o $(OBJS) $(FLAGS)


data_structures.o: 
	$(MAKE) -C ../data_structures

layer.o: layer.c includes/layer.h
	$(CC) -c layer.c

network.o: network.c includes/network.h
	$(CC) -c network.c

activations.o: activations.c includes/activations.h
	$(CC) -c activations.c

test_layer.o: tests/test_layer.c tests/includes/test_layer.h
	$(CC) -c tests/test_layer.c

test_network.o: tests/test_network.c tests/includes/test_network.h
	$(CC) -c tests/test_network.c

# main files
unit_test.o: tests/unit_test.c tests/includes/test_layer.h
	gcc -c tests/unit_test.c

main.o: main.c $(HEADERS)
	gcc -c main.c

# clean compilation (target doesn't work)
clean_binary:
	rm $(TARGET)

clean:
	rm -f *.o *~ *.pyc

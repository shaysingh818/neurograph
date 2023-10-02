#Outputs and compilation target
BIN=bin
CC=gcc
TARGET=target/networks
TEST_TARGET=target/test_networks

# source header files
HEADERS = $(wildcard /includes/*.h) 

# test header files
TEST_HEADERS = $(wildcard /tests/includes/*.h)

# data structure objects needed
MATRIX = ../data_structures/matrix.o ../data_structures/map.o

# CGRAPH OBJS
CGRAPH_OBJS = ../computation_graph/computation_graph.o ../computation_graph/value.o ../computation_graph/mat_ops.o ../computation_graph/tanh.o ../computation_graph/mse.o ../computation_graph/sigmoid.o

# source objects
SRC_OBJS =  layer.o network.o linear.o activation.o  $(MATRIX) $(CGRAPH_OBJS)

# unit test objects
TEST_OBJS =  test_network.o test_layer.o  

# flags
FLAGS = -g -lm -lpthread -fPIC


# link all programs here
all: data_structures cgraph unit_test source


cgraph:
	$(MAKE) -C ../computation_graph

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
	rm -f  *.o *~ *.pyc
	$(MAKE) -C  ../data_structures clean
	$(MAKE) -C  ../computation_graph clean

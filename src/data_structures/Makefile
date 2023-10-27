#Outputs and compilation target
BIN=bin
CC=gcc
TARGET=target/data_structures
TEST_TARGET=target/test_data_structures

# source header files
HEADERS = $(wildcard /includes/*.h)

# test header files
TEST_HEADERS = $(wildcard /tests/includes/*.h)

NODE_OBJS = node/node.o
QUEUE_OBJS = queue/queue.o
SET_OBJS = set/set.o
LIST_OBJS = list/ll.o list/adj_list.o list/array.o
MAP_OBJS = map/map.o map/table.o map/hash.o
MATRIX_OBJS = matrix/matrix.o matrix/adj_mat.o

# source objects
SRC_OBJS = $(NODE_OBJS) $(QUEUE_OBJS) $(SET_OBJS) $(LIST_OBJS) $(MAP_OBJS) $(MATRIX_OBJS)

# flags
FLAGS =  -lm -lpthread -g

all: build source

# link all programs here
build: node queue set list map matrix source

source: main.o $(SRC_OBJS)
	gcc -o $(TARGET) main.o  $(SRC_OBJS) $(FLAGS)

node:
	$(MAKE) -C ./node

queue: 
	$(MAKE) -C ./queue

set:
	$(MAKE) -C ./set

list:
	$(MAKE) -C ./list

map:
	$(MAKE) -C ./map

matrix:
	$(MAKE) -C ./matrix



main.o: main.c $(HEADERS)
	$(CC) -c $< -o $@


# clean compilation (target doesn't work)
clean:
	rm -f  *.o *~ *.pyc
	$(MAKE) -C  ./map clean
	$(MAKE) -C ./matrix clean
	$(MAKE) -C ./set clean
	$(MAKE) -C ./list clean
	$(MAKE) -C  ./queue clean

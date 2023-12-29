BIN=bin
CC=gcc
TARGET=target/matrix
CFLAGS = -lm -mavx
OBJS = objs
SO_TARGET = libmatrix.so
FLAGS = -lm -lpthread -Iincludes -mavx
SO_FLAGS =  -fPIC 

# source and test 
objects := $(patsubst %.c,%.o,$(wildcard *.c))
test_objects := $(patsubst %.c,%.o,$(wildcard ./tests/*.c))

# dependencies
node_objects := $(wildcard ../node/objs/*.o)

all: node source

source: $(objects) $(test_objects) $(node_objects)
	cc -o $(TARGET) $(objects) $(test_objects) $(node_objects) $(CFLAGS)
	mkdir $(OBJS)
	mv $(filter-out main.o, $(objects)) $(OBJS)

shared: $(objects) $(test_objects) $(node_objects)
	$(CC) -o $(SO_TARGET) $(SO_FLAGS) $(objects) $(test_objects) $(node_objects) $(FLAGS)
	cp $(SO_TARGET) /usr/local/lib
	cp includes/matrix.h /usr/local/include

node:
	$(MAKE) -C ../node

clean:
	rm -f  *.o *~ *.pyc
	$(MAKE) -C  ../node clean
	rm -rf $(OBJS)

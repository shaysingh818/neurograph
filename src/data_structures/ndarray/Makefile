BIN=bin
CC=gcc
TARGET=target/ndarray
CFLAGS = -lm -mavx
OBJS = objs
SO_TARGET = libndarray.so
FLAGS = -lm -lpthread -Iincludes -mavx
SO_FLAGS =  -fPIC 

# source and test 
objects := $(patsubst %.c,%.o,$(wildcard *.c))
test_objects := $(patsubst %.c,%.o,$(wildcard ./tests/*.c))

all: source

source: $(objects) $(test_objects) $(node_objects)
	cc -o $(TARGET) $(objects) $(test_objects) $(CFLAGS)
	mkdir $(OBJS)
	mv $(filter-out main.o, $(objects)) $(OBJS)

shared: $(objects) $(test_objects)
	$(CC) -o $(SO_TARGET) $(SO_FLAGS) $(objects) $(test_objects) $(FLAGS)
	cp $(SO_TARGET) /usr/local/lib
	cp includes/ndarray.h /usr/local/include

clean:
	rm -f  *.o *~ *.pyc
	rm -rf $(OBJS)
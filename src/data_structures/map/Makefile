BIN=bin
CC=gcc
TARGET=target/map
CFLAGS = -lm
OBJS = objs

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

node:
	$(MAKE) -C ../node

clean:
	rm -f  *.o *~ *.pyc
	$(MAKE) -C  ../node clean
	rm -rf $(OBJS)

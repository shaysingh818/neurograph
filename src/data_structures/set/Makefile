BIN=bin
CC=gcc
TARGET=target/set
CFLAGS = -lm
OBJS = objs

# source and test 
objects := $(patsubst %.c,%.o,$(wildcard *.c))
test_objects := $(patsubst %.c,%.o,$(wildcard ./tests/*.c))

# dependencies
node := $(wildcard ../node/objs/*.o)
queue := $(wildcard ../queue/objs/*.o)

all: node queue source

source: $(objects) $(test_objects) $(node) $(queue)
	cc -o $(TARGET) $(objects) $(test_objects) $(node) $(queue) $(CFLAGS)
	mkdir $(OBJS)
	mv $(filter-out main.o, $(objects)) $(OBJS)

node:
	$(MAKE) -C ../node

queue:
	$(MAKE) -C ../queue

clean:
	rm -f  *.o *~ *.pyc
	$(MAKE) -C  ../node clean
	$(MAKE) -C  ../queue clean
	rm -rf $(OBJS)

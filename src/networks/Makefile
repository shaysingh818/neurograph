BIN=bin
CC=gcc
TARGET=target/networks
CFLAGS = -g -lm -lpthread $(INCLUDES)
OBJS = objs

# dependencies
EXTRACTORS := $(wildcard ../extractors/objs/*.o)
DATA_STRUCTURES := $(wildcard ../data_structures/objs/*.o)
COMPUTATION_GRAPH := $(wildcard ../computation_graph/objs/*.o)
DEPS = $(DATA_STRUCTURES) $(COMPUTATION_GRAPH) $(EXTRACTORS)

# source and test
OBJECTS := $(patsubst %.c,%.o,$(wildcard *.c))
TEST_OBJECTS := $(patsubst %.c,%.o,$(wildcard ./tests/*.c))

# link all programs here
all:	
	$(MAKE) -C ../computation_graph
	$(MAKE) -C ../extractors package
	$(MAKE) source

# assumes data structures has already been built
package:
	$(MAKE) source

source: $(OBJECTS) $(TEST_OBJECTS) $(DEPS)
	cc -o $(TARGET) $(OBJECTS) $(TEST_OBJECTS) $(DEPS) $(CFLAGS)
	mkdir $(OBJS)
	mv $(filter-out main.o, $(OBJECTS)) $(OBJS)

# clean compilation (target doesn't work)
clean_binary:
	rm $(TARGET)


clean_package:
	rm -f *.o *~ *.pyc
	rm -rf $(OBJS)

clean:
	rm -f *.o *~ *.pyc
	rm -rf $(OBJS)
	$(MAKE) -C  ../computation_graph clean
	$(MAKE) -C  ../extractors clean

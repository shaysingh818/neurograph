BIN=bin
CC=gcc
TARGET=target/graph
CFLAGS = -g -lm -lpthread $(INCLUDES)
OBJS = objs

# dependencies
DATA_STRUCTURES := $(wildcard ../data_structures/objs/*.o)
EXTRACTORS := $(wildcard ../extractors/objs/*.o)
DEPS = $(DATA_STRUCTURES) $(EXTRACTORS)

# source and test
OBJECTS := $(patsubst %.c,%.o,$(wildcard *.c))
TEST_OBJECTS := $(patsubst %.c,%.o,$(wildcard ./tests/*.c))

# link all programs here
all:	
	$(MAKE) -C ../extractors
	$(MAKE) source

# assumes data structures has already been built
package:
	$(MAKE) source

source: $(OBJECTS) $(TEST_OBJECTS) $(DEPS)
	cc -o $(TARGET) $(OBJECTS) $(TEST_OBJECTS) $(DEPS) $(CFLAGS)
	mkdir $(OBJS)
	mv $(filter-out main.o, $(OBJECTS)) $(OBJS)


headers:
	mkdir -p graph/
	cp -r includes/ graph/	
	mv graph/ ../neurograph
	cp graph.h ../neurograph

# clean compilation (target doesn't work)
clean_binary:
	rm $(TARGET)

clean_package:
	rm -f *.o *~ *.pyc
	rm -rf $(OBJS)

clean:
	rm -f *.o *~ *.pyc
	rm -rf $(OBJS)
	$(MAKE) -C  ../extractors clean

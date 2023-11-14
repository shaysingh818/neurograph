BIN=bin
CC=gcc
TARGET=target/dataframe
TEST_TARGET=target/test_dataframe
CFLAGS = -g -lm -lpthread $(INCLUDES)
OBJS = objs

# dependencies
DATA_STRUCTURES := $(wildcard ../../data_structures/objs/*.o)

# source and test 
OBJECTS := $(patsubst %.c,%.o,$(wildcard *.c))
TEST_OBJECTS := $(patsubst %.c,%.o,$(wildcard ./tests/*.c))


# link all programs here
all: 
	$(MAKE) -C ../../data_structures
	$(MAKE) source

package:
	$(MAKE) source

test:
	@echo $(DATA_STRUCTURES)

source: $(OBJECTS) $(TEST_OBJECTS) $(DATA_STRUCTURES)
	cc -o $(TARGET) $(OBJECTS) $(TEST_OBJECTS) $(DATA_STRUCTURES) $(CFLAGS)
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
	$(MAKE) -C  ../../data_structures clean

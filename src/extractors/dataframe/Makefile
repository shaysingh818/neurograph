BIN=bin
CC=gcc
TARGET=target/dataframe
TEST_TARGET=target/test_dataframe
CFLAGS = -g -lm -lpthread -lds $(INCLUDES)
OBJS = objs

# source and test 
OBJECTS := $(patsubst %.c,%.o,$(wildcard *.c))
TEST_OBJECTS := $(patsubst %.c,%.o,$(wildcard ./tests/*.c))


# link all programs here
all: 
	$(MAKE) source

package:
	$(MAKE) source

source: $(OBJECTS) $(TEST_OBJECTS) 
	cc -o $(TARGET) $(OBJECTS) $(TEST_OBJECTS) $(CFLAGS)
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

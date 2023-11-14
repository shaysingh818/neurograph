BIN=bin
CC=gcc
TARGET=target/databases
CFLAGS = -g -lm -lpthread -lpq
OBJS = objs


# source and test 
OBJECTS := $(patsubst %.c,%.o,$(wildcard *.c))
TEST_OBJECTS := $(patsubst %.c,%.o,$(wildcard ./tests/*.c))


# link all programs here
all: source

source: $(OBJECTS) $(TEST_OBJECTS)
	cc -o $(TARGET) $(OBJECTS) $(TEST_OBJECTS) $(CFLAGS)
	mkdir $(OBJS)
	mv $(filter-out main.o, $(OBJECTS)) $(OBJS)

# clean compilation (target doesn't work)
clean_binary:
	rm $(TARGET)

clean:
	rm -f *.o *~ *.pyc
	rm -rf $(OBJS)

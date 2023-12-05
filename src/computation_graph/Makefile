BIN=bin
CC=gcc
TARGET=target/computation_graph
SO_TARGET = libcgraph.so
CFLAGS = -g -lm -lpthread -lds -fPIC $(INCLUDES)
SO_FLAGS =  -shared -fPIC  
OBJS = objs

# source and test
OBJECTS := $(patsubst %.c,%.o,$(wildcard *.c))
TEST_OBJECTS := $(patsubst %.c,%.o,$(wildcard ./tests/*.c))

# link all programs here
all:	
	$(MAKE) source

install:
	$(MAKE) shared
	$(MAKE) headers

uninstall:
	rm -r /usr/local/include/computation_graph
	rm /usr/local/lib/$(SO_TARGET)

source: $(OBJECTS) $(TEST_OBJECTS)
	cc -o $(TARGET) $(OBJECTS) $(TEST_OBJECTS) $(CFLAGS)
	mkdir $(OBJS)
	mv $(filter-out main.o, $(OBJECTS)) $(OBJS)

headers:
	mkdir -p computation_graph/
	cp -r includes/ computation_graph/
	mv computation_graph /usr/local/include

shared: $(OBJECTS) $(TEST_OBJECTS)
	$(CC) -o $(SO_TARGET) $(SO_FLAGS) $(OBJECTS) $(TEST_OBJECTS) $(CFLAGS)
	sudo mv $(SO_TARGET) /usr/local/lib
	ldconfig

# clean compilation (target doesn't work)
clean_binary:
	rm $(TARGET)

clean:
	rm -f *.o *~ *.pyc
	rm -rf $(OBJS)

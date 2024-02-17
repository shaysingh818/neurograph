BIN=bin
CC=gcc
TARGET=target/graph
CFLAGS = -g -lm -lpthread -lds -lextractors $(INCLUDES)
SO_FLAGS =  -shared -fPIC  
OBJS = objs
SO_TARGET = libgraph.so

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
	rm -r /usr/local/include/graph
	rm /usr/local/lib/$(SO_TARGET)

# assumes data structures has already been built
package:
	$(MAKE) source

source: $(OBJECTS) $(TEST_OBJECTS) 
	cc -o $(TARGET) $(OBJECTS) $(TEST_OBJECTS) $(CFLAGS)
	mkdir $(OBJS)
	mv $(filter-out main.o, $(OBJECTS)) $(OBJS)

shared: $(OBJECTS) $(TEST_OBJECTS)
	$(CC) -o $(SO_TARGET) $(SO_FLAGS) $(OBJECTS) $(TEST_OBJECTS) $(CFLAGS)
	sudo mv $(SO_TARGET) /usr/local/lib
	ldconfig

headers:
	mkdir -p graph/
	cp -r includes/ graph/	
	mv graph/ /usr/local/include

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


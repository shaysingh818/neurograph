BIN=bin
CC=gcc
TARGET=target/networks
SO_TARGET=libnetworks.so
CFLAGS = -g -lm -lpthread -fPIC -lds -lextractors -lcgraph 
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
	rm -r /usr/local/include/networks
	rm /usr/local/lib/$(SO_TARGET)

source: $(OBJECTS) $(TEST_OBJECTS)
	cc -o $(TARGET) $(OBJECTS) $(TEST_OBJECTS) $(CFLAGS)
	mkdir $(OBJS)
	mv $(filter-out main.o, $(OBJECTS)) $(OBJS)

headers:
	mkdir -p networks/
	cp -r includes/ networks/
	mv networks /usr/local/include

shared: $(OBJECTS) $(TEST_OBJECTS)
	$(CC) -o $(SO_TARGET) $(SO_FLAGS) $(OBJECTS) $(TEST_OBJECTS) $(CFLAGS)
	sudo mv $(SO_TARGET) /usr/local/lib
	ldconfig

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

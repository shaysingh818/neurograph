#Outputs and compilation target
BIN=bin
CC=gcc
TARGET=target/data_structures
OBJS = objs
OUTPUT_OBJ = data_structures.o
SO_TARGET = libds.so

# dependencies
NODE := $(wildcard ./node/objs/*.o)
QUEUE := $(wildcard ./queue/objs/*.o)
SET := $(wildcard ./set/objs/*.o)
LIST := $(wildcard ./list/objs/*.o)
MAP := $(wildcard ./map/objs/*.o)
MATRIX := $(wildcard ./matrix/objs/*.o)
DATA_STRUCTURES = $(NODE) $(QUEUE) $(SET) $(LIST) $(MAP) $(MATRIX)

# source objects
OBJECTS := $(patsubst %.c,%.o,$(wildcard *.c))

# flags
CFLAGS =  -lm -lpthread -g
SO_FLAGS =  -fPIC -shared

all: 
	$(MAKE) build
	$(MAKE) source
	$(MAKE) obj

install:
	$(MAKE) shared
	$(MAKE) headers

uninstall:
	rm -r /usr/local/include/data_structures
	rm /usr/local/lib/libds.so

source: $(OBJECTS) $(DATA_STRUCTURES)
	cc -o $(TARGET) $(OBJECTS) $(DATA_STRUCTURES) $(CFLAGS)

obj: 
	mkdir $(OBJS)
	cp $(DATA_STRUCTURES) $(OBJS)


shared: $(DATA_STRUCTURES)
	$(CC) -o $(SO_TARGET) $(SO_FLAGS) $(DATA_STRUCTURES) $(CFLAGS)
	sudo mv $(SO_TARGET) /usr/local/lib
	ldconfig

headers:

	mkdir -p data_structures/matrix
	cp -r matrix/includes data_structures/matrix

	mkdir -p data_structures/queue
	cp -r queue/includes data_structures/queue

	mkdir -p data_structures/node
	cp -r node/includes data_structures/node

	mkdir -p data_structures/set
	cp -r set/includes data_structures/set

	mkdir -p data_structures/list
	cp -r list/includes data_structures/list

	mkdir -p data_structures/map
	cp -r map/includes data_structures/map

	mv data_structures /usr/local/include

build:
	$(MAKE) -C ./node
	$(MAKE) -C ./queue
	$(MAKE) -C ./set
	$(MAKE) -C ./list
	$(MAKE) -C ./map
	$(MAKE) -C ./matrix

# clean compilation (target doesn't work)
clean:
	rm -f  *.o *~ *.pyc
	rm -rf objs
	$(MAKE) -C  ./map clean
	$(MAKE) -C ./matrix clean
	$(MAKE) -C ./set clean
	$(MAKE) -C ./list clean
	$(MAKE) -C  ./queue clean
	$(MAKE) -C  ./node clean
